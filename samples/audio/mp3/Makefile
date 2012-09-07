TARGET = pgeMp3Sample
OBJS = mp3test.o

BUILD_PRX = 1

INCDIR =
CFLAGS = -O3 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PGE MP3 Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/pge_build.mak
include $(PSPSDK)/lib/build.mak
