#include "app_config.h"

#if LV_USE_PERF_MONITOR || LV_USE_MEM_MONITOR
#include "widgets/lv_label.h"
#endif

#ifdef USE_LVGL_UI_DEMO
#include "lv_conf.h"
#include "system/includes.h"
#include "lvgl.h"
#include "lv_demo_benchmark.h"
#include "lv_demo_widgets.h"
#include "lv_example_freetype.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_port_fs.h"
#include "ui_new.h"

#define LVGL_TASK_NAME  "lvgl_main_task"

/*REGISTER_UI_MODULE_EVENT_HANDLER(0)*/
/*.onchange  = NULL,*/
/*};*/

void gui_msg_var_cb(int msg_id)
{
    for (const struct ui_module_event_handler *p = ui_module_event_handler_begin; p < ui_module_event_handler_end; p++) {
        if (p->msg_id == msg_id) {
            p->onchange(0, 0);
            break;
        }
    }
}



#define TCFG_FILTER_SAME_COORDINATES 1 //如果应用没有长按相同坐标触发事件的需求，可打开，减少消息发送消耗

static char lvgl_timerout_msg_remain_flag;
static char lvgl_touch_msg_remain_cnt;
static u16 lvgl_timer_timeout_id;

enum {
    UI_MSG_TOUCH,
    UI_MSG_TIMER_TIMEOUT,
    UI_MSG_MODULE_CHANGE,
    UI_MSG_MODULE_CHANGE_REFRESH_NOW,
};

struct touch_event {
    u16 x;
    u16 y;
    u8 status;
    u8 has_energy;
};

#if TCFG_FILTER_SAME_COORDINATES
static struct touch_event last_touch_event;
#endif

void lv_port_get_touch_x_y_status(struct touch_event *e, u16 *x, u16 *y, u8 *status)
{
    *x = e->x;
    *y = e->y;
    *status = e->status;
}

int lcd_touch_interrupt_event(u16 x, u16 y, u8 status)
{
    if (lvgl_touch_msg_remain_cnt > 1) { //最大缓存触摸坐标，可调试
        /*printf("lvgl touch msg drop1 %d, %d, %d\n", x, y, status);*/
        return -1;
    }

#if TCFG_FILTER_SAME_COORDINATES
    if (last_touch_event.x == x && last_touch_event.y == y && last_touch_event.status == status) {
        /*printf("lvgl filter same touch coordinates %d, %d, %d\n", x, y, status);*/
        return 0;
    }
#endif

    int err;
    int msg[2 + sizeof(struct touch_event) / 4];
    msg[0] = UI_MSG_TOUCH;
    struct touch_event event;
    event.x = x;
    event.y = y;
    event.status = status;
    memcpy(&msg[1], &event, sizeof(struct touch_event));
    err =  os_taskq_post_type(LVGL_TASK_NAME, Q_MSG, ARRAY_SIZE(msg), msg);
    if (err) {
        printf("lvgl touch msg drop2 %d, %d, %d\n", x, y, status);
    } else {
        ++lvgl_touch_msg_remain_cnt;
#if TCFG_FILTER_SAME_COORDINATES
        last_touch_event.x = x;
        last_touch_event.y = y;
        last_touch_event.status = status;
#endif
    }
    return err;
}

static void lvgl_timer_event_timeout(void)
{
    lvgl_timer_timeout_id = 0;

    int err;
    int msg[2];
    msg[0] = UI_MSG_TIMER_TIMEOUT;
    err =  task_queue_post_event(LVGL_TASK_NAME,  msg, ARRAY_SIZE(msg));
    if (err) {
        printf("lvgl_timer_event_timeout post_ui_msg err=%d\n", err);
    } else {
        lvgl_timerout_msg_remain_flag = 1;
    }
}

