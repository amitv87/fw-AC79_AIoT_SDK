/**
 * @file lv_port_fs_templ.h
 *
 */

/*Copy this file as "lv_port_fs.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_FS_TEMPL_H
#define LV_PORT_FS_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*******************JL************************/
typedef struct {
    uint8_t res_type;
    uint8_t res_compress;
    uint16_t res_crc;
    uint32_t res_size;
    uint32_t nop;
} JLBinResourceHeader;

typedef struct {
    char JL[2];
    uint16_t version;
    JLBinResourceHeader jl_header;
    void *resource;
} JLBinResource;

typedef struct {
    uint8_t first_byte;
    uint8_t second_byte;
} JL_get_type;
/*******************JL************************/
/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_port_fs_init(void);

/*JL获取.bin文件位图数据接口*/
//get lv_img_dsc_t结构体数据
lv_res_t lv_get_img_dsc_bin(const char *src, lv_img_dsc_t *bin_dsc);
lv_res_t lv_get_JLBinResource(const char *src, JLBinResource *bin_res);
lv_res_t lv_get_type_bin(const char *src, JL_get_type *type);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_FS_TEMPL_H*/

#endif /*Disable/Enable content*/
