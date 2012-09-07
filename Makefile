STATICLIB = libpge.a
TARGET = pge
VERSION = 3

LIBOBJS = support/pgesupport.o pgeWav.o pgeTimer.o pgeMath.o pgeVram.o pgeFont.o pgeControls.o pgeGfx.o pgeTexture.o pgeZip.o pgeMp3.o pgeUtils.o pgeNet.o pgeAdhoc.o pgeFile.o pgeDir.o pgeObj.o pgeUsb.o pgeSystem.o pge.o
OBJS = $(LIBOBJS)

CFLAGS = $(DEFINES) -O3 -G0 -Wall -g -D__PSP__ -DPGE_VERSION=$(VERSION)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
PSP_FW_VERSION = 340

PSPSDK = $(shell psp-config --pspsdk-path)
PSPBIN = $(shell psp-config --psp-prefix)
CFLAGS += $(shell $(PSPBIN)/bin/freetype-config --cflags)
include $(PSPSDK)/lib/build.mak

lib: $(STATICLIB)

$(STATICLIB): $(LIBOBJS)
	$(AR) rcs $@ $(LIBOBJS)
	$(RANLIB) $@

install:
	cp -f pge_build.mak $(PSPSDK)/lib/
	mkdir -p $(PSPSDK)/include/pge/
	cp -f pgeWav.h $(PSPSDK)/include/pge/
	cp -f pgeTimer.h $(PSPSDK)/include/pge/
	cp -f pgeMath.h $(PSPSDK)/include/pge/
	cp -f pge.h $(PSPSDK)/include/pge/
	cp -f pgeNet.h $(PSPSDK)/include/pge/
	cp -f pgeFont.h $(PSPSDK)/include/pge/
	cp -f pgeVram.h $(PSPSDK)/include/pge/
	cp -f pgeControls.h $(PSPSDK)/include/pge/
	cp -f pgeGfx.h $(PSPSDK)/include/pge/
	cp -f pgeTexture.h $(PSPSDK)/include/pge/
	cp -f pgeZip.h $(PSPSDK)/include/pge/
	cp -f pgeMp3.h $(PSPSDK)/include/pge/
	cp -f pgeUtils.h $(PSPSDK)/include/pge/
	cp -f pgeAdhoc.h $(PSPSDK)/include/pge/
	cp -f pgeFile.h $(PSPSDK)/include/pge/
	cp -f pgeEmulator.h $(PSPSDK)/include/pge/
	cp -f pgeObj.h $(PSPSDK)/include/pge/
	cp -f pgeParticle.h $(PSPSDK)/include/pge/
	cp -f pgeUsb.h $(PSPSDK)/include/pge/
	cp -f $(STATICLIB) $(PSPSDK)/lib/

supportfiles:
	$(MAKE) -C support clean
	$(MAKE) -C support
	$(MAKE) -C support files