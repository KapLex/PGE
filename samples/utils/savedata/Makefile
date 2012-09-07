TARGET = pgeSavedataSample
OBJS = savedata.o

INCDIR =
CFLAGS = -O3 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = 

PSP_EBOOT_ICON = ICON0.PNG
PSP_EBOOT_PIC1 = PIC1.PNG
PSP_EBOOT_SND0 = SND0.AT3

BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PGE Savedata Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/pge_build.mak
include $(PSPSDK)/lib/build.mak
