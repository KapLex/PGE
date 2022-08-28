TARGET = pge.font

OBJS = ../../pgeFont.o pgeLuaFont.o PGEGfxForFont.o ../PhoenixGameEngine.o

BUILD_PRX = 1

PRX_EXPORTS = pgefont_exports.exp

LIBS = $(shell $(PSPBIN)/bin/freetype-config --libs) -lfreetype -lz
LDFLAGS = -mno-crt0 -nostartfiles

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O3 -g -G0 -Wall -Wextra -mno-explicit-relocs $(shell $(PSPBIN)/bin/freetype-config --cflags) -D__PSP__
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
