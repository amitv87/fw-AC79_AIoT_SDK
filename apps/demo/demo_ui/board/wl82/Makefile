
# make 编译并下载
# make VERBOSE=1 显示编译详细过程
# make clean 清除编译临时文件
#
# 注意： Linux 下编译方式：
#     1. 从 http://pkgman.jieliapp.com/doc/all 处找到下载链接
#     2. 下载后，解压到 /opt/jieli 目录下，保证
#       /opt/jieli/common/bin/clang 存在（注意目录层次）
#     3. 确认 ulimit -n 的结果足够大（建议大于8096），否则链接可能会因为打开文件太多而失败
#       可以通过 ulimit -n 8096 来设置一个较大的值
#

# 工具路径设置
ifeq ($(OS), Windows_NT)
# Windows 下工具链位置
TOOL_DIR := C:/JL/pi32/bin
CC    := clang.exe
CXX   := clang.exe
LD    := pi32v2-lto-wrapper.exe
AR    := llvm-ar.exe
MKDIR := mkdir_win -p
RM    := rm -rf

SYS_LIB_DIR := 
SYS_INC_DIR := 
EXT_CFLAGS  := # Windows 下不需要 -D__SHELL__
export PATH:=$(TOOL_DIR);$(PATH)

## 后处理脚本
FIXBAT          := ..\..\..\..\..\tools\utils\fixbat.exe # 用于处理 utf8->gbk 编码问题
POST_SCRIPT     := ../../../../../cpu/wl82/tools/download.bat
RUN_POST_SCRIPT := ..\..\..\..\..\cpu\wl82\tools\download.bat
else
# Linux 下工具链位置
TOOL_DIR := /opt/jieli/pi32v2/bin
CC    := clang
CXX   := clang
LD    := lto-wrapper
AR    := lto-ar
MKDIR := mkdir -p
RM    := rm -rf
export OBJDUMP := $(TOOL_DIR)/objdump
export OBJCOPY := $(TOOL_DIR)/objcopy
export OBJSIZEDUMP := $(TOOL_DIR)/objsizedump

SYS_LIB_DIR := $(TOOL_DIR)/../lib/r3
SYS_INC_DIR := $(TOOL_DIR)/../include
EXT_CFLAGS  := -D__SHELL__ # Linux 下需要这个保证正确处理 download.c
export PATH:=$(TOOL_DIR):$(PATH)

## 后处理脚本
FIXBAT          := touch # Linux下不需要处理 bat 编码问题
POST_SCRIPT     := ../../../../../cpu/wl82/tools/download.sh
RUN_POST_SCRIPT := bash $(POST_SCRIPT)
endif

CC  := $(TOOL_DIR)/$(CC)
CXX := $(TOOL_DIR)/$(CXX)
LD  := $(TOOL_DIR)/$(LD)
AR  := $(TOOL_DIR)/$(AR)
# 输出文件设置
OUT_ELF   := ../../../../../cpu/wl82/tools/sdk.elf
OBJ_FILE  := $(OUT_ELF).objs.txt
# 编译路径设置
BUILD_DIR := objs
# 工程路径前缀
ROOT_PREFIX := ../../../../..

# 编译参数设置
CFLAGS := \
	-target pi32v2 \
	-integrated-as \
	-mcpu=r3 \
	-mfprev1 \
	-Wuninitialized \
	-Wno-invalid-noreturn \
	-fno-common \
	-integrated-as \
	-Ofast \
	-g \
	-flto \
	-fallow-pointer-null \
	-fprefer-gnu-section \
	-femulated-tls \
	-Wno-shift-negative-value \
	-Wframe-larger-than=2560 \
	-mllvm -pi32v2-large-program=true \
	-fms-extensions \
	-w \
	-fno-unwind-tables \
	-ffunction-sections \
	-fdata-sections \
	-fmessage-length=0 \


# C++额外的编译参数
CXXFLAGS := \
	-std=gnu++14 \
	-fno-exceptions \
	-fno-rtti \


