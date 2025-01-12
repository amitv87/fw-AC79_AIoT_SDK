/**
 * @file lv_draw_sw_blend_rgb888.h
 *
 */

#ifndef LV_DRAW_SW_BLEND_RGB888_H
#define LV_DRAW_SW_BLEND_RGB888_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_draw_sw.h"
#if LV_USE_DRAW_SW

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

LV_ATTRIBUTE_FAST_MEM void lv_draw_sw_blend_color_to_rgb888(_lv_draw_sw_blend_fill_dsc_t *dsc, uint32_t dest_px_size);

LV_ATTRIBUTE_FAST_MEM void lv_draw_sw_blend_image_to_rgb888(_lv_draw_sw_blend_image_dsc_t *dsc, uint32_t dest_px_size);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DRAW_SW*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DRAW_SW_BLEND_RGB888_H*/
