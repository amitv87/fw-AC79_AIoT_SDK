/**
 * @file lv_port_disp_templ.h
 *
 */

/*Copy this file as "lv_port_disp.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_DISP_TEMPL_H
#define LV_PORT_DISP_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl_v8/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/
// #define THREE_FB_ACCELERATION  //利用双核双线程+3FB加速 ,防止mcu lcd刷新完还空隙闲着,某些场景能够提升1-2帧
/* #define THREE_FB_ACCELERATION_BRANCH_TE  //带te分行刷新 */

/* #define LVGL_TEST_LINE_MUNB_MODE //用于自动检测最佳分行数量 需要最少有三帧屏buf 通过打印获取到最佳的分行数量 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
void lv_port_disp_init(void);

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void);

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/