# 宏定义
DEFINES := \
	-DSUPPORT_MS_EXTENSIONS \
	-DCONFIG_RELEASE_ENABLE \
	-DCONFIG_CPU_WL82 \
	-DCONFIG_FREE_RTOS_ENABLE \
	-DCONFIG_THREAD_ENABLE \
	-DCONFIG_AUDIO_ONCHIP \
	-D__GCC_PI32V2__ \
	-DCONFIG_NEW_ECC_ENABLE \
	-DCONFIG_EQ_SUPPORT_ASYNC \
	-DEQ_CORE_V1 \
	-DCONFIG_UI_ENABLE \
	-DCONFIG_VIDEO_ENABLE=1 \
	-DCONFIG_VIDEO0_ENABLE=1 \
	-DCONFIG_SFC_ENABLE \
	-DCONFIG_CXX_SUPPORT \
	-DCONFIG_JLFAT_ENABLE \
	-DEVENT_HANDLER_NUM_CONFIG=2 \
	-DEVENT_TOUCH_ENABLE_CONFIG=0 \
	-DEVENT_POOL_SIZE_CONFIG=256 \
	-DCONFIG_EVENT_KEY_MAP_ENABLE=0 \
	-DTIMER_POOL_NUM_CONFIG=15 \
	-DAPP_ASYNC_POOL_NUM_CONFIG=0 \
	-DVFS_ENABLE=1 \
	-DUSE_SDFILE_NEW=1 \
	-DSDFILE_STORAGE=1 \
	-DVFS_FILE_POOL_NUM_CONFIG=8 \
	-DVM_MAX_PAGE_ALIGN_SIZE_CONFIG=64*1024 \
	-DVM_MAX_SECTOR_ALIGN_SIZE_CONFIG=64*1024 \
	-DVM_ITEM_MAX_NUM=256 \
	-DCONFIG_UPDATA_ENABLE \
	-DCONFIG_OTA_UPDATA_ENABLE \
	-DCONFIG_ITEM_FORMAT_VM \
	-DRLOTTIE_COMMIT_HASH=\"056c0a1bc14bcee6f6b1a821013872a1228b0fa9\" \
	-DFREETYPE_COMMIT_HASH=\"45903920b984540bb629bc89f4c010159c23a89a\" \
	-DFT2_BUILD_LIBRARY \
	-DLVGL_COMMIT_HASH=\"release/v8.3_39687e808fd0b84357f646ad390a0eb26764cb3f\" \
	-D_XOPEN_SOURCE=700 \
	-D_GNU_SOURCE \
	-D__ELF__ \


DEFINES += $(EXT_CFLAGS) # 额外的一些定义

# 头文件搜索路径
INCLUDES := \
	-I../../../../../include_lib/c++ \
	-I../../../../../include_lib/c++/include \
	-I../../../../../include_lib/newlib/include \
	-I../../../../../include_lib/c++/simple_pthread \
	-I../../../../../include_lib \
	-I../../../../../include_lib/driver \
	-I../../../../../include_lib/driver/device \
	-I../../../../../include_lib/driver/cpu/wl82 \
	-I../../../../../include_lib/system \
	-I../../../../../include_lib/system/generic \
	-I../../../../../include_lib/btctrler \
	-I../../../../../include_lib/btctrler/port/wl82 \
	-I../../../../../include_lib/update \
	-I../../../../../include_lib/btstack/third_party/common \
	-I../../../../../include_lib/btstack/third_party/rcsp \
	-I../../../../../include_lib/utils \
	-I../../../../../include_lib/utils/syscfg \
	-I../../../../../include_lib/utils/event \
	-I../../../../../include_lib/media \
	-I../../../../../include_lib/media/cpu/wl82 \
	-I../../../../../apps/demo/demo_ui/include \
	-I../../../../../include_lib/driver/device/video \
	-I../../../../../apps \
	-I../../../../../apps/common/config/include \
	-I../../../../../apps/common/system \
	-I../../../../../apps/common/system/perf_counter \
	-I../../../../../apps/demo/demo_ui \
	-I../../../../../include_lib/server \
	-I../../../../../include_lib/system/os \
	-I../../../../../apps/common \
	-I../../../../../apps/common/ui/include \
	-I../../../../../include_lib/utils/ui \
	-I../../../../../apps/common/example/third_party/rlottie_impl/inc \
	-I../../../../../apps/common/example/third_party/rlottie_impl/src/vector \
	-I../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype \
	-I../../../../../apps/common/example/third_party/freetype/include \
	-I../../../../../apps/common/example/third_party/lvgl_v8 \
	-I../../../../../apps/common/example/third_party/lvgl_v8/examples/porting \
	-I../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/freetype \
	-I../../../../../apps/common/example/third_party \
	-I../../../../../apps/common/example/third_party/lvgl_v8/demos \
	-I../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark \
	-I../../../../../apps/common/example/third_party/lvgl_v8/demos/keypad_encoder \
	-I../../../../../apps/common/example/third_party/lvgl_v8/demos/music \
	-I../../../../../apps/common/example/third_party/lvgl_v8/demos/stress \
	-I../../../../../apps/common/example/third_party/lvgl_v8/demos/widgets \
	-I../../../../../apps/common/example/third_party/lvgl_v8/src \
	-I../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical \


