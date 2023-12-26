#ifndef GUIDER_FONTS_H
#define GUIDER_FONTS_H
#ifdef __cplusplus
extern "C" {
#endif

#if LVGL_VERSION_MAJOR == 7
#include "lv_font/lv_font.h"
#else
#include "src/font/lv_font.h"
#endif

LV_FONT_DECLARE(lv_font_montserratMedium_18);
LV_FONT_DECLARE(lv_font_montserratMedium_16);

void init_guider_fonts();

#ifdef __cplusplus
}
#endif
#endif