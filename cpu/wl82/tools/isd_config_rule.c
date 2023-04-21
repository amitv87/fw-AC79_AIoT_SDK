#include "app_config.h"


// *INDENT-OFF*

/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/
/****************************注意！！！量产时不能使能CONFIG_OVERCLOCKING_ENABLE宏使用超频配置，否则后果自负**********************************/

[配置项预留起始项一_注意该位置不要定义子配置项]

[EXTRA_CFG_PARAM]
#if CONFIG_DOUBLE_BANK_ENABLE
BR22_TWS_DB=YES;
BR22_TWS_VERSION=0;
DB_UPDATE_DATA=YES;
#else
NEW_FLASH_FS=YES; [单备份模式]//单备份
#endif
#if __FLASH_SIZE__ == (1 * 1024 * 1024)
FLASH_SIZE=1M; [FLASH 总大小]
#elif __FLASH_SIZE__ == (2 * 1024 * 1024)
FLASH_SIZE=2M; [FLASH 总大小]
#elif __FLASH_SIZE__ == (4 * 1024 * 1024)
FLASH_SIZE=4M; [FLASH 总大小]
#elif __FLASH_SIZE__ == (8 * 1024 * 1024)
FLASH_SIZE=8M; [FLASH 总大小]
#elif __FLASH_SIZE__ == (16 * 1024 * 1024)
FLASH_SIZE=16M; [FLASH 总大小]
#elif __FLASH_SIZE__ == (32 * 1024 * 1024)
FLASH_SIZE=32M; [FLASH 总大小]
#elif __FLASH_SIZE__ == (64 * 1024 * 1024)
FLASH_SIZE=64M; [FLASH 总大小]
#endif

//FORCE_VM_ALIGN=YES;
CHIP_NAME=AC791N;[芯片型号选择] //8
#if (defined CONFIG_SFC_ENABLE) || (defined CONFIG_NO_SDRAM_ENABLE)
ENTRY=0x2000120; [程序入口地址 SFC模式地址]//程序入口地址
#else
ENTRY=0x4000120; [程序入口地址 SDRAM模式地址]
#endif
PID=AC791N_STORY;//长度16byte,示例：芯片封装_应用方向_方案名称
VID=0.01;
RESERVED_OPT=0;//入口地址为0x1E00120需要定义该配置项

FORCE_4K_ALIGN=YES;//用于烧写器烧写预留区文件, 需要定义该配置项
SPECIAL_OPT=0;//用于烧写器烧写预留区文件, 需要定义该配置项
//DOWNLOAD_MODEL=SERIAL;//usb
DOWNLOAD_MODEL=usb;//
SERIAL_DEVICE_NAME=JlVirtualJtagSerial;
SERIAL_BARD_RATE=1000000;
SERIAL_CMD_OPT=10;
SERIAL_CMD_RATE=100; [n*10000]
SERIAL_CMD_RES=0;
SERIAL_INIT_BAUD_RATE=9600;
LOADER_BAUD_RATE=1000000;
LOADER_ASK_BAUD_RATE=1000000;
SERIAL_SEND_KEY=YES;
BEFORE_LOADER_WAIT_TIME=150;

NEED_RESERVED_4K=YES;//关闭4K保留写NO
//#支持EFUSE 烧写到flash最后4K
//[FW_ADDITIONAL]
//FILE_LIST=(file=fw.cfg:type=0xEE)

/*#####################################################    UBOOT配置项，请勿随意调整顺序    ##################################################*/
[SYS_CFG_PARAM]
/*
#data_width[0 1 2 3 4] 3的时候uboot自动识别2或者4线
#clk [0-255]
#mode:
#	  0 RD_OUTPUT,		 1 cmd 		 1 addr
#	  1 RD_I/O,   		 1 cmd 		 x addr
#	  2 RD_I/O_CONTINUE] no_send_cmd x add
#port:
#	  0  优先选A端口  CS:PD3  CLK:PD0  D0:PD1  D1:PD2  D2:PB7  D3:PD5
#	  1  优先选B端口  CS:PA13 CLK:PD0  D0:PD1  D1:PA14 D2:PA15 D3:PD5
*/

#if defined CONFIG_FLASH_FOUR_WIDTH_ENABLE
SPI=4_1_0_0;	[width_clk_mode_port]
#else
SPI=2_1_0_0;	[width_clk_mode_port]
#endif