# 需要编译的 .c 文件
c_SRC_FILES := \
	../../../../../apps/common/c++/cpp_run_init.c \
	../../../../../apps/common/camera/byd20a6/byd20a6.c \
	../../../../../apps/common/camera/byd30a2/byd30a2.c \
	../../../../../apps/common/camera/byd3720/byd3720.c \
	../../../../../apps/common/camera/byd3901/byd3901.c \
	../../../../../apps/common/camera/byd3a03/byd3a03.c \
	../../../../../apps/common/camera/gc0307_dvp/gc0307.c \
	../../../../../apps/common/camera/gc0308_dvp/gc0308.c \
	../../../../../apps/common/camera/gc0309_dvp/gc0309.c \
	../../../../../apps/common/camera/gc0310_spi/gc0310.c \
	../../../../../apps/common/camera/gc0312_dvp/gc0312.c \
	../../../../../apps/common/camera/gc0328_dvp/gc0328.c \
	../../../../../apps/common/camera/gc0329_dvp/gc0329.c \
	../../../../../apps/common/camera/gc032a_dvp/gc032a.c \
	../../../../../apps/common/camera/gc2035_dvp/gc2035.c \
	../../../../../apps/common/camera/gc2145_dvp/gc2145.c \
	../../../../../apps/common/camera/h7375s/h7375s.c \
	../../../../../apps/common/camera/ov7670_dvp/ov7670.c \
	../../../../../apps/common/camera/pr2000k/pr2000k.c \
	../../../../../apps/common/camera/xc7011_dvp/xc7011.c \
	../../../../../apps/common/config/log_config/lib_driver_config.c \
	../../../../../apps/common/config/log_config/lib_system_config.c \
	../../../../../apps/common/config/log_config/lib_update_config.c \
	../../../../../apps/common/config/user_cfg.c \
	../../../../../apps/common/debug/debug.c \
	../../../../../apps/common/debug/debug_user.c \
	../../../../../apps/common/example/third_party/freetype/src/autofit/autofit.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftbase.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftbitmap.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftdebug.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftglyph.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftinit.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftmm.c \
	../../../../../apps/common/example/third_party/freetype/src/base/ftsystem.c \
	../../../../../apps/common/example/third_party/freetype/src/bdf/bdf.c \
	../../../../../apps/common/example/third_party/freetype/src/bzip2/ftbzip2.c \
	../../../../../apps/common/example/third_party/freetype/src/cache/ftcache.c \
	../../../../../apps/common/example/third_party/freetype/src/cff/cff.c \
	../../../../../apps/common/example/third_party/freetype/src/cid/type1cid.c \
	../../../../../apps/common/example/third_party/freetype/src/dlg/dlgwrap.c \
	../../../../../apps/common/example/third_party/freetype/src/gxvalid/gxvalid.c \
	../../../../../apps/common/example/third_party/freetype/src/gzip/ftgzip.c \
	../../../../../apps/common/example/third_party/freetype/src/lzw/ftlzw.c \
	../../../../../apps/common/example/third_party/freetype/src/otvalid/otvalid.c \
	../../../../../apps/common/example/third_party/freetype/src/pcf/pcf.c \
	../../../../../apps/common/example/third_party/freetype/src/pfr/pfr.c \
	../../../../../apps/common/example/third_party/freetype/src/psaux/psaux.c \
	../../../../../apps/common/example/third_party/freetype/src/pshinter/pshinter.c \
	../../../../../apps/common/example/third_party/freetype/src/psnames/psnames.c \
	../../../../../apps/common/example/third_party/freetype/src/raster/raster.c \
	../../../../../apps/common/example/third_party/freetype/src/sdf/sdf.c \
	../../../../../apps/common/example/third_party/freetype/src/sfnt/sfnt.c \
	../../../../../apps/common/example/third_party/freetype/src/smooth/smooth.c \
	../../../../../apps/common/example/third_party/freetype/src/svg/svg.c \
	../../../../../apps/common/example/third_party/freetype/src/truetype/truetype.c \
	../../../../../apps/common/example/third_party/freetype/src/type1/type1.c \
	../../../../../apps/common/example/third_party/freetype/src/type42/type42.c \
	../../../../../apps/common/example/third_party/freetype/src/winfonts/winfnt.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/components/ui_comp_hook.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/fonts/ui_font_Big_Number.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/fonts/ui_font_Bold_Font.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_icn_battery_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_icn_bluetooth_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_icn_history_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_btn_bg_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_btn_off_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_btn_on_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_heart_big_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_heart_small_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_line_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_slider_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/images/ui_img_img_switch_bg_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/screens/ui_Medical_Screen.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/ui.c \
	../../../../../apps/common/example/third_party/lvgl_v8/SquareLine_demos/Medical/ui_helpers.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/img_benchmark_cogwheel_argb.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/img_benchmark_cogwheel_rgb.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/benchmark/lv_demo_benchmark.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/keypad_encoder/lv_demo_keypad_encoder.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_corner_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_list_pause.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_list_pause_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_list_play.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_list_play_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_loop.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_loop_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_next.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_next_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_pause.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_pause_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_play.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_play_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_prev.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_prev_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_rnd.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_btn_rnd_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_corner_left.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_corner_left_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_corner_right.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_corner_right_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_cover_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_cover_1_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_cover_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_cover_2_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_cover_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_cover_3_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_1_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_2_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_3_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_icon_4_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_list_border.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_list_border_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_logo.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_slider_knob.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_slider_knob_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_wave_bottom.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_wave_bottom_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_wave_top.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/assets/img_lv_demo_music_wave_top_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/lv_demo_music.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/lv_demo_music_list.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/music/lv_demo_music_main.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/stress/lv_demo_stress.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/widgets/assets/img_clothes.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/widgets/assets/img_demo_widgets_avatar.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/widgets/assets/img_lvgl_logo.c \
	../../../../../apps/common/example/third_party/lvgl_v8/demos/widgets/lv_demo_widgets.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/anim/lv_example_anim_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/anim/lv_example_anim_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/anim/lv_example_anim_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/anim/lv_example_anim_timeline_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/animimg001.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/animimg002.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/animimg003.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/emoji/img_emoji_F617.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_caret_down.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_cogwheel_alpha16.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_cogwheel_argb.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_cogwheel_chroma_keyed.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_cogwheel_indexed16.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_cogwheel_rgb.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_hand.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_skew_strip.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/img_star.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/imgbtn_left.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/imgbtn_mid.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/assets/imgbtn_right.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/event/lv_example_event_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/event/lv_example_event_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/event/lv_example_event_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/event/lv_example_event_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/get_started/lv_example_get_started_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/get_started/lv_example_get_started_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/get_started/lv_example_get_started_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/flex/lv_example_flex_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/flex/lv_example_flex_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/flex/lv_example_flex_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/flex/lv_example_flex_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/flex/lv_example_flex_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/flex/lv_example_flex_6.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/grid/lv_example_grid_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/grid/lv_example_grid_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/grid/lv_example_grid_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/grid/lv_example_grid_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/grid/lv_example_grid_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/layouts/grid/lv_example_grid_6.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/bmp/lv_example_bmp_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/ffmpeg/lv_example_ffmpeg_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/ffmpeg/lv_example_ffmpeg_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/freetype/lv_example_freetype_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/gif/img_bulb_gif.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/gif/lv_example_gif_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/png/img_wink_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/png/lv_example_png_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/qrcode/lv_example_qrcode_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/rlottie/lv_example_rlottie_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/rlottie/lv_example_rlottie_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/rlottie/lv_example_rlottie_approve.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/libs/sjpg/lv_example_sjpg_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/fragment/lv_example_fragment_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/fragment/lv_example_fragment_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/gridnav/lv_example_gridnav_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/gridnav/lv_example_gridnav_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/gridnav/lv_example_gridnav_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/gridnav/lv_example_gridnav_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/ime/lv_example_ime_pinyin_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/ime/lv_example_ime_pinyin_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/imgfont/lv_example_imgfont_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/monkey/lv_example_monkey_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/monkey/lv_example_monkey_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/monkey/lv_example_monkey_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/msg/lv_example_msg_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/msg/lv_example_msg_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/msg/lv_example_msg_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/others/snapshot/lv_example_snapshot_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/porting/lv_port_disp.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/porting/lv_port_fs.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/porting/lv_port_indev.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/scroll/lv_example_scroll_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/scroll/lv_example_scroll_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/scroll/lv_example_scroll_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/scroll/lv_example_scroll_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/scroll/lv_example_scroll_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/scroll/lv_example_scroll_6.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_10.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_11.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_12.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_13.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_14.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_15.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_6.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_7.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_8.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/styles/lv_example_style_9.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/animimg/lv_example_animimg_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/arc/lv_example_arc_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/arc/lv_example_arc_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/bar/lv_example_bar_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/bar/lv_example_bar_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/bar/lv_example_bar_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/bar/lv_example_bar_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/bar/lv_example_bar_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/bar/lv_example_bar_6.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/btn/lv_example_btn_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/btn/lv_example_btn_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/btn/lv_example_btn_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/btnmatrix/lv_example_btnmatrix_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/btnmatrix/lv_example_btnmatrix_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/btnmatrix/lv_example_btnmatrix_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/calendar/lv_example_calendar_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/canvas/lv_example_canvas_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/canvas/lv_example_canvas_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_6.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_7.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_8.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/chart/lv_example_chart_9.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/checkbox/lv_example_checkbox_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/checkbox/lv_example_checkbox_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/colorwheel/lv_example_colorwheel_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/dropdown/lv_example_dropdown_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/dropdown/lv_example_dropdown_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/dropdown/lv_example_dropdown_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/img/lv_example_img_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/img/lv_example_img_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/img/lv_example_img_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/img/lv_example_img_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/imgbtn/lv_example_imgbtn_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/keyboard/lv_example_keyboard_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/label/lv_example_label_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/label/lv_example_label_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/label/lv_example_label_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/label/lv_example_label_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/label/lv_example_label_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/led/lv_example_led_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/line/lv_example_line_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/list/lv_example_list_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/list/lv_example_list_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/menu/lv_example_menu_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/menu/lv_example_menu_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/menu/lv_example_menu_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/menu/lv_example_menu_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/menu/lv_example_menu_5.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/meter/lv_example_meter_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/meter/lv_example_meter_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/meter/lv_example_meter_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/meter/lv_example_meter_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/msgbox/lv_example_msgbox_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/obj/lv_example_obj_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/obj/lv_example_obj_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/roller/lv_example_roller_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/roller/lv_example_roller_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/roller/lv_example_roller_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/slider/lv_example_slider_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/slider/lv_example_slider_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/slider/lv_example_slider_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/span/lv_example_span_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/spinbox/lv_example_spinbox_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/spinner/lv_example_spinner_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/switch/lv_example_switch_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/table/lv_example_table_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/table/lv_example_table_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/tabview/lv_example_tabview_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/tabview/lv_example_tabview_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/textarea/lv_example_textarea_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/textarea/lv_example_textarea_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/textarea/lv_example_textarea_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/tileview/lv_example_tileview_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/examples/widgets/win/lv_example_win_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8/lvgl_main.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_disp.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_event.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_group.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_indev.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_indev_scroll.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_class.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_draw.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_pos.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_scroll.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_style.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_style_gen.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_obj_tree.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_refr.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/core/lv_theme.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/arm2d/lv_gpu_arm2d.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_layer.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_mask.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_transform.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_draw_triangle.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_img_buf.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_img_cache.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/lv_img_decoder.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/pxp/lv_draw_pxp.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_draw_vglite.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_draw_vglite_blend.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_draw_vglite_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_draw_vglite_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_vglite_buf.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/nxp/vglite/lv_vglite_utils.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/renesas/lv_gpu_d2_draw_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/renesas/lv_gpu_d2_ra6m3.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_bg.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_composite.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_layer.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_mask.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_polygon.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_stack_blur.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_texture_cache.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sdl/lv_draw_sdl_utils.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_blend.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_dither.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_gradient.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_layer.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_letter.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_polygon.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/sw/lv_draw_sw_transform.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/draw/swm341_dma2d/lv_gpu_swm341_dma2d.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/layouts/flex/lv_flex.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/layouts/grid/lv_grid.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/barcode/code128.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/barcode/lv_barcode.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/bmp/lv_bmp.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/ffmpeg/lv_ffmpeg.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/freetype/lv_freetype.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/fsdrv/lv_fs_fatfs.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/fsdrv/lv_fs_littlefs.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/fsdrv/lv_fs_posix.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/fsdrv/lv_fs_stdio.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/fsdrv/lv_fs_win32.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/gif/gifdec.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/gif/lv_gif.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/png/lodepng.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/png/lv_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/qrcode/lv_qrcode.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/qrcode/qrcodegen.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/rlottie/lv_rlottie.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/rlottie/lv_rlottie_example_fingerprint.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/sjpg/lv_sjpg.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/sjpg/tjpgd.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/libs/tiny_ttf/lv_tiny_ttf.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/lv_extra.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_attention.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_back.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_bounce.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_fade.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_global.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_rotate.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_sliding.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_specials.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/anim_effect/lv_anim_effect_zooming.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/file_explorer/lv_file_explorer.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/fragment/lv_fragment.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/fragment/lv_fragment_manager.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/gridnav/lv_gridnav.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/ime/lv_ime_pinyin.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/imgfont/lv_imgfont.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/monkey/lv_monkey.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/msg/lv_msg.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/others/snapshot/lv_snapshot.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/themes/basic/lv_theme_basic.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/themes/default/lv_theme_default.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/themes/mono/lv_theme_mono.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/analogclock/lv_analogclock.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/animimg/lv_animimg.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/calendar/lv_calendar.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/carousel/lv_carousel.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/chart/lv_chart.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/colorwheel/lv_colorwheel.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/imgbtn/lv_imgbtn.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/keyboard/lv_keyboard.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/keyboard/lv_zh_keyboard.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/led/lv_led.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/list/lv_list.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/menu/lv_menu.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/meter/lv_meter.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/msgbox/lv_msgbox.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/radiobtn/lv_radiobtn.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/span/lv_span.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/spinbox/lv_spinbox.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/spinner/lv_spinner.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/tabview/lv_tabview.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/textprogress/lv_textprogress.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/tileview/lv_tileview.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/extra/widgets/win/lv_win.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_dejavu_16_persian_hebrew.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_fmt_txt.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_loader.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_10.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_12.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_12_subpx.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_14.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_16.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_18.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_20.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_22.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_24.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_26.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_28.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_28_compressed.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_30.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_32.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_34.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_36.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_38.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_40.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_42.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_44.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_46.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_48.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_montserrat_8.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_simsun_16_cjk.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_unscii_16.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/font/lv_font_unscii_8.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/hal/lv_hal_disp.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/hal/lv_hal_indev.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/hal/lv_hal_tick.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_anim.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_anim_timeline.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_area.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_async.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_bidi.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_color.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_fs.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_gc.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_ll.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_log.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_lru.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_math.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_mem.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_printf.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_style.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_style_gen.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_templ.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_timer.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_tlsf.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_txt.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_txt_ap.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/misc/lv_utils.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_bar.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_btn.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_btnmatrix.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_canvas.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_checkbox.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_dropdown.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_objx_templ.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_roller.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_slider.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_switch.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_table.c \
	../../../../../apps/common/example/third_party/lvgl_v8/src/widgets/lv_textarea.c \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/stb/rlottie_stb_image.c \
	../../../../../apps/common/iic/iic.c \
	../../../../../apps/common/iic/software_iic.c \
	../../../../../apps/common/key/adkey.c \
	../../../../../apps/common/key/adkey_rtcvdd.c \
	../../../../../apps/common/key/ctmu_touch_key.c \
	../../../../../apps/common/key/iokey.c \
	../../../../../apps/common/key/irkey.c \
	../../../../../apps/common/key/key_driver.c \
	../../../../../apps/common/key/matrix_keyboard.c \
	../../../../../apps/common/key/rdec_key.c \
	../../../../../apps/common/key/slidekey.c \
	../../../../../apps/common/key/tent600_key.c \
	../../../../../apps/common/key/touch_key.c \
	../../../../../apps/common/key/uart_key.c \
	../../../../../apps/common/system/device_mount.c \
	../../../../../apps/common/system/init.c \
	../../../../../apps/common/system/perf_counter/example/main.c \
	../../../../../apps/common/system/perf_counter/perf_counter.c \
	../../../../../apps/common/system/system_reset_reason.c \
	../../../../../apps/common/system/version.c \
	../../../../../apps/common/ui/GUI_GIF.c \
	../../../../../apps/common/ui/font/fontinit.c \
	../../../../../apps/common/ui/gif_api.c \
	../../../../../apps/common/ui/lcd/lcd_ui_api.c \
	../../../../../apps/common/ui/lcd_driver/lcd_480x272_8bits.c \
	../../../../../apps/common/ui/lcd_driver/lcd_data_driver.c \
	../../../../../apps/common/ui/lcd_driver/lcd_drive.c \
	../../../../../apps/common/ui/lcd_driver/lcd_hx8357.c \
	../../../../../apps/common/ui/lcd_driver/lcd_ili9341.c \
	../../../../../apps/common/ui/lcd_driver/lcd_ili9481.c \
	../../../../../apps/common/ui/lcd_driver/lcd_ili9488.c \
	../../../../../apps/common/ui/lcd_driver/lcd_st7735s.c \
	../../../../../apps/common/ui/lcd_driver/lcd_st7789s.c \
	../../../../../apps/common/ui/lcd_driver/lcd_st7789v.c \
	../../../../../apps/common/ui/lcd_driver/lcd_tm9486.c \
	../../../../../apps/common/ui/touch_panel/ft6236.c \
	../../../../../apps/common/ui/touch_panel/gt911.c \
	../../../../../apps/common/ui/ui_action_video.c \
	../../../../../apps/common/ui/ui_driver/interface/ui_platform.c \
	../../../../../apps/common/update/update.c \
	../../../../../apps/demo/demo_ui/app_main.c \
	../../../../../apps/demo/demo_ui/board/wl82/JL_AC79_DevKitBoard.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_0_ui_template.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_1_0.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_1_1.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_1_2.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_1_3.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_2_0.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_2_1.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_2_2.c \
	../../../../../apps/demo/demo_ui/demo/ui_demo_2_3.c \
	../../../../../apps/demo/demo_ui/get_yuv_data.c \
	../../../../../apps/demo/demo_ui/simple_avi_unpkg.c \
	../../../../../cpu/wl82/debug.c \
	../../../../../cpu/wl82/iic.c \
	../../../../../cpu/wl82/key/adc_api.c \
	../../../../../cpu/wl82/key/ctmu.c \
	../../../../../cpu/wl82/key/irflt.c \
	../../../../../cpu/wl82/key/plcnt.c \
	../../../../../cpu/wl82/key/rdec.c \
	../../../../../cpu/wl82/port_waked_up.c \
	../../../../../cpu/wl82/setup.c \


