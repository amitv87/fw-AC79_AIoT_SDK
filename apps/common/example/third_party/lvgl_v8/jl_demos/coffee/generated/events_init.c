/*Generate Code, Do NOT Edit!*/
#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

static int32_t current_value = 0;
void events_init(lv_ui *ui)
{
}

static void coffeePour_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_animimg_t *animimg1 = (lv_animimg_t *)guider_ui.coffeePour_animimg_coffee;
            lv_anim_set_values(&animimg1->anim, 0, 31);
            lv_animimg_start(guider_ui.coffeePour_animimg_coffee);
        }
    }
    break;
    default:
        break;
    }
}

static void coffeePour_btn_full_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_animimg_start(guider_ui.coffeePour_animimg_coffee);
        }
    }
    break;
    default:
        break;
    }
}

static void coffeePour_btn_stop_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            if (lv_anim_get(guider_ui.coffeePour_animimg_coffee, NULL) != NULL) {
                lv_anim_t *anim_status = lv_anim_get(guider_ui.coffeePour_animimg_coffee, NULL);
                current_value = anim_status->current_value;
                lv_anim_del(guider_ui.coffeePour_animimg_coffee, NULL);
            }

        }
    }
    break;
    default:
        break;
    }
}

static void coffeePour_btn_continue_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;
            lv_animimg_t *animimg1 = (lv_animimg_t *)guider_ui.coffeePour_animimg_coffee;
            lv_anim_set_values(&animimg1->anim, current_value, 31);
            lv_animimg_set_repeat_count(guider_ui.coffeePour_animimg_coffee, 1);
            lv_animimg_start(guider_ui.coffeePour_animimg_coffee);
            current_value = 0;
        }
    }
    break;
    default:
        break;
    }
}

static void coffeePour_btn_reset_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code
        {
            lv_obj_t *dest = src;

            lv_event_code_t code = lv_event_get_code(e);

            switch (code) {
            case LV_EVENT_CLICKED: {
                lv_animimg_t *animimg1 = (lv_animimg_t *)guider_ui.coffeePour_animimg_coffee;
                lv_anim_set_values(&animimg1->anim, 0, 1);
                lv_animimg_start(guider_ui.coffeePour_animimg_coffee);
                break;
            }
            default:
                break;
            }
        }
    }
    break;
    default:
        break;
    }
}

void events_init_coffeePour(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->coffeePour, coffeePour_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->coffeePour_btn_full, coffeePour_btn_full_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->coffeePour_btn_stop, coffeePour_btn_stop_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->coffeePour_btn_continue, coffeePour_btn_continue_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->coffeePour_btn_reset, coffeePour_btn_reset_event_handler, LV_EVENT_ALL, ui);
}
