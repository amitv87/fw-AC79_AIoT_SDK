/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

const lv_img_dsc_t *coffeePour_animimg_coffee_imgs[31] = {
    &coffeePour_animimg_coffeef01,
    &coffeePour_animimg_coffeef02,
    &coffeePour_animimg_coffeef03,
    &coffeePour_animimg_coffeef04,
    &coffeePour_animimg_coffeef05,
    &coffeePour_animimg_coffeef06,
    &coffeePour_animimg_coffeef07,
    &coffeePour_animimg_coffeef08,
    &coffeePour_animimg_coffeef09,
    &coffeePour_animimg_coffeef10,
    &coffeePour_animimg_coffeef11,
    &coffeePour_animimg_coffeef12,
    &coffeePour_animimg_coffeef13,
    &coffeePour_animimg_coffeef14,
    &coffeePour_animimg_coffeef15,
    &coffeePour_animimg_coffeef16,
    &coffeePour_animimg_coffeef17,
    &coffeePour_animimg_coffeef18,
    &coffeePour_animimg_coffeef19,
    &coffeePour_animimg_coffeef20,
    &coffeePour_animimg_coffeef21,
    &coffeePour_animimg_coffeef22,
    &coffeePour_animimg_coffeef23,
    &coffeePour_animimg_coffeef24,
    &coffeePour_animimg_coffeef25,
    &coffeePour_animimg_coffeef26,
    &coffeePour_animimg_coffeef27,
    &coffeePour_animimg_coffeef28,
    &coffeePour_animimg_coffeef29,
    &coffeePour_animimg_coffeef30,
    &coffeePour_animimg_coffeef31
};

