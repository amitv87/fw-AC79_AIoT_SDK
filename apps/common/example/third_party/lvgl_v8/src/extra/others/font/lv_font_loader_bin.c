#define BOOL_DEFINE_CONFLICT
#include "lv_font_loader_bin.h"
#include "lv_port_fs.h"
#include "fs/fs.h"

#define FPGA_TEST 0

#if FPGA_TEST
#define CONFIG_FONT_BIN_PATH "storage/sd0/C/" //SD卡资源路径
uint8_t __attribute__((aligned(4)))ptr[1024 * 6]  = {0}; //根据字体bin文件调整大小

lv_res_t lv_load_font_from_sd(const char *src, char *ptr, int len) //从SD卡读取文件数据
{
    char route[128] = CONFIG_FONT_BIN_PATH;
    strcat(route, src);
    FILE *profile_fp = fopen(route, "r");

    if (profile_fp == NULL) {
        LV_LOG_ERROR("user_get_sd_file ERROR!!!\r\n");
        return LV_RES_INV;
    }

    fread(profile_fp, ptr, len);
    fclose(profile_fp);
    return LV_RES_OK;
}

#else

#define CONFIG_FONT_BIN_PATH "mnt/sdfile/res/" //flash资源路径
//通过文件名获取到flash地址
static uint8_t *lv_load_font_from_flash(const char *src)
{
    char route[128] = CONFIG_FONT_BIN_PATH;
    strcat(route, src);
    u32 addr;
    FILE *profile_fp = fopen(route, "r");
    if (profile_fp == NULL) {
        LV_LOG_ERROR("user_get_flash_addr ERROR!!!");
        return LV_RES_INV;
    }
    struct vfs_attr file_attr;
    fget_attrs(profile_fp, &file_attr);
    fclose(profile_fp);
    uint8_t *test_addr = (uint8_t *)file_attr.sclust;
    return test_addr;
}
#endif

lv_font_t *lv_font_load_bin(const char *font_name)
{

#if FPGA_TEST
    lv_load_font_from_sd(font_name, ptr, sizeof(ptr)); //从sd卡读取数据
#else

    uint8_t *ptr = lv_load_font_from_flash(font_name);
    if (ptr == NULL) {
        LV_LOG_ERROR("lv load file data from flash error");
        return NULL;
    }
#endif

    //JLBinResource
    JLBinResource *JL_head = ptr;
    //lv_font_bin_offset
    lv_font_bin_offset *offset = (lv_font_bin_offset *)(ptr + sizeof(JLBinResource));
    //lv_offset_cmaps_list
    lv_offset_cmaps_list *offset_cmaps_list_arr = (lv_offset_cmaps_list *)(ptr + sizeof(JLBinResource) + sizeof(lv_font_bin_offset));
    //lv_font_t
    lv_font_t *font = malloc(sizeof(lv_font_t));
    if (font == NULL) {
        LV_LOG_ERROR("[font_loader] user_malloc_ERROR!!!\r\n");
        return NULL;
    }
    memcpy(font, (ptr + offset->offset_font), sizeof(lv_font_t));
    font->get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt;
    font->get_glyph_bitmap = lv_font_get_bitmap_fmt_txt;

    //font_dsc
    lv_font_fmt_txt_dsc_t *font_dsc = malloc(sizeof(lv_font_fmt_txt_dsc_t));
    if (font_dsc == NULL) {
        LV_LOG_ERROR("[font_loader] user_malloc_ERROR!!!\r\n");
        return NULL;
    }
    memcpy(font_dsc, (ptr + offset->offset_dsc), sizeof(lv_font_fmt_txt_dsc_t));
    font->dsc = font_dsc;
    font_dsc->glyph_bitmap = (uint8_t *)(ptr + offset->offset_glyph_bitmap);
    font_dsc->glyph_dsc = (uint8_t *)(ptr + offset->offset_glyph_dsc);

    //cmaps
    lv_font_fmt_txt_cmap_t *cmaps =  malloc(sizeof(lv_font_fmt_txt_cmap_t) * (font_dsc->cmap_num));
    if (cmaps == NULL) {
        LV_LOG_ERROR("[font_loader] user_malloc_ERROR!!!\r\n");
        return NULL;
    }
    memcpy(cmaps, (ptr + offset->offset_cmaps), sizeof(lv_font_fmt_txt_cmap_t) * (font_dsc->cmap_num));
    for (int i = 0; i < font_dsc->cmap_num; i++) {
        cmaps[i].unicode_list = (uint16_t *)(ptr + offset_cmaps_list_arr[i].offset_unicode_list_arr);
        cmaps[i].glyph_id_ofs_list = (ptr + offset_cmaps_list_arr[i].offset_glyph_id_ofs_list_arr);
    }
    font_dsc->cmaps = (lv_font_fmt_txt_cmap_t *)cmaps;

    //kern_dsc
    if (offset->offset_kern_dsc_class != offset->offset_values) { //kern_dsc == NULL
        if (font_dsc->kern_classes) {
            lv_font_fmt_txt_kern_classes_t *kern_classes =  malloc(sizeof(lv_font_fmt_txt_kern_classes_t));
            if (kern_classes == NULL) {
                LV_LOG_ERROR("[font_loader] user_malloc_ERROR!!!\r\n");
                return NULL;
            }
            memcpy(kern_classes, (ptr + offset->offset_kern_dsc_class), sizeof(lv_font_fmt_txt_kern_classes_t));
            kern_classes->class_pair_values = (int8_t *)(ptr +  offset->offset_class_pair_values);
            kern_classes->left_class_mapping = (uint8_t *)(ptr +  offset->offset_left_class_mapping);
            kern_classes->right_class_mapping = (uint8_t *)(ptr + offset->offset_right_class_mapping);
            font_dsc->kern_dsc = kern_classes;
        } else {
            lv_font_fmt_txt_kern_pair_t *kern_pairs =  malloc(sizeof(lv_font_fmt_txt_kern_pair_t));
            if (kern_pairs == NULL) {
                LV_LOG_ERROR("[font_loader] user_malloc_ERROR!!!\r\n");
                return NULL;
            }
            memcpy(kern_pairs, (ptr + offset->offset_kern_dsc_pair), sizeof(lv_font_fmt_txt_kern_pair_t));
            kern_pairs->glyph_ids = (ptr + offset->offset_glyph_ids);
            kern_pairs->values = (int8_t *)(ptr + offset->offset_values);
            font_dsc->kern_dsc = kern_pairs;
        }
    } else {
        font_dsc->kern_dsc = NULL;
    }
    //cache
    font_dsc->cache = NULL;

    return font;
}

/**
 * Frees the memory allocated by the `lv_load_font_from_flash()` function
 * @param font lv_font_t object created by the lv_font_load function
 */

void lv_font_free_bin(lv_font_t *font)
{
    if (NULL != font) {
        lv_font_fmt_txt_dsc_t *dsc = (lv_font_fmt_txt_dsc_t *)font->dsc;
        if (NULL != dsc) {
            if (NULL != dsc->kern_dsc) {
                free(dsc->kern_dsc);
            }
            if (NULL != dsc->cmaps) {
                free(dsc->cmaps);
            }
            free(dsc);
        }
        free(font);
    }
}

