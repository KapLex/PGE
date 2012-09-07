TARGET = pgeWavSample
OBJS = wavtest.o eightbitstereo.o

INCDIR =
CFLAGS = -O3 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS =

BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP
EXTRA_CLEAN = eightbitmono.c

PSP_EBOOT_TITLE = PGE Wav Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/pge_build.mak
include $(PSPSDK)/lib/build.mak

wavtest.o: eightbitmono.c

# Use bin2c to convert the WAV file 
eightbitmono.c: 8bitmono.wav
	bin2c $< $@ eightbitmono

# Use bin2o to convert the WAV file
eightbitstereo.o: 8bitstereo.wav
	bin2o -i 8bitstereo.wav eightbitstereo.o eightbitstereo

