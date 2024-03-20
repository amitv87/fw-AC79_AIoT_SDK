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

#define LVGL_TASK_NAME  "lvgl_main_task"

#define FILTER_SAME_COORDINATES 0 //如果应用没有长按相同坐标触发事件的需求，可打开，减少消息发送消耗

enum {
    UI_MSG_TOUCH = 1,
    UI_MSG_TIMEOUT,
};

struct touch_event {
    u16 x;
    u16 y;
    u8 status;
    u8 has_energy;
};

#if FILTER_SAME_COORDINATES
static struct touch_event last_touch_event;
#endif

void lv_port_get_touch_x_y_status(struct touch_event *e, u16 *x, u16 *y, u8 *status)
{
    *x = e->x;
    *y = e->y;
    *status = e->status;
}

static char lvgl_touch_msg_remain_cnt;
int lcd_touch_interrupt_event(u16 x, u16 y, u8 status)
{
    if (lvgl_touch_msg_remain_cnt > 8) { //最大缓存触摸坐标，可调试
        /*printf("lvgl touch msg drop1 %d, %d, %d\n", x, y, status);*/
        return -1;
    }

#if FILTER_SAME_COORDINATES
    if (last_touch_event.x == x && last_touch_event.y == y && last_touch_event.status == status) {
        /*printf("lvgl filter same touch coordinates %d, %d, %d\n", x, y, status);*/
        return 0;
    }
#endif

    ++lvgl_touch_msg_remain_cnt;

    int err;
    int msg[2 + sizeof(struct touch_event) / 4];
    msg[0] = UI_MSG_TOUCH;
    struct touch_event event;
    event.x = x;
    event.y = y;
    event.status = status;
    memcpy(&msg[1], &event, sizeof(struct touch_event));
    err =  os_taskq_post_type(LVGL_TASK_NAME, Q_USER, ARRAY_SIZE(msg), msg);
    if (err) {
        --lvgl_touch_msg_remain_cnt;
        /*printf("lvgl touch msg drop2 %d, %d, %d\n", x, y, status);*/
    } else {
#if FILTER_SAME_COORDINATES
        last_touch_event.x = x;
        last_touch_event.y = y;
        last_touch_event.status = status;
#endif
    }
    return err;
}

static char lvgl_timerout_msg_remain_cnt;
static void lvgl_timer_event_timeout(void)
{
    int err;
    int msg[2];
    msg[0] = UI_MSG_TIMEOUT;
    err =  os_taskq_post_type(LVGL_TASK_NAME, Q_USER, ARRAY_SIZE(msg), msg);
    if (err) {
        printf("lvgl_timer_event_timeout post_ui_msg err=%d\n", err);
        --lvgl_timerout_msg_remain_cnt;
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
    u32 time_till_next;

    //刷新第一帧不需要事件触发
    time_till_next = lv_timer_handler();
    if (time_till_next != LV_NO_TIMER_READY) {
        ++lvgl_timerout_msg_remain_cnt;
        sys_timeout_add_to_task(LVGL_TASK_NAME, NULL, lvgl_timer_event_timeout, time_till_next);
    }

    while (1) {
        ret = os_taskq_pend(NULL, msg, ARRAY_SIZE(msg));
        if (ret != OS_TASKQ || msg[0] != Q_USER) {
            printf("lvgl_main_task os_taskq_pend err=%d\n", ret);
            continue;
        }
        if (msg[1] == UI_MSG_TOUCH) {
            --lvgl_touch_msg_remain_cnt;
            /*printf("lvgl_touch_msg_remain_cnt = %d\r\n", lvgl_touch_msg_remain_cnt);*/
            struct touch_event *e = (struct touch_event *)&msg[2];
            lv_indev_timer_read(e);
        }

        if (msg[1] == UI_MSG_TIMEOUT) {
            --lvgl_timerout_msg_remain_cnt;//消耗掉UI超时消息
        }

__repeat_run:
        time_till_next = lv_timer_handler();
        if (time_till_next == 0) {//没有时间释放CPU了
            if (lvgl_touch_msg_remain_cnt) {
                continue;    //如果还有触摸事件，那就把触摸坐标拿到再运行
            } else {
                goto __repeat_run;
            }
        }

        if (time_till_next != LV_NO_TIMER_READY) {
            /*printf("lvgl time_till_next %d ms, timerout_msg_remain_cnt = %d\r\n", time_till_next, lvgl_timerout_msg_remain_cnt);*/
            if (lvgl_timerout_msg_remain_cnt == 0) {//超时事件消耗完了才触发发送消息
                if (lvgl_touch_msg_remain_cnt == 0) { //如果触摸事件还没消耗完，优先消耗触摸事件，LVGL会持续运转，不需要超时事件调度
                    /*printf("lvgl_post timeout msg\r\n");*/
                    ++lvgl_timerout_msg_remain_cnt;
                    sys_timeout_add_to_task(LVGL_TASK_NAME, NULL, lvgl_timer_event_timeout, time_till_next); //FIX_ME:系统未支持1ms时间超时释放cpu
                } else {
                    /*printf("lvgl_touch_msg_remain_cnt = %d\r\n", lvgl_touch_msg_remain_cnt);*/
                }
            }
        }
    }
}

static int lvgl_main_task_init(void)
{
    puts("lvgl_main_task_init \n\n");
    return thread_fork(LVGL_TASK_NAME, 25, 8 * 1024, 256, 0, lvgl_main_task, NULL);
}
late_initcall(lvgl_main_task_init);


#endif


