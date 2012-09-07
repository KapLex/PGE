TARGET = pgeAutoUpdateSample
OBJS = autoupdate.o

INCDIR =
CFLAGS = -O3 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 
LIBS =

BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PGE Auto Update Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/pge_build.mak
include $(PSPSDK)/lib/build.mak