void setup_scr_coffeePour(lv_ui *ui)
{

    //Write codes coffeePour
    ui->coffeePour = lv_obj_create(NULL);

    //Set style for coffeePour. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->coffeePour, lv_color_make(0x2A, 0x26, 0x31), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->coffeePour, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->coffeePour, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->coffeePour, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->coffeePour, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour, LV_STATE_DEFAULT);

    //Write codes coffeePour_lbl_1
    ui->coffeePour_lbl_1 = lv_label_create(ui->coffeePour);
    lv_label_set_text(ui->coffeePour_lbl_1, "JieLi Coffee Latte");
    lv_label_set_long_mode(ui->coffeePour_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for coffeePour_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->coffeePour_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->coffeePour_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->coffeePour_lbl_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->coffeePour_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->coffeePour_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->coffeePour_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->coffeePour_lbl_1, &lv_font_montserratMedium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->coffeePour_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->coffeePour_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_lbl_1, 59, 15);
    lv_obj_set_size(ui->coffeePour_lbl_1, 217, 29);
    lv_obj_set_scrollbar_mode(ui->coffeePour_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_lbl_1, LV_STATE_DEFAULT);

    //Write codes coffeePour_line_1
    ui->coffeePour_line_1 = lv_line_create(ui->coffeePour);

    //Set style for coffeePour_line_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_line_color(ui->coffeePour_line_1, lv_color_make(0x60, 0x60, 0x60), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->coffeePour_line_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->coffeePour_line_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_line_1, 3, 80);
    lv_obj_set_size(ui->coffeePour_line_1, 122, 182);
    lv_obj_set_scrollbar_mode(ui->coffeePour_line_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_line_1, LV_STATE_DEFAULT);
    static lv_point_t coffeePour_line_1[] = {{120, 0}, {120, 180}, {120, 90}, {0, 90},};
    lv_line_set_points(ui->coffeePour_line_1, coffeePour_line_1, 4);

    //Write codes coffeePour_animimg_coffee
    ui->coffeePour_animimg_coffee = lv_animimg_create(ui->coffeePour);

    //Set style for coffeePour_animimg_coffee. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_animimg_coffee, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->coffeePour_animimg_coffee, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_animimg_coffee, 107, 298);
    lv_obj_set_size(ui->coffeePour_animimg_coffee, 96, 85);
    lv_obj_set_scrollbar_mode(ui->coffeePour_animimg_coffee, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_animimg_coffee, LV_STATE_DEFAULT);
    lv_animimg_set_src(ui->coffeePour_animimg_coffee, (const void **) coffeePour_animimg_coffee_imgs, 31);
    lv_animimg_set_duration(ui->coffeePour_animimg_coffee, 930);
    lv_animimg_set_repeat_count(ui->coffeePour_animimg_coffee, -1);
    lv_animimg_start(ui->coffeePour_animimg_coffee);

    //Write codes coffeePour_line_2
    ui->coffeePour_line_2 = lv_line_create(ui->coffeePour);

    //Set style for coffeePour_line_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_line_color(ui->coffeePour_line_2, lv_color_make(0x60, 0x60, 0x60), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->coffeePour_line_2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->coffeePour_line_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_line_2, 187, 80);
    lv_obj_set_size(ui->coffeePour_line_2, 129, 182);
    lv_obj_set_scrollbar_mode(ui->coffeePour_line_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_line_2, LV_STATE_DEFAULT);
    static lv_point_t coffeePour_line_2[] = {{0, 0}, {0, 180}, {0, 90}, {120, 90},};
    lv_line_set_points(ui->coffeePour_line_2, coffeePour_line_2, 4);

    //Write codes coffeePour_btn_full
    ui->coffeePour_btn_full = lv_btn_create(ui->coffeePour);

    //Set style for coffeePour_btn_full. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_btn_full, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->coffeePour_btn_full, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->coffeePour_btn_full, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->coffeePour_btn_full, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->coffeePour_btn_full, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->coffeePour_btn_full, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->coffeePour_btn_full, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->coffeePour_btn_full, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->coffeePour_btn_full, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->coffeePour_btn_full, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->coffeePour_btn_full, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->coffeePour_btn_full, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->coffeePour_btn_full, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->coffeePour_btn_full, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->coffeePour_btn_full, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->coffeePour_btn_full, lv_color_make(0xD1, 0xC1, 0xB2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->coffeePour_btn_full, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->coffeePour_btn_full, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_btn_full, 8, 104);
    lv_obj_set_size(ui->coffeePour_btn_full, 80, 50);
    lv_obj_set_scrollbar_mode(ui->coffeePour_btn_full, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_btn_full, LV_STATE_DEFAULT);
    ui->coffeePour_btn_full_label = lv_label_create(ui->coffeePour_btn_full);
    lv_label_set_text(ui->coffeePour_btn_full_label, "FULL");
    lv_obj_set_style_pad_all(ui->coffeePour_btn_full, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->coffeePour_btn_full_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes coffeePour_btn_stop
    ui->coffeePour_btn_stop = lv_btn_create(ui->coffeePour);

    //Set style for coffeePour_btn_stop. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_btn_stop, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->coffeePour_btn_stop, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->coffeePour_btn_stop, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->coffeePour_btn_stop, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->coffeePour_btn_stop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->coffeePour_btn_stop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->coffeePour_btn_stop, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->coffeePour_btn_stop, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->coffeePour_btn_stop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->coffeePour_btn_stop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->coffeePour_btn_stop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->coffeePour_btn_stop, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->coffeePour_btn_stop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->coffeePour_btn_stop, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->coffeePour_btn_stop, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->coffeePour_btn_stop, lv_color_make(0xD1, 0xC1, 0xB2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->coffeePour_btn_stop, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->coffeePour_btn_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_btn_stop, 8, 192);
    lv_obj_set_size(ui->coffeePour_btn_stop, 80, 50);
    lv_obj_set_scrollbar_mode(ui->coffeePour_btn_stop, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_btn_stop, LV_STATE_DEFAULT);
    ui->coffeePour_btn_stop_label = lv_label_create(ui->coffeePour_btn_stop);
    lv_label_set_text(ui->coffeePour_btn_stop_label, "STOP");
    lv_obj_set_style_pad_all(ui->coffeePour_btn_stop, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->coffeePour_btn_stop_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes coffeePour_btn_continue
    ui->coffeePour_btn_continue = lv_btn_create(ui->coffeePour);

    //Set style for coffeePour_btn_continue. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_btn_continue, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->coffeePour_btn_continue, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->coffeePour_btn_continue, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->coffeePour_btn_continue, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->coffeePour_btn_continue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->coffeePour_btn_continue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->coffeePour_btn_continue, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->coffeePour_btn_continue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->coffeePour_btn_continue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->coffeePour_btn_continue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->coffeePour_btn_continue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->coffeePour_btn_continue, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->coffeePour_btn_continue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->coffeePour_btn_continue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->coffeePour_btn_continue, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->coffeePour_btn_continue, lv_color_make(0xD1, 0xC1, 0xB2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->coffeePour_btn_continue, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->coffeePour_btn_continue, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_btn_continue, 205, 104);
    lv_obj_set_size(ui->coffeePour_btn_continue, 100, 50);
    lv_obj_set_scrollbar_mode(ui->coffeePour_btn_continue, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_btn_continue, LV_STATE_DEFAULT);
    ui->coffeePour_btn_continue_label = lv_label_create(ui->coffeePour_btn_continue);
    lv_label_set_text(ui->coffeePour_btn_continue_label, "CONTINUE");
    lv_obj_set_style_pad_all(ui->coffeePour_btn_continue, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->coffeePour_btn_continue_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes coffeePour_btn_reset
    ui->coffeePour_btn_reset = lv_btn_create(ui->coffeePour);

    //Set style for coffeePour_btn_reset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_btn_reset, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->coffeePour_btn_reset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->coffeePour_btn_reset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->coffeePour_btn_reset, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->coffeePour_btn_reset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->coffeePour_btn_reset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->coffeePour_btn_reset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->coffeePour_btn_reset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->coffeePour_btn_reset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->coffeePour_btn_reset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->coffeePour_btn_reset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->coffeePour_btn_reset, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->coffeePour_btn_reset, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->coffeePour_btn_reset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->coffeePour_btn_reset, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->coffeePour_btn_reset, lv_color_make(0xD1, 0xC1, 0xB2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->coffeePour_btn_reset, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->coffeePour_btn_reset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_btn_reset, 216, 190);
    lv_obj_set_size(ui->coffeePour_btn_reset, 80, 50);
    lv_obj_set_scrollbar_mode(ui->coffeePour_btn_reset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_btn_reset, LV_STATE_DEFAULT);
    ui->coffeePour_btn_reset_label = lv_label_create(ui->coffeePour_btn_reset);
    lv_label_set_text(ui->coffeePour_btn_reset_label, "RESET");
    lv_obj_set_style_pad_all(ui->coffeePour_btn_reset, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->coffeePour_btn_reset_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes coffeePour_img_1
    ui->coffeePour_img_1 = lv_img_create(ui->coffeePour);

    //Set style for coffeePour_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->coffeePour_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->coffeePour_img_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->coffeePour_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->coffeePour_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->coffeePour_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->coffeePour_img_1, 225, 397);
    lv_obj_set_size(ui->coffeePour_img_1, 71, 65);
    lv_obj_set_scrollbar_mode(ui->coffeePour_img_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui->coffeePour_img_1, LV_STATE_DEFAULT);
    lv_obj_add_flag(ui->coffeePour_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->coffeePour_img_1, &_qrcode_alpha_71x65);
    lv_img_set_pivot(ui->coffeePour_img_1, 0, 0);
    lv_img_set_angle(ui->coffeePour_img_1, 0);

    //Init events for screen
    events_init_coffeePour(ui);
}
