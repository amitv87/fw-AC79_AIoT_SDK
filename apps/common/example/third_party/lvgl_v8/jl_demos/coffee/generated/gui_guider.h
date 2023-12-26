/*Generate Code, Do NOT Edit!*/
#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"
typedef struct {
    // Screen coffeePour
    lv_obj_t *coffeePour;
    bool      coffeePour_del;
    lv_obj_t *coffeePour_lbl_1;
    lv_obj_t *coffeePour_line_1;
    lv_obj_t *coffeePour_animimg_coffee;
    lv_obj_t *coffeePour_line_2;
    lv_obj_t *coffeePour_btn_full;
    lv_obj_t *coffeePour_btn_full_label;
    lv_obj_t *coffeePour_btn_stop;
    lv_obj_t *coffeePour_btn_stop_label;
    lv_obj_t *coffeePour_btn_continue;
    lv_obj_t *coffeePour_btn_continue_label;
    lv_obj_t *coffeePour_btn_reset;
    lv_obj_t *coffeePour_btn_reset_label;
    lv_obj_t *coffeePour_img_1;

} lv_ui;
void ui_init_style(lv_style_t *style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
// Screen coffeePour
void setup_scr_coffeePour(lv_ui *ui);

#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(coffeePour_animimg_coffeef01)
LV_IMG_DECLARE(coffeePour_animimg_coffeef02)
LV_IMG_DECLARE(coffeePour_animimg_coffeef03)
LV_IMG_DECLARE(coffeePour_animimg_coffeef04)
LV_IMG_DECLARE(coffeePour_animimg_coffeef05)
LV_IMG_DECLARE(coffeePour_animimg_coffeef06)
LV_IMG_DECLARE(coffeePour_animimg_coffeef07)
LV_IMG_DECLARE(coffeePour_animimg_coffeef08)
LV_IMG_DECLARE(coffeePour_animimg_coffeef09)
LV_IMG_DECLARE(coffeePour_animimg_coffeef10)
LV_IMG_DECLARE(coffeePour_animimg_coffeef11)
LV_IMG_DECLARE(coffeePour_animimg_coffeef12)
LV_IMG_DECLARE(coffeePour_animimg_coffeef13)
LV_IMG_DECLARE(coffeePour_animimg_coffeef14)
LV_IMG_DECLARE(coffeePour_animimg_coffeef15)
LV_IMG_DECLARE(coffeePour_animimg_coffeef16)
LV_IMG_DECLARE(coffeePour_animimg_coffeef17)
LV_IMG_DECLARE(coffeePour_animimg_coffeef18)
LV_IMG_DECLARE(coffeePour_animimg_coffeef19)
LV_IMG_DECLARE(coffeePour_animimg_coffeef20)
LV_IMG_DECLARE(coffeePour_animimg_coffeef21)
LV_IMG_DECLARE(coffeePour_animimg_coffeef22)
LV_IMG_DECLARE(coffeePour_animimg_coffeef23)
LV_IMG_DECLARE(coffeePour_animimg_coffeef24)
LV_IMG_DECLARE(coffeePour_animimg_coffeef25)
LV_IMG_DECLARE(coffeePour_animimg_coffeef26)
LV_IMG_DECLARE(coffeePour_animimg_coffeef27)
LV_IMG_DECLARE(coffeePour_animimg_coffeef28)
LV_IMG_DECLARE(coffeePour_animimg_coffeef29)
LV_IMG_DECLARE(coffeePour_animimg_coffeef30)
LV_IMG_DECLARE(coffeePour_animimg_coffeef31)
LV_IMG_DECLARE(coffeePour_animimg_coffeef11);
LV_IMG_DECLARE(coffeePour_animimg_coffeef12);
LV_IMG_DECLARE(coffeePour_animimg_coffeef31);
LV_IMG_DECLARE(coffeePour_animimg_coffeef10);
LV_IMG_DECLARE(coffeePour_animimg_coffeef30);
LV_IMG_DECLARE(coffeePour_animimg_coffeef19);
LV_IMG_DECLARE(coffeePour_animimg_coffeef17);
LV_IMG_DECLARE(coffeePour_animimg_coffeef18);
LV_IMG_DECLARE(coffeePour_animimg_coffeef15);
LV_IMG_DECLARE(coffeePour_animimg_coffeef16);
LV_IMG_DECLARE(coffeePour_animimg_coffeef13);
LV_IMG_DECLARE(coffeePour_animimg_coffeef14);
LV_IMG_DECLARE(coffeePour_animimg_coffeef22);
LV_IMG_DECLARE(coffeePour_animimg_coffeef01);
LV_IMG_DECLARE(coffeePour_animimg_coffeef23);
LV_IMG_DECLARE(coffeePour_animimg_coffeef20);
LV_IMG_DECLARE(coffeePour_animimg_coffeef21);
LV_IMG_DECLARE(coffeePour_animimg_coffeef08);
LV_IMG_DECLARE(coffeePour_animimg_coffeef09);
LV_IMG_DECLARE(coffeePour_animimg_coffeef06);
LV_IMG_DECLARE(coffeePour_animimg_coffeef28);
LV_IMG_DECLARE(coffeePour_animimg_coffeef07);
LV_IMG_DECLARE(coffeePour_animimg_coffeef29);
LV_IMG_DECLARE(coffeePour_animimg_coffeef04);
LV_IMG_DECLARE(coffeePour_animimg_coffeef26);
LV_IMG_DECLARE(coffeePour_animimg_coffeef05);
LV_IMG_DECLARE(coffeePour_animimg_coffeef27);
LV_IMG_DECLARE(coffeePour_animimg_coffeef02);
LV_IMG_DECLARE(coffeePour_animimg_coffeef24);
LV_IMG_DECLARE(coffeePour_animimg_coffeef03);
LV_IMG_DECLARE(coffeePour_animimg_coffeef25);
LV_IMG_DECLARE(_qrcode_alpha_71x65);
#ifdef __cplusplus
}
#endif
#endif