# 需要编译的 .S 文件
S_SRC_FILES := \
	../../../../../include_lib/btctrler/version.z.S \
	../../../../../include_lib/btstack/version.z.S \
	../../../../../include_lib/driver/version.z.S \
	../../../../../include_lib/media/version.z.S \
	../../../../../include_lib/net/version.z.S \
	../../../../../include_lib/server/version.z.S \
	../../../../../include_lib/system/version.z.S \
	../../../../../include_lib/update/version.z.S \
	../../../../../include_lib/utils/version.z.S \
	../../../../../lib/net/version.z.S \
	../../../../../lib/server/version.z.S \
	../../../../../lib/utils/version.z.S \


# 需要编译的 .s 文件
s_SRC_FILES :=


# 需要编译的 .cpp 文件
cpp_SRC_FILES := \
	../../../../../apps/common/c++/cxx_runtime.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/binding/c/lottieanimation_capi.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieanimation.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieitem.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieitem_capi.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottiekeypath.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieloader.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottiemodel.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieparser.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/lottie/lottieproxymodel.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype/v_ft_math.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype/v_ft_raster.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/freetype/v_ft_stroker.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/varenaalloc.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vbezier.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vbitmap.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vbrush.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdasher.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdebug.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawable.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper_common.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper_neon.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vdrawhelper_sse2.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/velapsedtimer.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vimageloader.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vinterpolator.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vmatrix.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vpainter.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vpath.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vpathmesure.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vraster.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vrect.cpp \
	../../../../../apps/common/example/third_party/rlottie_impl/src/vector/vrle.cpp \


