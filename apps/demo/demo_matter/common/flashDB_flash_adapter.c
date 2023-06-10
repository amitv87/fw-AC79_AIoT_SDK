#include "system/includes.h"
#include "asm/sfc_norflash_api.h"
#include <fal.h>

#define USER_FLASH_SPACE_PATH "mnt/sdfile/EXT_RESERVED/user"
#define FLASHDB_SIZE (16 * 1024)

static u32 flashDB_addr;

struct vfs_attr {
    u8 attr;					/*!< 文件属性标志位 */
    u32 fsize;					/*!< 文件大小 */
    u32 sclust;					/*!< 最小分配单元 */
    struct sys_time crt_time;	/*!< 文件创建时间 */
    struct sys_time wrt_time;	/*!< 文件最后修改时间 */
    struct sys_time acc_time;   /*!< 文件最后访问时间 */
};

static int flashDB_norflash_init(void)
{
    u32 addr;
    FILE *profile_fp = fopen(USER_FLASH_SPACE_PATH, "r");
    if (profile_fp == NULL) {
        puts("__flashDB_mount ERROR!!!\r\n");
        return -1;
    }
    struct vfs_attr file_attr;
    fget_attrs(profile_fp, &file_attr);
    addr = sdfile_cpu_addr2flash_addr(file_attr.sclust);
    fclose(profile_fp);
    flashDB_addr = addr;

    printf("__flashDB_mount_addr = 0x%x, size = 0x%x \r\n", addr, file_attr.fsize);
    if (file_attr.fsize < FLASHDB_SIZE) {
        while (1) {
            printf("USER_LEN < FLASHDB_SIZE\n");
            os_time_dly(30);
        }
    }
    return 0;
}

static int flashDB_norflash_read(long offset, u8 *buf, u32 size)
{
    return norflash_read(NULL, buf, size, flashDB_addr + offset);
}

static int flashDB_norflash_write(long offset, u8 *buf, u32 size)
{
    return norflash_write(NULL, buf, size, flashDB_addr + offset);
}

static int flashDB_norflash_erase(long offset, u32 size)
{
    long addr = 0;
    u32	 erase_addr, erase_block = 0, i = 0;

    addr = flashDB_addr + offset;

    if (size % (4 * 1024)) {
        ASSERT(0, "[flashDB]4k byte alignment is required\n");
    } else {
        erase_block = (size / (4 * 1024));
    }

    for (i = 1, erase_addr = addr; i <= erase_block; i++, erase_addr += 4 * 1024) {
        norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, erase_addr);
    }

    return size;
}

const struct fal_flash_dev AC79_onchip_norflash = {
    .name       = "AC79_onchip_norflash",
    .addr       = 0,
    .len        = FLASHDB_SIZE,    //需要根据 isd_config.ini 的 EXIF_LEN 配置
    .blk_size   = 4 * 1024,
    .ops        = {flashDB_norflash_init, flashDB_norflash_read, flashDB_norflash_write, flashDB_norflash_erase},
    .write_gran = 1
};

