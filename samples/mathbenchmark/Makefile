TARGET = pgeMathBenchmarkSample
OBJS = mathbenchmark.o

INCDIR =
CFLAGS = -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBDIR =
LDFLAGS =
LIBS = 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PGE Math Benchmark Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/pge_build.mak
include $(PSPSDK)/lib/build.mak
