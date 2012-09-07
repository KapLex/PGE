TARGET = pge.mp3

OBJS = ../../pgeMp3.o pgeLuaMp3.o PGEFileForMp3.o ../PhoenixGameEngine.o

BUILD_PRX = 1

PRX_EXPORTS = pgemp3_exports.exp

LIBS = -lpspaudiocodec -lpspaudio -lpsppower
LDFLAGS = -mno-crt0 -nostartfiles

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O3 -G0 -Wall -Wextra -mno-explicit-relocs -D__PSP__ -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
