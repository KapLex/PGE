TARGET = pge.zip

OBJS = ../../pgeZip.o pgeLuaZip.o ../PhoenixGameEngine.o

BUILD_PRX = 1

PRX_EXPORTS = pgezip_exports.exp

LIBS = -lz
LDFLAGS = -mno-crt0 -nostartfiles

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O3 -G0 -Wall -Wextra -mno-explicit-relocs -D__PSP__
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