# 需要编译的 .cc 文件
cc_SRC_FILES :=


# 需要编译的 .cxx 文件
cxx_SRC_FILES :=


# 链接参数
LFLAGS := \
	--plugin-opt=-pi32v2-always-use-itblock=false \
	--plugin-opt=-enable-ipra=true \
	--plugin-opt=-pi32v2-merge-max-offset=4096 \
	--plugin-opt=-pi32v2-enable-simd=true \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-global-merge-on-const \
	--plugin-opt=-inline-threshold=5 \
	--plugin-opt=-inline-max-allocated-size=32 \
	--plugin-opt=-inline-normal-into-special-section=true \
	--plugin-opt=-dont-used-symbol-list=malloc,free,sprintf,printf,puts,putchar \
	--plugin-opt=save-temps \
	--plugin-opt=-pi32v2-enable-rep-memop \
	--plugin-opt=-emulated-tls \
	--sort-common \
	--plugin-opt=-used-symbol-file=../../../../../cpu/wl82/sdk_used_list.used \
	--plugin-opt=-enable-movable-region=true \
	--plugin-opt=-movable-region-section-prefix=.movable.slot. \
	--plugin-opt=-movable-region-stub-section-prefix=.movable.stub. \
	--plugin-opt=-movable-region-prefix=.movable.region. \
	--plugin-opt=-movable-region-stub-prefix=__movable_stub_ \
	--plugin-opt=-movable-region-stub-swi-number=-2 \
	--plugin-opt=-movable-region-map-file-list=../../../../../apps/common/movable/funcname.txt \
	--plugin-opt=-movable-region-section-map-file-list=../../../../../apps/common/movable/section.txt \
	--plugin-opt=-movable-region-exclude-func-file-list=../../../../../apps/common/movable/exclude.txt \
	--plugin-opt=-pi32v2-large-program=true \
	--plugin-opt=-pi32v2-csync-before-rti=true \
	--start-group \
	../../../../../include_lib/newlib/pi32v2-lib/libm.a \
	../../../../../include_lib/newlib/pi32v2-lib/libc.a \
	../../../../../include_lib/newlib/pi32v2-lib/libcompiler_rt.a \
	--start-group  \
	../../../../../cpu/wl82/liba/cpu.a \
	../../../../../cpu/wl82/liba/event.a \
	../../../../../cpu/wl82/liba/system.a \
	../../../../../cpu/wl82/liba/cfg_tool.a \
	../../../../../cpu/wl82/liba/fs.a \
	../../../../../cpu/wl82/liba/common_lib.a \
	../../../../../cpu/wl82/liba/video_rec_server.a \
	../../../../../cpu/wl82/liba/audio_server.a \
	../../../../../cpu/wl82/liba/update.a \
	../../../../../cpu/wl82/liba/net_server.a \
	--end-group \
	../../../../../cpu/wl82/liba/video_dec_server.a \
	../../../../../cpu/wl82/liba/ui.a \
	../../../../../cpu/wl82/liba/res.a \
	../../../../../cpu/wl82/liba/font.a \
	../../../../../cpu/wl82/liba/ui_draw.a \
	../../../../../include_lib/c++/libstdc++/libemutls.a \
	../../../../../include_lib/c++/libstdc++/libc++.a \
	../../../../../include_lib/c++/libstdc++/libc++abi.a \
	-T../../../../../cpu/wl82/sdk.ld \
	-M=../../../../../cpu/wl82/tools/sdk.map \
	--end-group  \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-mattr=+fprev1 \



