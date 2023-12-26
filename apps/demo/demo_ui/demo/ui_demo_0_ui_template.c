/********************************测试例程说明************************************
 *  功能说明：
 *  	ui工程路径ui_project目录下如果里面没文件需要自行下载解压到该文件夹下
 *  	使用JL_UI 显示一张图片
 *  	ui工程位置 ui_project/0.ui_template
 *  	ui资源文件夹位置cpu/wl82/tools/ui_res
 *  	ui音频文件夹位置cpu/wl82/tools/audlogo
 *  	ui自动化脚本对应ui工程下auto_ui_res
 *  	ui控件定义ename.h  不同的ui工程对应不同的ename.h内容 该文件在ui工程下找
 *  	如果不需要自动开关ui工程自行修改auto_ui_res.bat
 * ******************************************************************************/
#include "app_config.h"
#include "system/includes.h"
//ui头文件
#include "ename.h"//控件定义
#include "res_config.h"//ui资源文件夹路径定义
#include "ui/ui.h"//ui接口

#ifdef UI_DEMO_0_UI_TEMPLATE
static void ui_test_task(void *priv) //测试显示不同大小文字
{
    user_ui_lcd_init();
    ui_show_main(PAGE_0);
    while (1) {
        printf("\n [ui_test_task] %s -[run] %d\n", __FUNCTION__, __LINE__);
        os_time_dly(100);
    }
}

static int ui_test_task_init(void)
{
    puts("ui_test_task_init \n\n");
    return thread_fork("ui_test_task", 5, 1024, 0, 0, ui_test_task, NULL);
}
late_initcall(ui_test_task_init);

#endif //UI_DEMO_0_UI_TEMPLATE



