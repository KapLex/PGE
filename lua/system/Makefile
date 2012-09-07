TARGET = pge.system

OBJS = ../../pgeSystem.o pgeLuaSystem.o PGEMathForSystem.o ../PhoenixGameEngine.o

BUILD_PRX = 1

PRX_EXPORTS = pgesystem_exports.exp

LIBS = -lpsputility -lpspopenpsid -lpsppower -lpspwlan
LDFLAGS = -mno-crt0 -nostartfiles

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O3 -G0 -Wall -Wextra -mno-explicit-relocs -D__PSP__
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