/*clock modules configuration*/
OSC=OSC0;             [OSC0|OSC1|OSC_RTC|HTC]
OSC_FREQ=24MHz;
OSC_HC_EN=0;
OSC_1PIN_EN=0;
#if defined CONFIG_OVERCLOCKING_ENABLE
SYS_CLK=396MHz;	       [320M 240M 192M 160M 120M 96M 48M 24M 40M 24M，当SYS_CLK为其他值时sdram时钟跟随系统时钟]
HSB_DIV=1; [高速总线时钟分频系数 HSB_DIV+1]
LSB_DIV=1; [低速总线时钟分频系数 LSB_DIV+1]
#else
SYS_CLK=320MHz;	       [320M 240M 192M 160M 120M 96M 48M 24M 40M 24M，当SYS_CLK为其他值时sdram时钟跟随系统时钟]
#if (defined CONFIG_RTC_ENABLE) && ((defined CONFIG_BOARD_7913A)||(defined CONFIG_BOARD_7915B))//7913 7915需要使用内置RTC电源模块需要P33速度低一些
HSB_DIV=2; [高速总线时钟分频系数 HSB_DIV+1]
LSB_DIV=5; [低速总线时钟分频系数 LSB_DIV+1]
#else
HSB_DIV=1; [高速总线时钟分频系数 HSB_DIV+1]
LSB_DIV=2; [低速总线时钟分频系数 LSB_DIV+1]
#endif//CONFIG_RTC_ENABLE
#endif//CONFIG_OVERCLOCKING_ENABLE

//BOOT_DELAY=100;[系统起来前增加延时配置，针对电源不稳时一些外设拉电导致系统跑飞情况，单位为毫秒]
//UTTX=PB03; [配置UBOOT调试输出Pin] //uboot串口tx
UTBD=1000000; [配置UBOOT调试波特率]//uboot串口波特率
//UTRX=PB05;串口升级[PB00 PB05 PA05]
RESET=PB01_08_0; [port口_长按时间_有效电平（长按时间有00、01、02、04、08三个值可选，单位为秒，当长按时间为00时，则关闭长按复位功能]
UPDATE_JUMP=0;

/*
#PORT_INPUT=PA03_00;	//AC79不支持PR口，PXXX_XX，如：PA05_00关上下拉，PA00_01关上拉开下拉，PA00_11开上下拉
#PORT_OUTPUT=PA04_0;	//AC79不支持PR口，PXXX_X，如：PA05_1输出高电平，PA00_0输出低电平

#0:disable
#1:PA9 PA10
#2:USB
#3:PB1 PB2
#4:PB6 PB7

#sdtap=2;
#psram=1;
*/

VLVD=4;//VDDIO_LVD挡位，0: 1.9V   1: 2.0V   2: 2.1V   3: 2.2V   4: 2.3V   5: 2.4V   6: 2.5V   7: 2.6V

//#############################################################################################################################################


#if defined CONFIG_NO_SDRAM_ENABLE
ENABLE_SDRAM=0; [使能SDRAM]
#else
ENABLE_SDRAM=1; [使能SDRAM]
#endif

