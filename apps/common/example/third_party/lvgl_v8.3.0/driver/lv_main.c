#include "app_config.h"

#if LV_USE_PERF_MONITOR || LV_USE_MEM_MONITOR
#include "widgets/lv_label.h"
#endif

#ifdef USE_LVGL_UI_DEMO

#include "lv_conf.h"
#include "system/includes.h"
#include "lvgl.h"

extern void (*lv_lcd_init_handler)(void);
extern int (*lv_touchpad_handler)(int *x, int *y);
extern void (*lv_lcd_draw_handler)(int, int, int, int, void *);
extern void *get_touch_x_y(void);
extern void lcd_lvgl_full(u16 xs, u16 xe, u16 ys, u16 ye, char *img);

void lv_header_timer_run(void)
{
    lv_tick_inc(2);
}


static void Calculation_frame(void)
{
    static u32 tstart = 0, tdiff = 0;
    static u8 fps_cnt = 0;

    fps_cnt++ ;

    if (!tstart) {
        tstart = timer_get_ms();
    } else {
        tdiff = timer_get_ms() - tstart;

        if (tdiff >= 1000) {
            printf("\n [MSG]fps_count = %d\n", fps_cnt *  1000 / tdiff);
            tstart = 0;
            fps_cnt = 0;
        }
    }
}

static struct touch_hdl {
    u16 x;
    u16 y;
    u8 status;
};
static struct touch_hdl *hdl = NULL;

static int lv_touch_get_x_y(int *x, int *y)
{
    *x = hdl->x;
    *y = hdl->y;
    return hdl->status;
}
//对接平台显示初始化
static void lv_lcd_init(void)
{
    void user_lcd_init(void);
    user_lcd_init();
}
//对接平台发送帧接口
static void lv_send_fps(int x1, int x2, int y1, int y2, void *data)
{
    lcd_lvgl_full(x1, x2, y1, y2, (u16 *)data);
    Calculation_frame();
}

static void  lv_dev_hal_init(void)
{
    hdl = get_touch_x_y();
    lv_touchpad_handler = lv_touch_get_x_y;
    lv_lcd_init_handler = lv_lcd_init;
    lv_lcd_draw_handler = lv_send_fps;
}

void lvgl_rotation_test(void *priv)
{
    static u8 time = 0;
    time++;
    time %= 2;
    if (time) {
        lv_disp_set_rotation(NULL, 1);
    } else {
        lv_disp_set_rotation(NULL, 0);
    }
}

static void lvgl_main_task(void *priv)
{
    lv_init();
    sys_timer_add(NULL, lv_header_timer_run, 1); //LVGL心跳提供
    lv_dev_hal_init();
    lv_port_disp_init();
    lv_port_indev_init();

#if 0  //UIdemo
    void lv_demo_widgets(void);
    lv_demo_widgets();
#else  //帧率测试
    void lv_demo_benchmark(void);
    lv_demo_benchmark();
#endif
    /* sys_timer_add(NULL,lvgl_rotation_test, 2000); */
    while (1) {
        lv_timer_handler();
    }
}

static int lvgl_main_task_init(void)
{
    puts("lvgl_main_task_init \n\n");
    //说明由于LVGL没有加延时让出CPU需要配置为最低优先级 高优先级不能长时间占用CPU不然LVGL运行卡顿
    return thread_fork("lvgl_main_task", 1, 1024, 0, 0, lvgl_main_task, NULL);
}
late_initcall(lvgl_main_task_init);


#endif


