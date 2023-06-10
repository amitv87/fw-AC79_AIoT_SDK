
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

SYS_LIB_DIR := C:/JL/pi32/pi32v2-lib/r3
SYS_INC_DIR := C:/JL/pi32/pi32v2-include
EXT_CFLAGS  := # Windows 下不需要 -D__SHELL__
export PATH:=$(TOOL_DIR);$(PATH)

## 后处理脚本
FIXBAT          := ..\..\..\..\..\tools\utils\fixbat.exe # 用于处理 utf8->gbk 编码问题
POST_SCRIPT     := ..\..\..\..\..\cpu\wl82\tools\download.bat
RUN_POST_SCRIPT := $(POST_SCRIPT)
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
	-mcpu=r3 \
	-integrated-as \
	-flto \
	-Wuninitialized \
	-Wno-invalid-noreturn \
	-fno-common \
	-integrated-as \
	-Oz \
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
	-DAWTK_COMMIT_HASH=\"b080ad1c01aafc7329265fe216eb75ea9d1adc3e\" \
	-DHAS_AWTK_CONFIG \
	-DWITH_JERRYSCRIPT \
	-DHAVE_CONFIG_H \
	-DJERRY_COMMIT_HASH=\"3737a28eafd580a2bee2794e4f5edd0c0471a0c6\" \
	-D_XOPEN_SOURCE=700 \
	-D_GNU_SOURCE \
	-D__ELF__ \
	-D__LD__ \


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
	-I../../../../../apps/demo/demo_ui \
	-I../../../../../include_lib/server \
	-I../../../../../include_lib/system/os \
	-I../../../../../apps/common \
	-I../../../../../apps/common/ui/include \
	-I../../../../../include_lib/utils/ui \
	-I../../../../../apps/common/example/third_party/awtk/3rd/awtk-csv-file/src \
	-I../../../../../apps/common/example/third_party/awtk \
	-I../../../../../apps/common/example/third_party/awtk/src \
	-I../../../../../apps/common/example/third_party/awtk/src/ext_widgets \
	-I../../../../../apps/common/example/third_party/awtk/3rd \
	-I../../../../../apps/common/example/third_party/awtk/3rd/SDL/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/cairo \
	-I../../../../../apps/common/example/third_party/awtk/3rd/nanovg \
	-I../../../../../apps/common/example/third_party/awtk/3rd/nanovg/base \
	-I../../../../../apps/common/example/third_party/awtk/3rd/nanovg_plus/base \
	-I../../../../../apps/common/example/third_party/awtk/3rd/nanovg/gl \
	-I../../../../../apps/common/example/third_party/awtk/3rd/nanovg_plus/gl \
	-I../../../../../apps/common/example/third_party/awtk/src/platforms/jieli \
	-I../../../../../apps/common/example/third_party/awtk/3rd/svgtiny/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/agge \
	-I../../../../../apps/common/example/third_party/awtk/3rd/agg/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/sqlite3/src \
	-I../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo \
	-I../../../../../apps/common/example/third_party/awtk/3rd/pixman \
	-I../../../../../apps/common/example/third_party/awtk/awtk-mvvm/src \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/jmem \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/jrt \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/lit \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/jcontext \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/debugger \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-ext/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-ext/common \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-port/default/include \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/ecma/base \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/ecma/builtin-objects \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/ecma/operations \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/parser/js \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/parser/regexp \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/vm \
	-I../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0 \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/core \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/arm2d \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/nxp \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/nxp/pxp \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/nxp/vglite \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/sdl \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/stm32_dma2d \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/sw \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/draw/swm341_dma2d \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/layouts/flex \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/layouts/grid \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/bmp \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/ffmpeg \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/freetype \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/fsdrv \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/gif \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/png \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/qrcode \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/rlottie \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/libs/sjpg \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/fragment \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/gridnav \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/ime \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/imgfont \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/monkey \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/msg \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/others/snapshot \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/themes/basic \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/themes/default \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/themes/mono \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/animimg \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/calendar \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/chart \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/colorwheel \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/imgbtn \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/keyboard \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/led \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/list \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/menu \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/meter \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/msgbox \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/span \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/spinbox \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/spinner \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/tabview \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/tileview \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/extra/widgets/win \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/font \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/hal \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/misc \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/include/widgets \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/keypad_encoder \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/stress \
	-I../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/widgets \
	-I$(SYS_INC_DIR) \


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
	../../../../../apps/common/example/third_party/awtk/3rd/awtk-csv-file/demos/main.c \
	../../../../../apps/common/example/third_party/awtk/3rd/awtk-csv-file/src/csv_file.c \
	../../../../../apps/common/example/third_party/awtk/3rd/awtk-csv-file/src/csv_file_object.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-analysis-surface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-arc.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-array.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-atomic.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-base64-stream.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-base85-stream.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-bentley-ottmann-rectangular.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-bentley-ottmann-rectilinear.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-bentley-ottmann.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-botor-scan-converter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-boxes-intersect.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-boxes.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-cache.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-clip-boxes.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-clip-polygon.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-clip-region.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-clip-surface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-clip-tor-scan-converter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-clip.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-color.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-composite-rectangles.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-contour.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-damage.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-debug.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-default-context.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-device.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-error.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-fallback-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-font-face-twin-data.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-font-face-twin.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-font-face.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-font-options.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-freelist.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-gstate.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-hash.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-hull.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-image-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-image-info.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-image-source.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-image-surface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-line.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-lzw.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-mask-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-matrix.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-mempool.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-mesh-pattern-rasterizer.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-misc.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-mono-scan-converter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-mutex.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-no-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-observer.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-output-stream.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-paginated-surface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-bounds.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-fill.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-fixed.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-in-fill.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-stroke-boxes.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-stroke-polygon.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-stroke-traps.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-stroke-tristrip.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path-stroke.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-path.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-pattern.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-pen.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-polygon-intersect.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-polygon-reduce.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-polygon.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-raster-source-pattern.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-recording-surface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-rectangle.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-rectangular-scan-converter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-region.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-rtree.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-scaled-font.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-shape-mask-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-slope.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-spans-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-spans.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-spline.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-stroke-dash.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-stroke-style.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface-clipper.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface-fallback.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface-offset.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface-snapshot.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface-subsurface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface-wrapper.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-surface.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-tor-scan-converter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-tor22-scan-converter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-toy-font-face.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-traps-compositor.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-traps.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-tristrip.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-unicode.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-user-font.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-version.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo-wideint.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/cairo/cairo.c \
	../../../../../apps/common/example/third_party/awtk/3rd/cairo/demos/stars.c \
	../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerry-all-in.c \
	../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-main/cli.c \
	../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-main/main-jerry.c \
	../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-main/main-options.c \
	../../../../../apps/common/example/third_party/awtk/3rd/jerryscript/jerryscript/jerry-main/main-utils.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/emojidef.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/graphemebreak.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/linebreak.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/linebreakdata.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/linebreakdef.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/unibreakbase.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/unibreakdef.c \
	../../../../../apps/common/example/third_party/awtk/3rd/libunibreak/wordbreak.c \
	../../../../../apps/common/example/third_party/awtk/3rd/nanovg/base/nanovg.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-access-accessors.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-access.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-arm.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-bits-image.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-combine-float.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-combine32.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-conical-gradient.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-edge-accessors.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-edge.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-fast-path.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-filter.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-general.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-glyph.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-gradient-walker.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-image.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-implementation.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-linear-gradient.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-matrix.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-mips.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-noop.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-ppc.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-radial-gradient.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-region16.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-region32.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-solid-fill.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-timer.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-trap.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-utils.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman-x86.c \
	../../../../../apps/common/example/third_party/awtk/3rd/pixman/pixman/pixman.c \
	../../../../../apps/common/example/third_party/awtk/3rd/svgtiny/src/colors.c \
	../../../../../apps/common/example/third_party/awtk/3rd/svgtiny/src/svgtiny.c \
	../../../../../apps/common/example/third_party/awtk/3rd/svgtiny/src/svgtiny_dom.c \
	../../../../../apps/common/example/third_party/awtk/3rd/svgtiny/src/svgtiny_gradient.c \
	../../../../../apps/common/example/third_party/awtk/3rd/svgtiny/src/svgtiny_list.c \
	../../../../../apps/common/example/third_party/awtk/awtk_main.c \
	../../../../../apps/common/example/third_party/awtk/demos/assets_old-1m.c \
	../../../../../apps/common/example/third_party/awtk/demos/demo_ui_old_app.c \
	../../../../../apps/common/example/third_party/awtk/src/awtk_global.c \
	../../../../../apps/common/example/third_party/awtk/src/base/asset_loader.c \
	../../../../../apps/common/example/third_party/awtk/src/base/asset_loader_default.c \
	../../../../../apps/common/example/third_party/awtk/src/base/asset_loader_zip.c \
	../../../../../apps/common/example/third_party/awtk/src/base/assets_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/base/bidi.c \
	../../../../../apps/common/example/third_party/awtk/src/base/bitmap.c \
	../../../../../apps/common/example/third_party/awtk/src/base/canvas.c \
	../../../../../apps/common/example/third_party/awtk/src/base/children_layouter.c \
	../../../../../apps/common/example/third_party/awtk/src/base/children_layouter_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/base/clip_board.c \
	../../../../../apps/common/example/third_party/awtk/src/base/data_reader_asset.c \
	../../../../../apps/common/example/third_party/awtk/src/base/date_time_format.c \
	../../../../../apps/common/example/third_party/awtk/src/base/dialog.c \
	../../../../../apps/common/example/third_party/awtk/src/base/dialog_highlighter.c \
	../../../../../apps/common/example/third_party/awtk/src/base/dialog_highlighter_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/base/enums.c \
	../../../../../apps/common/example/third_party/awtk/src/base/event_queue.c \
	../../../../../apps/common/example/third_party/awtk/src/base/event_recorder_player.c \
	../../../../../apps/common/example/third_party/awtk/src/base/events.c \
	../../../../../apps/common/example/third_party/awtk/src/base/font.c \
	../../../../../apps/common/example/third_party/awtk/src/base/font_loader.c \
	../../../../../apps/common/example/third_party/awtk/src/base/font_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/base/glyph_cache.c \
	../../../../../apps/common/example/third_party/awtk/src/base/graphic_buffer.c \
	../../../../../apps/common/example/third_party/awtk/src/base/hscrollable.c \
	../../../../../apps/common/example/third_party/awtk/src/base/idle.c \
	../../../../../apps/common/example/third_party/awtk/src/base/image_base.c \
	../../../../../apps/common/example/third_party/awtk/src/base/image_loader.c \
	../../../../../apps/common/example/third_party/awtk/src/base/image_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/base/input_device_status.c \
	../../../../../apps/common/example/third_party/awtk/src/base/input_engine.c \
	../../../../../apps/common/example/third_party/awtk/src/base/input_method.c \
	../../../../../apps/common/example/third_party/awtk/src/base/layout.c \
	../../../../../apps/common/example/third_party/awtk/src/base/lcd.c \
	../../../../../apps/common/example/third_party/awtk/src/base/lcd_profile.c \
	../../../../../apps/common/example/third_party/awtk/src/base/line_break.c \
	../../../../../apps/common/example/third_party/awtk/src/base/locale_info.c \
	../../../../../apps/common/example/third_party/awtk/src/base/main_loop.c \
	../../../../../apps/common/example/third_party/awtk/src/base/native_window.c \
	../../../../../apps/common/example/third_party/awtk/src/base/self_layouter.c \
	../../../../../apps/common/example/third_party/awtk/src/base/self_layouter_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/base/shortcut.c \
	../../../../../apps/common/example/third_party/awtk/src/base/style.c \
	../../../../../apps/common/example/third_party/awtk/src/base/style_const.c \
	../../../../../apps/common/example/third_party/awtk/src/base/style_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/base/style_mutable.c \
	../../../../../apps/common/example/third_party/awtk/src/base/suggest_words.c \
	../../../../../apps/common/example/third_party/awtk/src/base/system_info.c \
	../../../../../apps/common/example/third_party/awtk/src/base/text_edit.c \
	../../../../../apps/common/example/third_party/awtk/src/base/theme.c \
	../../../../../apps/common/example/third_party/awtk/src/base/timer.c \
	../../../../../apps/common/example/third_party/awtk/src/base/ui_builder.c \
	../../../../../apps/common/example/third_party/awtk/src/base/ui_feedback.c \
	../../../../../apps/common/example/third_party/awtk/src/base/ui_loader.c \
	../../../../../apps/common/example/third_party/awtk/src/base/velocity.c \
	../../../../../apps/common/example/third_party/awtk/src/base/vgcanvas.c \
	../../../../../apps/common/example/third_party/awtk/src/base/widget.c \
	../../../../../apps/common/example/third_party/awtk/src/base/widget_animator.c \
	../../../../../apps/common/example/third_party/awtk/src/base/widget_animator_factory_null.c \
	../../../../../apps/common/example/third_party/awtk/src/base/widget_animator_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/base/widget_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/base/widget_vtable.c \
	../../../../../apps/common/example/third_party/awtk/src/base/window.c \
	../../../../../apps/common/example/third_party/awtk/src/base/window_animator.c \
	../../../../../apps/common/example/third_party/awtk/src/base/window_animator_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/base/window_base.c \
	../../../../../apps/common/example/third_party/awtk/src/base/window_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr565_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr565_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr565_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr565_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr888_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr888_bgr888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr888_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr888_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgr888_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgra8888_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgra8888_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgra8888_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_bgra8888_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb565_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb565_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb565_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb565_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb888_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb888_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb888_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb888_rgb888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgb888_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgba8888_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgba8888_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgba8888_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/blend_image_rgba8888_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_abgr8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_argb8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_bgr888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_rgb888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/fill_image_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/image_g2d.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/rotate_image_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/rotate_image_bgr888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/rotate_image_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/rotate_image_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/rotate_image_rgb888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/rotate_image_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/soft_g2d.c \
	../../../../../apps/common/example/third_party/awtk/src/blend/stm32_g2d.c \
	../../../../../apps/common/example/third_party/awtk/src/charset/encoding.c \
	../../../../../apps/common/example/third_party/awtk/src/clip_board/clip_board_default.c \
	../../../../../apps/common/example/third_party/awtk/src/clip_board/clip_board_sdl.c \
	../../../../../apps/common/example/third_party/awtk/src/compressors/compressor_miniz.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/app_conf.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/app_conf_init.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/app_conf_init_ini.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/app_conf_init_json.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/app_conf_init_ubjson.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/conf_ini.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/conf_json.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/conf_node.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/conf_obj.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/conf_ubjson.c \
	../../../../../apps/common/example/third_party/awtk/src/conf_io/conf_xml.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_client.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_client_tcp.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_fscript.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_global.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_message.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_server.c \
	../../../../../apps/common/example/third_party/awtk/src/debugger/debugger_server_tcp.c \
	../../../../../apps/common/example/third_party/awtk/src/dialog_highlighters/dialog_highlighter_builtins.c \
	../../../../../apps/common/example/third_party/awtk/src/dialog_highlighters/dialog_highlighter_default.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/canvas_widget/canvas_widget.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/color_picker/color_component.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/color_picker/color_picker.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/color_picker/rgb_and_hsv.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/combo_box_ex/combo_box_ex.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/ext_widgets.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/features/draggable.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/file_browser/file_browser.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/file_browser/file_browser_view.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/file_browser/file_chooser.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/file_browser/file_dialog.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/gauge/gauge.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/gauge/gauge_pointer.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/gif_image/gif_image.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/image_animation/image_animation.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/image_value/image_value.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/keyboard/candidates.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/keyboard/keyboard.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/keyboard/lang_indicator.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/mledit/line_number.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/mledit/mledit.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/mutable_image/mutable_image.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/progress_circle/progress_circle.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/rich_text/rich_text.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/rich_text/rich_text_node.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/rich_text/rich_text_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/rich_text/rich_text_render_node.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/rich_text/rich_text_view.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_label/hscroll_label.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_view/children_layouter_list_view.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_view/list_item.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_view/list_view.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_view/list_view_h.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_view/scroll_bar.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/scroll_view/scroll_view.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/serial_widget/serial_widget.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/slide_menu/slide_menu.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/slide_view/slide_indicator.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/slide_view/slide_view.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/svg_image/svg_image.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/switch/switch.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/text_selector/text_selector.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/time_clock/time_clock.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/timer_widget/timer_widget.c \
	../../../../../apps/common/example/third_party/awtk/src/ext_widgets/vpage/vpage.c \
	../../../../../apps/common/example/third_party/awtk/src/font_loader/font_loader_bitmap.c \
	../../../../../apps/common/example/third_party/awtk/src/font_loader/font_loader_ft.c \
	../../../../../apps/common/example/third_party/awtk/src/font_loader/font_loader_stb.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_app_conf.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_array.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_bits.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_crc.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_date_time.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_endian.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_ext.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_fs.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_iostream.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_iostream_file.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_iostream_inet.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_iostream_serial.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_istream.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_json.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_math.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_module.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_object.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_ostream.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_rbuffer.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_typed_array.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_utils.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_wbuffer.c \
	../../../../../apps/common/example/third_party/awtk/src/fscript_ext/fscript_widget.c \
	../../../../../apps/common/example/third_party/awtk/src/graphic_buffer/graphic_buffer_default.c \
	../../../../../apps/common/example/third_party/awtk/src/hal/macos/network_interface_macos.c \
	../../../../../apps/common/example/third_party/awtk/src/hal/network_interface.c \
	../../../../../apps/common/example/third_party/awtk/src/image_loader/image_loader_stb.c \
	../../../../../apps/common/example/third_party/awtk/src/input_engines/ime_utils.c \
	../../../../../apps/common/example/third_party/awtk/src/input_engines/input_engine_null.c \
	../../../../../apps/common/example/third_party/awtk/src/input_engines/input_engine_spinyin.c \
	../../../../../apps/common/example/third_party/awtk/src/input_engines/input_engine_t9.c \
	../../../../../apps/common/example/third_party/awtk/src/input_engines/input_engine_t9ext.c \
	../../../../../apps/common/example/third_party/awtk/src/input_methods/input_method_creator.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/children_layouter_builtins.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/children_layouter_default.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/children_layouter_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/self_layouter_builtins.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/self_layouter_default.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/self_layouter_menu.c \
	../../../../../apps/common/example/third_party/awtk/src/layouters/self_layouter_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_bgr565.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_bgr888.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_bgra8888.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_rgb565.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_rgb888.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_rgba8888.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mem_special.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_mono.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_nanovg.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_sdl2.c \
	../../../../../apps/common/example/third_party/awtk/src/lcd/lcd_sdl2_mono.c \
	../../../../../apps/common/example/third_party/awtk/src/main_loop/main_loop_simple.c \
	../../../../../apps/common/example/third_party/awtk/src/native_window/native_window_raw.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/cond_var.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/dl.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/fs_os.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/lcd_impl.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/main_loop_impl.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/mutex.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/platform.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/semaphore.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/sys_tick_handler.c \
	../../../../../apps/common/example/third_party/awtk/src/platforms/jieli/thread.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/buffered/istream_buffered.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/buffered/ostream_buffered.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/file/istream_file.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/file/ostream_file.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/mem/iostream_mem.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/mem/istream_mem.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/mem/ostream_mem.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/misc/ostream_retry.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/noisy/iostream_noisy.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/noisy/ostream_noisy.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/serial/iostream_serial.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/serial/istream_serial.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/serial/ostream_serial.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/serial/serial_helper.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/statistics/iostream_stats.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/statistics/istream_stats.c \
	../../../../../apps/common/example/third_party/awtk/src/streams/statistics/ostream_stats.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/bsvg.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/bsvg_builder.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/bsvg_draw.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/bsvg_to_svg.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/svg_path.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/svg_path_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/svg_shape.c \
	../../../../../apps/common/example/third_party/awtk/src/svg/svg_to_bsvg.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/action_darray_thread.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/action_queue.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/action_thread.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/action_thread_pool.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/asset_info.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/async.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/buffer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/color.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/color_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/compressor.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/cond_var.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/crc.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/darray.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_reader.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_reader_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_reader_file.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_reader_mem.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_writer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_writer_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_writer_file.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/data_writer_wbuffer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/date_time.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/easing.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/emitter.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event_source.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event_source_fd.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event_source_idle.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event_source_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event_source_manager_default.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/event_source_timer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/fs.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/fscript.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/func_call_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/hash_table.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/idle_info.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/idle_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/int_str.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/iostream.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/istream.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/log.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/matrix.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/mem.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/mutex_nest.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/named_value.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_array.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_compositor.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_date_time.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_default.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_locker.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_rbuffer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_typed_array.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/object_wbuffer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/ostream.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/path.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/plugin_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/qaction.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/rect.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/ring_buffer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/rlog.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/rom_fs.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/sha256.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/slist.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/socket_helper.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/socket_pair.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/state_machine.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/str.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/str_str.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/time_now.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/timer_info.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/timer_manager.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/tokenizer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/typed_array.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/url.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/utf8.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/utils.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/value.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/value_desc.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/waitable_action_darray.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/waitable_action_queue.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/waitable_ring_buffer.c \
	../../../../../apps/common/example/third_party/awtk/src/tkc/wstr.c \
	../../../../../apps/common/example/third_party/awtk/src/ubjson/tools/ubjson_dump.c \
	../../../../../apps/common/example/third_party/awtk/src/ubjson/ubjson_parser.c \
	../../../../../apps/common/example/third_party/awtk/src/ubjson/ubjson_reader.c \
	../../../../../apps/common/example/third_party/awtk/src/ubjson/ubjson_writer.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/ui_binary_writer.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/ui_builder_default.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/ui_loader_default.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/ui_loader_xml.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/ui_serializer.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/ui_xml_writer.c \
	../../../../../apps/common/example/third_party/awtk/src/ui_loader/window_open.c \
	../../../../../apps/common/example/third_party/awtk/src/vgcanvas/vgcanvas_cairo.c \
	../../../../../apps/common/example/third_party/awtk/src/vgcanvas/vgcanvas_nanovg_soft.c \
	../../../../../apps/common/example/third_party/awtk/src/vgcanvas/vgcanvas_null.c \
	../../../../../apps/common/example/third_party/awtk/src/widget_animators/widget_animator_factory.c \
	../../../../../apps/common/example/third_party/awtk/src/widget_animators/widget_animator_prop.c \
	../../../../../apps/common/example/third_party/awtk/src/widget_animators/widget_animator_prop2.c \
	../../../../../apps/common/example/third_party/awtk/src/widget_animators/widget_animator_scroll.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/app_bar.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/button.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/button_group.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/calibration_win.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/check_button.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/clip_view.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/color_tile.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/column.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/combo_box.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/combo_box_item.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/dialog_client.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/dialog_helper.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/dialog_title.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/digit_clock.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/dragger.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/edit.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/grid.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/grid_item.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/group_box.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/image.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/label.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/overlay.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/pages.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/popup.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/progress_bar.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/row.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/slider.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/spin_box.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/system_bar.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/tab_button.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/tab_button_group.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/tab_control.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/view.c \
	../../../../../apps/common/example/third_party/awtk/src/widgets/widgets.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_builtins.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_center_scale.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_common.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_fade.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_htranslate.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_popdown.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_popup.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_slide.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_slide_down.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_slide_left.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_slide_right.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_slide_up.c \
	../../../../../apps/common/example/third_party/awtk/src/window_animators/window_animator_vtranslate.c \
	../../../../../apps/common/example/third_party/awtk/src/window_manager/window_manager_default.c \
	../../../../../apps/common/example/third_party/awtk/src/xml/xml_builder.c \
	../../../../../apps/common/example/third_party/awtk/src/xml/xml_parser.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/img_benchmark_cogwheel_argb.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/img_benchmark_cogwheel_rgb.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/benchmark/lv_demo_benchmark.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/keypad_encoder/lv_demo_keypad_encoder.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_corner_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_list_pause.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_list_pause_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_list_play.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_list_play_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_loop.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_loop_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_next.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_next_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_pause.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_pause_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_play.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_play_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_prev.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_prev_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_rnd.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_btn_rnd_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_corner_left.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_corner_left_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_corner_right.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_corner_right_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_cover_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_cover_1_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_cover_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_cover_2_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_cover_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_cover_3_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_1.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_1_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_2.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_2_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_3.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_3_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_4.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_icon_4_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_list_border.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_list_border_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_logo.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_slider_knob.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_slider_knob_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_wave_bottom.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_wave_bottom_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_wave_top.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/assets/img_lv_demo_music_wave_top_large.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/lv_demo_music.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/lv_demo_music_list.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/music/lv_demo_music_main.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/stress/lv_demo_stress.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/widgets/assets/img_clothes.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/widgets/assets/img_demo_widgets_avatar.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/widgets/assets/img_lvgl_logo.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/demos/widgets/lv_demo_widgets.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/driver/lv_fs_driver.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/driver/lv_main.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/driver/lv_show_driver.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/driver/lv_touch_driver.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_disp.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_event.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_group.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_indev.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_indev_scroll.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_class.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_draw.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_pos.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_scroll.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_style.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_style_gen.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_obj_tree.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_refr.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/core/lv_theme.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/arm2d/lv_gpu_arm2d.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_layer.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_mask.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_transform.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_draw_triangle.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_img_buf.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_img_cache.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/lv_img_decoder.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/lv_gpu_nxp.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/vglite/lv_draw_vglite_blend.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/vglite/lv_draw_vglite_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/nxp/vglite/lv_gpu_nxp_vglite.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_bg.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_composite.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_layer.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_mask.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_polygon.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_stack_blur.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_texture_cache.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sdl/lv_draw_sdl_utils.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_blend.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_dither.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_gradient.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_layer.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_letter.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_polygon.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_rect.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/sw/lv_draw_sw_transform.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/draw/swm341_dma2d/lv_gpu_swm341_dma2d.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/layouts/flex/lv_flex.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/layouts/grid/lv_grid.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/bmp/lv_bmp.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/ffmpeg/lv_ffmpeg.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/freetype/lv_freetype.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/fsdrv/lv_fs_fatfs.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/fsdrv/lv_fs_posix.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/fsdrv/lv_fs_stdio.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/fsdrv/lv_fs_win32.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/gif/gifdec.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/gif/lv_gif.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/png/lodepng.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/png/lv_png.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/qrcode/lv_qrcode.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/qrcode/qrcodegen.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/rlottie/lv_rlottie.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/sjpg/lv_sjpg.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/libs/sjpg/tjpgd.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/lv_extra.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/fragment/lv_fragment.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/fragment/lv_fragment_manager.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/gridnav/lv_gridnav.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/ime/lv_ime_pinyin.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/imgfont/lv_imgfont.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/monkey/lv_monkey.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/msg/lv_msg.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/others/snapshot/lv_snapshot.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/themes/basic/lv_theme_basic.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/themes/default/lv_theme_default.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/themes/mono/lv_theme_mono.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/animimg/lv_animimg.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/calendar/lv_calendar.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/chart/lv_chart.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/colorwheel/lv_colorwheel.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/imgbtn/lv_imgbtn.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/keyboard/lv_keyboard.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/led/lv_led.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/list/lv_list.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/menu/lv_menu.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/meter/lv_meter.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/msgbox/lv_msgbox.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/span/lv_span.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/spinbox/lv_spinbox.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/spinner/lv_spinner.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/tabview/lv_tabview.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/tileview/lv_tileview.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/extra/widgets/win/lv_win.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_dejavu_16_persian_hebrew.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_fmt_txt.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_loader.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_10.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_12.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_12_subpx.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_14.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_16.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_18.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_20.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_22.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_24.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_26.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_28.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_28_compressed.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_30.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_32.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_34.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_36.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_38.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_40.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_42.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_44.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_46.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_48.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_montserrat_8.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_simsun_16_cjk.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_unscii_16.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/font/lv_font_unscii_8.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/hal/lv_hal_disp.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/hal/lv_hal_indev.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/hal/lv_hal_tick.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_anim.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_anim_timeline.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_area.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_async.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_bidi.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_color.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_fs.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_gc.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_ll.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_log.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_lru.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_math.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_mem.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_printf.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_style.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_style_gen.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_templ.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_timer.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_tlsf.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_txt.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_txt_ap.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/misc/lv_utils.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_arc.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_bar.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_btn.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_btnmatrix.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_canvas.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_checkbox.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_dropdown.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_img.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_label.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_line.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_objx_templ.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_roller.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_slider.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_switch.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_table.c \
	../../../../../apps/common/example/third_party/lvgl_v8.3.0/src/widgets/lv_textarea.c \
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
	../../../../../apps/common/system/system_reset_reason.c \
	../../../../../apps/common/system/version.c \
	../../../../../apps/common/ui/GUI_GIF.c \
	../../../../../apps/common/ui/font/fontinit.c \
	../../../../../apps/common/ui/gif_api.c \
	../../../../../apps/common/ui/lcd/lcd_ui_api.c \
	../../../../../apps/common/ui/lcd_driver/lcd_480x272_8bits.c \
	../../../../../apps/common/ui/lcd_driver/lcd_drive.c \
	../../../../../apps/common/ui/lcd_driver/lcd_hx8357.c \
	../../../../../apps/common/ui/lcd_driver/lcd_ili9341.c \
	../../../../../apps/common/ui/lcd_driver/lcd_ili9481.c \
	../../../../../apps/common/ui/lcd_driver/lcd_ili9488.c \
	../../../../../apps/common/ui/lcd_driver/lcd_st7735s.c \
	../../../../../apps/common/ui/lcd_driver/lcd_st7789s.c \
	../../../../../apps/common/ui/lcd_driver/lcd_st7789v.c \
	../../../../../apps/common/ui/lcd_driver/te_driver/lcd_data_driver.c \
	../../../../../apps/common/ui/lcd_driver/te_driver/lcd_te_driver.c \
	../../../../../apps/common/ui/touch_panel/ft6236.c \
	../../../../../apps/common/ui/touch_panel/gt911.c \
	../../../../../apps/common/ui/ui_action_video.c \
	../../../../../apps/common/ui/ui_driver/interface/ui_platform.c \
	../../../../../apps/common/update/update.c \
	../../../../../apps/demo/demo_ui/app_main.c \
	../../../../../apps/demo/demo_ui/board/wl82/AC7916_DEV_V1.0.c \
	../../../../../apps/demo/demo_ui/board/wl82/JL_AC79_DevKitBoard.c \
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
	../../../../../apps/common/example/third_party/awtk/3rd/agg/src/agg_color_rgba.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agg/src/agg_image_filters.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agg/src/agg_sqrt_tables.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agg/src/agg_trans_affine.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agg/src/agg_vcgen_stroke.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agge/agge/math.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agge/agge/stroke.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agge/agge/stroke_features.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/agge/agge/vector_rasterizer.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/dictlist.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/dicttrie.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/lpicache.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/matrixsearch.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/mystdlib.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/ngram.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/pinyinime.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/searchutility.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/spellingtrie.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/splparser.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/gpinyin/src/utf16char.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/nanovg/agg/nanovg_agg.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/nanovg/agge/nanovg_agge.cpp \
	../../../../../apps/common/example/third_party/awtk/3rd/nanovg/agge/nanovg_vertex.cpp \
	../../../../../apps/common/example/third_party/awtk/src/input_engines/input_engine_pinyin.cpp \


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
	--start-group \
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


LIBPATHS := \
	-L$(SYS_LIB_DIR) \


LIBS := \
	$(SYS_LIB_DIR)/libm.a \
	$(SYS_LIB_DIR)/libc.a \
	$(SYS_LIB_DIR)/libm.a \
	$(SYS_LIB_DIR)/libcompiler-rt.a \



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
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../../cpu/wl82/sdk_used_list.c -o ../../../../../cpu/wl82/sdk_used_list.used
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../../apps/common/movable/section.c -o ../../../../../apps/common/movable/section.txt
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../../cpu/wl82/sdk_ld.c -o ../../../../../cpu/wl82/sdk.ld
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../../cpu/wl82/tools/download.c -o $(POST_SCRIPT)
	$(QUITE) $(FIXBAT) $(POST_SCRIPT)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../../cpu/wl82/tools/isd_config_rule.c -o ../../../../../cpu/wl82/tools/isd_config.ini
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../../cpu/wl82/tools/isd_config_rule_loader.c -o ../../../../../cpu/wl82/tools/isd_config_loader.ini

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