c_OBJS    := $(c_SRC_FILES:%.c=%.c.o)
S_OBJS    := $(S_SRC_FILES:%.S=%.S.o)
s_OBJS    := $(s_SRC_FILES:%.s=%.s.o)
cpp_OBJS  := $(cpp_SRC_FILES:%.cpp=%.cpp.o)
cxx_OBJS  := $(cxx_SRC_FILES:%.cxx=%.cxx.o)
cc_OBJS   := $(cc_SRC_FILES:%.cc=%.cc.o)

OBJS      := $(c_OBJS) $(S_OBJS) $(s_OBJS) $(cpp_OBJS) $(cxx_OBJS) $(cc_OBJS)
DEP_FILES := $(OBJS:%.o=%.d)


OBJS      := $(addprefix $(BUILD_DIR)/, $(OBJS:$(ROOT_PREFIX)/%=%))
DEP_FILES := $(addprefix $(BUILD_DIR)/, $(DEP_FILES:$(ROOT_PREFIX)/%=%))


VERBOSE ?= 0
ifeq ($(VERBOSE), 1)
QUITE :=
else
QUITE := @
endif

# 一些旧的 make 不支持 file 函数，需要 make 的时候指定 LINK_AT=0 make
LINK_AT ?= 1

# 表示下面的不是一个文件的名字，无论是否存在 all, clean, pre_build 这样的文件
# 还是要执行命令
# see: https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean pre_build

