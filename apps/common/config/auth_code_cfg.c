#include "app_config.h"
#include "system/includes.h"

#define AUTH_CODE_MAX_LEN (127) //auth code最大为127字节
#define AUTH_CODE_HEAD_SIZE (4)
#define AUTH_CODE_DATA_OFFSET (0x50)
#define AUTH_CODE_DATA_ADDRESS ((__FLASH_SIZE__) -256 + (AUTH_CODE_DATA_OFFSET)) //auth code地址

typedef struct {
    unsigned short codeCrc;
    unsigned short codeLen;
    unsigned char  codeData[0];
} AUTH_CODE_CFG;

int get_auth_code(char *buf, int *len)
{
    unsigned short crc;
    u32 code_addr = AUTH_CODE_DATA_ADDRESS;
    char code_buf[AUTH_CODE_MAX_LEN + AUTH_CODE_HEAD_SIZE];
    AUTH_CODE_CFG *codeCfg;

    if (NULL == buf || NULL == len) {
        return -1;
    }

    norflash_read(NULL, code_buf, (AUTH_CODE_MAX_LEN + AUTH_CODE_HEAD_SIZE), code_addr);

    codeCfg = (AUTH_CODE_CFG *)code_buf;
    if (codeCfg->codeLen > AUTH_CODE_MAX_LEN) {
        return -1;
    }

    crc = CRC16(&codeCfg->codeLen, codeCfg->codeLen + 2);
    if (crc != codeCfg->codeCrc) {
        printf("[err]crc:0x%x, codeCrc:0x%x\n", crc, codeCfg->codeCrc);
        return -1;
    }

    memcpy(buf, codeCfg->codeData, codeCfg->codeLen);
    *len = codeCfg->codeLen;

    return 0;
}
