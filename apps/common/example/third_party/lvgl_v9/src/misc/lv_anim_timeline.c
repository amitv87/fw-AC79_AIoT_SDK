/**
 * @file lv_anim_timeline.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_assert.h"
#include "lv_anim_timeline.h"
#include "../stdlib/lv_mem.h"
#include "../stdlib/lv_string.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_anim_timeline_virtual_exec_cb(void *var, int32_t v);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_anim_timeline_t *lv_anim_timeline_create(void)
{
    lv_anim_timeline_t *at = lv_malloc_zeroed(sizeof(lv_anim_timeline_t));
    LV_ASSERT_MALLOC(at);
    return at;
}

void lv_anim_timeline_delete(lv_anim_timeline_t *at)
{
    LV_ASSERT_NULL(at);

    lv_anim_timeline_stop(at);

    lv_free(at->anim_dsc);
    lv_free(at);
}

void lv_anim_timeline_add(lv_anim_timeline_t *at, uint32_t start_time, lv_anim_t *a)
{
    LV_ASSERT_NULL(at);

    at->anim_dsc_cnt++;
    at->anim_dsc = lv_realloc(at->anim_dsc, at->anim_dsc_cnt * sizeof(lv_anim_timeline_dsc_t));

    LV_ASSERT_MALLOC(at->anim_dsc);

    at->anim_dsc[at->anim_dsc_cnt - 1].anim = *a;
    at->anim_dsc[at->anim_dsc_cnt - 1].start_time = start_time;

    /*Add default var and virtual exec_cb, used to delete animation.*/
    if (a->var == NULL && a->exec_cb == NULL && a->custom_exec_cb == NULL) {
        at->anim_dsc[at->anim_dsc_cnt - 1].anim.var = at;
        at->anim_dsc[at->anim_dsc_cnt - 1].anim.exec_cb = lv_anim_timeline_virtual_exec_cb;
    }
}

uint32_t lv_anim_timeline_start(lv_anim_timeline_t *at)
{
    LV_ASSERT_NULL(at);

    const uint32_t playtime = lv_anim_timeline_get_playtime(at);
    bool reverse = at->reverse;

    for (uint32_t i = 0; i < at->anim_dsc_cnt; i++) {
        lv_anim_t a = at->anim_dsc[i].anim;
        uint32_t start_time = at->anim_dsc[i].start_time;

        if (reverse) {
            int32_t temp = a.start_value;
            a.start_value = a.end_value;
            a.end_value = temp;
            lv_anim_set_delay(&a, playtime - (start_time + a.duration));
        } else {
            lv_anim_set_delay(&a, start_time);
        }

        lv_anim_start(&a);
    }

    return playtime;
}

void lv_anim_timeline_stop(lv_anim_timeline_t *at)
{
    LV_ASSERT_NULL(at);

    for (uint32_t i = 0; i < at->anim_dsc_cnt; i++) {
        lv_anim_t *a = &(at->anim_dsc[i].anim);
        if (a->exec_cb) {
            lv_anim_delete(a->var, a->exec_cb);
        } else {
            lv_anim_delete(a->var, NULL);
        }
    }
}

void lv_anim_timeline_set_reverse(lv_anim_timeline_t *at, bool reverse)
{
    LV_ASSERT_NULL(at);
    at->reverse = reverse;
}

void lv_anim_timeline_set_progress(lv_anim_timeline_t *at, uint16_t progress)
{
    LV_ASSERT_NULL(at);

    const uint32_t playtime = lv_anim_timeline_get_playtime(at);
    const uint32_t act_time = progress * playtime / 0xFFFF;

    for (uint32_t i = 0; i < at->anim_dsc_cnt; i++) {
        lv_anim_t *a = &(at->anim_dsc[i].anim);

        if (a->exec_cb == NULL && a->custom_exec_cb == NULL) {
            continue;
        }

        uint32_t start_time = at->anim_dsc[i].start_time;
        int32_t value = 0;
        if (act_time < start_time && a->early_apply) {
            value = a->start_value;
            if (a->exec_cb) {
                a->exec_cb(a->var, value);
            }
            if (a->custom_exec_cb) {
                a->custom_exec_cb(a, value);
            }
        } else if (act_time >= start_time && act_time <= (start_time + a->duration)) {
            a->act_time = act_time - start_time;
            value = a->path_cb(a);
            if (a->exec_cb) {
                a->exec_cb(a->var, value);
            }
            if (a->custom_exec_cb) {
                a->custom_exec_cb(a, value);
            }
        } else if (act_time > start_time + a->duration) {
            value = a->end_value;
            if (a->exec_cb) {
                a->exec_cb(a->var, value);
            }
            if (a->custom_exec_cb) {
                a->custom_exec_cb(a, value);
            }
        }
    }
}

uint32_t lv_anim_timeline_get_playtime(lv_anim_timeline_t *at)
{
    LV_ASSERT_NULL(at);

    uint32_t playtime = 0;
    for (uint32_t i = 0; i < at->anim_dsc_cnt; i++) {
        uint32_t end = lv_anim_get_playtime(&at->anim_dsc[i].anim);
        if (end == LV_ANIM_PLAYTIME_INFINITE) {
            return end;
        }
        end += at->anim_dsc[i].start_time;
        if (end > playtime) {
            playtime = end;
        }
    }

    return playtime;
}

bool lv_anim_timeline_get_reverse(lv_anim_timeline_t *at)
{
    LV_ASSERT_NULL(at);
    return at->reverse;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_anim_timeline_virtual_exec_cb(void *var, int32_t v)
{
    LV_UNUSED(var);
    LV_UNUSED(v);
}