//###SDRAM配置====================================================================
SDRAM_REFRESH_TIME=32;  // REFRESH CYCLES
SDRAM_REFRESH_CYCLES=4K; [4096|8192]
SDRAM_MODE=0;	[0 sdram  | 1 ddr  | 2 ddr2]
SDRAM_COLUM=0;    //      [9~10]THE COLUMN ADDRESS IS SPECIFIED BYA0-9
#if __SDRAM_SIZE__ == (8 * 1024 * 1024)
SDRAM_SIZE=8M;
#elif __SDRAM_SIZE__ == (2 * 1024 * 1024)
SDRAM_SIZE=2M;
#else
SDRAM_SIZE=0M;
#endif
#if defined CONFIG_OVERCLOCKING_ENABLE
SDRAM_PLL3_EN = 1;      [1:SDRAM时钟使用PLL3，时钟只能240M，SDK可使用USB2.0]
SDRAM_PLL3_NOUSB_EN = 0;[1:SDRAM时钟时钟PLL3，时钟跟随SDRAM_CL对应，但SDK不能使用USB2.0]
SDRAM_CL=3;      [SDRAM时钟：SYS_CLK<=240M或=320M时:[0-120M,1-160M,2-192M,3-240M,4-246M,5-252M,6-258M,7-264M,8-270M,9-276M,10-282M,11-288M]，SYS_CLK>320M并且<384M时:SDRAM时钟为SYS_CLK*1.5/2，SYS_CLK>=384M时:SDRAM时钟为SYS_CLK/2,,, SDRAM时钟极限为288M]
SDRAM_DQ_DLY_TRM=5; [SDRAM对应时钟的刷新配置：选0 刷新最快（太快影响SDRAM带宽），2-120M，3-160M，4-192M，5-240M，6->240M]
#else
SDRAM_PLL3_EN = 0;      [1:SDRAM时钟使用PLL3，时钟只能240M，SDK可使用USB2.0]
SDRAM_PLL3_NOUSB_EN = 0;[1:SDRAM时钟时钟PLL3，时钟跟随SDRAM_CL对应，但SDK不能使用USB2.0]
#if defined CONFIG_SDRAM_OVERCLOCKING_ENABLE
SDRAM_CL=3;      [SDRAM时钟：SYS_CLK<=240M或=320M时:[0-120M,1-160M,2-192M,3-240M,4-246M,5-252M,6-258M,7-264M,8-270M,9-276M,10-282M,11-288M]，SYS_CLK>320M并且<384M时:SDRAM时钟为SYS_CLK*1.5/2，SYS_CLK>=384M时:SDRAM时钟为SYS_CLK/2,,, SDRAM时钟极限为288M]
SDRAM_DQ_DLY_TRM=5; [SDRAM对应时钟的刷新配置：选0 刷新最快（太快影响SDRAM带宽），2-120M，3-160M，4-192M，5-240M，6->240M]
#else
SDRAM_CL=2;      [SDRAM时钟：SYS_CLK<=240M或=320M时:[0-120M,1-160M,2-192M,3-240M,4-246M,5-252M,6-258M,7-264M,8-270M,9-276M,10-282M,11-288M]，SYS_CLK>320M并且<384M时:SDRAM时钟为SYS_CLK*1.5/2，SYS_CLK>=384M时:SDRAM时钟为SYS_CLK/2,,, SDRAM时钟极限为288M]
SDRAM_DQ_DLY_TRM=4; [SDRAM对应时钟的刷新配置：选0 刷新最快（太快影响SDRAM带宽），2-120M，3-160M，4-192M，5-240M，6->240M]
#endif
#endif
SDRAM_WLCNT=3;		[PLL启动延时MS]
SDRAM_D_DLY=1;	[0:不测试SDRAM，1:测试SDRAM]
SDRAM_RLCNT=1;       	[PSRAM时钟分频]
SDRAM_Q_DLY=1;         [0:PSRAM单线，1:PSRAM四线]
SDRAM_PHASE=3;

//#DDR UNIVERSALLY TIMING CONFIGURATION

SDRAM_TRFC=60;      [SDRAM 时序配置]  //       REFRESH CYCLE TIME UNIT IS NS[1-63]
SDRAM_TRP=18;       [SDRAM 时序配置]    //     ROW PRECHARGE TIME UNIT IS NS[1-15]
SDRAM_TRCD=18;      [SDRAM 时序配置]   //   ROW TO COLUMN DELAY UNIT IS NS[1-15]
SDRAM_TRRD=12;      [SDRAM 时序配置]   //       ACT TO ACT DELAY TIME UNIT IS NS[1-15]
SDRAM_TWTR=20;		//			2个TCK
SDRAM_TRTW=60;			//		6个TCK
SDRAM_TWR=60;			//	0-15
SDRAM_TRC=55;	//		0-15

SDRAM_DQS_DLY_TRM=0;
SDRAM_UDQS_DLY_TRM=10;
SDRAM_LDQS_DLY_TRM=10;
SDRAM_DQ_DLY_INNER_TRM=0;

/*
###########################################
#
# 支持当前SDK最低烧写器测试盒工具版本
#
*/
[TOOL_CONFIG]
1TO2_MIN_VER=2.24.5;
1TO8_MIN_VER=3.0.35;
BTBOX_MIN_VER=1.2.4.f;
//###########################################

/*
########flash空间使用配置区域###############################################
#PDCTNAME:    产品名，对应此代码，用于标识产品，升级时可以选择匹配产品名
#BOOT_FIRST:  1=代码更新后，提示APP是第一次启动；0=代码更新后，不提示
#UPVR_CTL：   0：不允许高版本升级低版本   1：允许高版本升级低版本
#XXXX_ADR:    区域起始地址	AUTO：由工具自动分配起始地址
#XXXX_LEN:    区域长度		CODE_LEN：代码长度
#XXXX_OPT:    区域操作属性
#
#
#
#操作符说明  OPT:
#	0:  下载代码时擦除指定区域
#	1:  下载代码时不操作指定区域
#	2:  下载代码时给指定区域加上保护
############################################################################
*/
[RESERVED_CONFIG]
//#升级之后需要保留VM数据，在生成升级文件时需要设置VM_OPT=1
VM_ADR=0; [设置VM]
VM_LEN=32K;
VM_OPT=0;