////////
int gui_msg_send(u32 msg_id, void *value, int32_t len)
{
    printf("####^*^###-> %s, %d,%d,%d \r\n", __FUNCTION__, msg_id, value, len);
    return 0;
}
////////
void lvgl_module_msg_send(u32 msg_id, void *value, int32_t len, char refr_now)
{
    int err;
    int msg[4];
    msg[0] = refr_now ? UI_MSG_MODULE_CHANGE_REFRESH_NOW : UI_MSG_MODULE_CHANGE;
    msg[1] = msg_id;
    msg[2] = value;
    msg[3] = len;

    err = os_taskq_del_type(LVGL_TASK_NAME, Q_MSG | msg_id);
    if (err == 0) {
        printf("lvgl_module_msg[%d] del\n", msg_id);
    }
    err =  os_taskq_post_type(LVGL_TASK_NAME, Q_MSG | msg_id, ARRAY_SIZE(msg), msg);
    if (err) {
        printf("lvgl_module_msg_send err=%d\n", err);
    }
}
static void lvgl_main_task(void *priv)
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    /*lv_port_fs_init();*/
    /*lv_png_init();*/


    // uncomment one of these demos
    /*lv_example_arc_1();*/
    /*lv_demo_benchmark();*/
    /* lv_example_freetype_1(); */
    lv_demo_widgets();
    //lv_example_rlottie_1();//FIXME:有死机问题 void renderer::Layer::render(VPainter *painter, const VRle &inheritMask
    //lv_example_rlottie_2();
    /* lv_example_btn_1(); */
    /*lv_demo_keypad_encoder();*/
    /*lv_demo_music();          */
    /*lv_demo_stress();           */
    /*lvgl_fs_test();*/
    //ui_init(); //SquareLine_demos

    int msg[8] = {0};
    int ret;
    char lvgl_task_pend_timeout_refr_flag = 0;
    u32 time_till_next;
    u32 last_refr_time;

    //刷新第一帧不需要事件触发
    time_till_next = lv_task_handler();
    if (time_till_next != LV_NO_TIMER_READY) {
        lvgl_timer_timeout_id = sys_timeout_add(NULL, lvgl_timer_event_timeout, time_till_next);
    }

    while (1) {

        ret = os_taskq_pend_timeout(NULL, msg, ARRAY_SIZE(msg), 3);//超时是为了模型改变，但未触发刷屏，设置最大延时30毫秒
        if (ret != OS_TASKQ && ret != OS_TIMEOUT) {
            printf("lvgl_main_task os_taskq_pend err=%d %d\n", ret, msg[0]);
            continue;
        }
        if (ret == OS_TIMEOUT) {
            if (lvgl_task_pend_timeout_refr_flag == 0) {
                /*puts("ui task pend timeout, nothing happend\r\n");*/
                continue; //如果没有模型改变消息，不需要刷新屏幕
            } else {
                puts("ui task pend timeout, module change happend\r\n");
            }
            lvgl_task_pend_timeout_refr_flag = 0;
        } else if (msg[1] == UI_MSG_TOUCH) {
            --lvgl_touch_msg_remain_cnt;
            /* printf("lvgl_touch_msg_remain_cnt = %d\r\n", lvgl_touch_msg_remain_cnt); */
            struct touch_event *e = (struct touch_event *)&msg[2];
            lv_indev_timer_read(e);
        } else if (msg[1] == UI_MSG_MODULE_CHANGE || msg[1] == UI_MSG_MODULE_CHANGE_REFRESH_NOW) {
            if (gui_msg_send(msg[2], (void *)msg[3], msg[4])) {
                printf("gui msg_id[%d] had unsubscribe\r\n", msg[2]);
            }
            if (msg[1] == UI_MSG_MODULE_CHANGE) {
                if (timer_get_ms() - last_refr_time < 18) {//对于不需要立刻刷屏的模型改变的消息,限制最大间隔18毫秒刷屏一次
                    /*printf("UI_MSG_MODULE_CHANGE DELAY");*/
                    lvgl_task_pend_timeout_refr_flag = 1;
                    continue;
                } else {
                    /*printf("UI_MSG_MODULE_CHANGE REFRESH NOW");*/
                }
            }
        } else if (msg[1] == UI_MSG_TIMER_TIMEOUT) {
            lvgl_timerout_msg_remain_flag = 0; //标记LVGL定时器超时消息已经消耗掉
        }

//__repeat_run:
        last_refr_time = timer_get_ms();
        time_till_next = lv_task_handler();

        if (time_till_next == 0) {//没有时间释放CPU了
            /*printf("lvgl time_till_next == 0\r\n");*/
#if 0// TCFG_LVGL_HIJACK_CPU//如果cpu不够外面优先级低的任务被阻挡厉害，就不搞极端行为，把cpu释放点出来, 劫持CPU可以最高快1帧/秒
            wdt_clear();
            if (lvgl_touch_msg_remain_cnt || lvgl_module_change_msg_remain_cnt) {
                continue;    //如果还有触摸事件未消耗完，那就把触摸坐标拿到再运行
            } else {
                goto __repeat_run;
            }
#endif
        }

        if (lvgl_touch_msg_remain_cnt == 0) { //如果触摸事件还没消耗完，利用触摸事件来调度运行，不需要超时事件来调度, LVGL任务会持续运转
            /*printf("lvgl time_till_next %d ms, lvgl_timer_timeout_id=%d, lvgl_timerout_msg_remain_flag=%d\r\n", time_till_next,lvgl_timer_timeout_id,lvgl_timerout_msg_remain_flag); */
            if (time_till_next != LV_NO_TIMER_READY) {//如果LVGL内部有注册超时定时器
                if (lvgl_timer_timeout_id) { //超时函数还未跑起，重新配置超时时间
                    sys_timeout_del(lvgl_timer_timeout_id);
                } else if (lvgl_timerout_msg_remain_flag) { //超时函数已跑起，并且post消息成功，但是消息还在队列内未消耗
                    lvgl_timerout_msg_remain_flag = 0;
                    if (os_taskq_del_type(LVGL_TASK_NAME, Q_EVENT)) {
                        puts("lvgl_timeout_event_del err\r\n");
                    }
                }
                /*printf("lvgl_post timeout msg\r\n");*/
                lvgl_timer_timeout_id = sys_timeout_add(NULL, lvgl_timer_event_timeout, time_till_next); //FIX_ME:系统未支持1ms时间超时释放cpu
            }
        }

    }//while(1)
}

static int lvgl_main_task_init(void)
{
    puts("lvgl_v8_main_task_init \n\n");
    return thread_fork(LVGL_TASK_NAME, 1, 8 * 1024, 256, 0, lvgl_main_task, NULL);
}
late_initcall(lvgl_main_task_init);


#endif


