TARGET = pge.texture

OBJS = ../../pgeTexture.o pgeLuaTexture.o PGEGfxForTexture.o ../PhoenixGameEngine.o

BUILD_PRX = 1

PRX_EXPORTS = pgetexture_exports.exp

LIBS = -lpspgu -lpng -lz -lm
LDFLAGS = -mno-crt0 -nostartfiles

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O3 -G0 -Wall -Wextra -mno-explicit-relocs -D__PSP__
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