BTIF_ADR=AUTO; [设置资源]
BTIF_LEN=0x1000;
BTIF_OPT=1;

//#第三方云平台profile
#if defined CONFIG_SERVER_ASSIGN_PROFILE
PROFILE_ADR=AUTO; [第三方云平台profile]
PROFILE_LEN=0x1000;
PROFILE_OPT=1;
#endif

//#思必驰打断唤醒profile
#if (defined CONFIG_ASR_ALGORITHM) && (CONFIG_ASR_ALGORITHM == AISP_ALGORITHM)
AISP_ADR=AUTO; [思必驰打断唤醒profile]
AISP_LEN=0x1000;
AISP_OPT=1;
#endif

#if defined CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH
LOG_ADR=AUTO; [异常打印信息]
LOG_LEN=0x1000;
LOG_OPT=0;
#endif

//#保留客户使用
EXIF_ADR=AUTO;[保留客户使用 也可自定义名字 参考example文档使用]
EXIF_LEN=0x1000;
EXIF_OPT=1;

#if defined CONFIG_AUDIO_ENABLE && defined CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_ZONE
AUPACKRES_FILE=packres/AUPACKRES;
AUPACKRES_ADR=AUTO; [请根据编译后FLASH INFO打印的实际地址填写,比如0x59a000]
AUPACKRES_LEN=0; [更新提示音资源打包后必须更新此实际长度,比如0x141000,建议根据后续资源升级的需求预留好空间]
AUPACKRES_OPT=1;
#endif

#if defined CONFIG_UI_ENABLE && defined CONFIG_UI_FILE_SAVE_IN_RESERVED_ZONE
UIPACKRES_FILE=packres/UIPACKRES;
UIPACKRES_ADR=AUTO; [请根据编译后FLASH INFO打印的实际地址填写,比如0x6db000]
UIPACKRES_LEN=0; [更新UI资源打包后必须更新此实际长度,比如0x123000, 建议根据后续资源升级的需求预留好空间]
UIPACKRES_OPT=1;
#endif

PRCT_ADR=0;
PRCT_LEN=CODE_LEN;
PRCT_OPT=2;

/***************资源文件打包 请阅读以下信息******************************/
//packers文件夹下会生成AUPACKRES,UIPACKRES这两个包是资源文件打包好的包需要
//根据实际大小填写AUPACKRES_ADR,AUPACKRES_LEN,
//AUPACKRES_ADR 配置 AUTO 第一次下载后会下载不进 需要根据FLASH INFO打印的实际地址填写
//例如AUPACKRES 378KB = 0x5e800 实际填大小可以填大一些 AUPACKRES_LEN = 0x5f000
//AUPACKRES_OPT为下载是否需要擦除
//#升级后不可更变的资源
[RESERVED_EXPAND_CONFIG]
#if defined CONFIG_AUDIO_ENABLE && defined CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
AUPACKRES_FILE=packres/AUPACKRES; [烧录后不可升级的资源]
AUPACKRES_ADR=AUTO; [请根据编译后FLASH INFO打印的实际地址填写,比如0x59b000]
AUPACKRES_LEN=0; [更新提示音资源打包后必须更新此实际长度,比如0x141000]
AUPACKRES_OPT=1;
#endif

#if defined CONFIG_UI_ENABLE && defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
UIPACKRES_FILE=packres/UIPACKRES; [烧录后不可升级的资源]
UIPACKRES_ADR=AUTO; [请根据编译后FLASH INFO打印的实际地址填写,比如0x6dc000]
UIPACKRES_LEN=0; [更新UI资源打包后必须更新此实际长度,比如0x123000]
UIPACKRES_OPT=1;
#endif

/* fixed.mp3_FILE=fixed_res/fixed.mp3; [烧录后不可升级的资源] */
/* fixed.mp3_ADR=AUTO; */
/* fixed.mp3_LEN=0x4000; */
/* fixed.mp3_OPT=1; */

#if defined TCFG_EXTFLASH_ENABLE
//截取flash的一段空间作为extflash设备
EXTFLASH_ADR=AUTO;
EXTFLASH_LEN=0x400000;
EXTFLASH_OPT=1;
#endif

[BURNER_CONFIG]
SIZE=32;

