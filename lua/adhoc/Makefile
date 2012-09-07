TARGET = pge.adhoc

OBJS = ../../pgeAdhoc.o pgeLuaAdhoc.o ../PhoenixGameEngine.o

BUILD_PRX = 1

PRX_EXPORTS = pgeadhoc_exports.exp

LIBS = -lpspnet_adhoc -lpspnet_adhocctl -lpspnet_adhocmatching
LDFLAGS = -mno-crt0 -nostartfiles

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O2 -G0 -Wall -Wextra -mno-explicit-relocs -D__PSP__
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