# 不要使用 make 预设置的规则
# see: https://www.gnu.org/software/make/manual/html_node/Suffix-Rules.html
.SUFFIXES:

all: pre_build $(OUT_ELF)
	$(info +POST-BUILD)
	$(QUITE) $(RUN_POST_SCRIPT) sdk

pre_build:
	$(info +PRE-BUILD)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl82/sdk_used_list.c -o ../../../../../cpu/wl82/sdk_used_list.used
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../apps/common/movable/section.c -o ../../../../../apps/common/movable/section.txt
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl82/sdk_ld.c -o ../../../../../cpu/wl82/sdk.ld
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl82/tools/download.c -o $(POST_SCRIPT)
	$(QUITE) $(FIXBAT) $(POST_SCRIPT)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl82/tools/isd_config_rule.c -o ../../../../../cpu/wl82/tools/isd_config.ini
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P ../../../../../cpu/wl82/tools/isd_config_rule_loader.c -o ../../../../../cpu/wl82/tools/isd_config_loader.ini

clean:
	$(QUITE) $(RM) $(OUT_ELF)
	$(QUITE) $(RM) $(BUILD_DIR)



ifeq ($(LINK_AT), 1)
$(OUT_ELF): $(OBJS)
	$(info +LINK $@)
	$(shell $(MKDIR) $(@D))
	$(file >$(OBJ_FILE), $(OBJS))
	$(QUITE) $(LD) -o $(OUT_ELF) @$(OBJ_FILE) $(LFLAGS) $(LIBPATHS) $(LIBS)
else
$(OUT_ELF): $(OBJS)
	$(info +LINK $@)
	$(shell $(MKDIR) $(@D))
	$(QUITE) $(LD) -o $(OUT_ELF) $(OBJS) $(LFLAGS) $(LIBPATHS) $(LIBS)
endif


$(BUILD_DIR)/%.c.o : $(ROOT_PREFIX)/%.c
	$(info +CC $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT $@ $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.S.o : $(ROOT_PREFIX)/%.S
	$(info +AS $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT $@ $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.s.o : $(ROOT_PREFIX)/%.s
	$(info +AS $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT $@ $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.cpp.o : $(ROOT_PREFIX)/%.cpp
	$(info +CXX $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT $@ $< -o $(@:.o=.d)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.cxx.o : $(ROOT_PREFIX)/%.cxx
	$(info +CXX $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT $@ $< -o $(@:.o=.d)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.cc.o : $(ROOT_PREFIX)/%.cc
	$(info +CXX $<)
	$(QUITE) $(MKDIR) $(@D)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT $@ $< -o $(@:.o=.d)
	$(QUITE) $(CXX) $(CXXFLAGS) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)
