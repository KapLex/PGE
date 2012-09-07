TARGET = pgelua
VERSION = 3

OBJS = ../pge.o ../pgeVram.o ../support/pgesupport.o pgeLuaIni.o pgeLua.o

BUILD_PRX = 1

PRX_EXPORTS = exports.exp

LIBS = -llua -lm

PSPBIN = $(shell psp-config --psp-prefix)

CFLAGS = $(DEFINES) -O3 -G0 -Wall -Wextra -mno-explicit-relocs $(shell $(PSPBIN)/bin/freetype-config --cflags) -g -D__PSP__ -DPGE_VERSION=$(VERSION)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_EBOOT_ICON = ICON0.PNG

PSP_EBOOT_TITLE = Phoenix Game Engine Lua (0.03)

EXTRA_TARGETS = EBOOT.PBP

PSP_FW_VERSION = 340

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

release:
	rm -Rf *.o
	$(MAKE) -C ../support clean
	$(MAKE) -C ../support
	$(MAKE) -C ../support files
	$(MAKE) -C adhoc clean
	$(MAKE) -C adhoc
	$(MAKE) -C controls clean
	$(MAKE) -C controls
	$(MAKE) -C dir clean
	$(MAKE) -C dir
	$(MAKE) -C file clean
	$(MAKE) -C file
	$(MAKE) -C font clean
	$(MAKE) -C font
	$(MAKE) -C gfx clean
	$(MAKE) -C gfx
	$(MAKE) -C math clean
	$(MAKE) -C math
	$(MAKE) -C mp3 clean
	$(MAKE) -C mp3
	$(MAKE) -C net clean
	$(MAKE) -C net
	$(MAKE) -C system clean
	$(MAKE) -C system
	$(MAKE) -C texture clean
	$(MAKE) -C texture
	$(MAKE) -C timer clean
	$(MAKE) -C timer
	$(MAKE) -C usb clean
	$(MAKE) -C usb
	$(MAKE) -C utils clean
	$(MAKE) -C utils
	$(MAKE) -C wav clean
	$(MAKE) -C wav
	$(MAKE) -C zip clean
	$(MAKE) -C zip
	mkdir -p release
	mkdir -p release/modules
	mkdir -p release/samples
	cp -Rf adhoc/pge.adhoc.prx release/modules/pge.adhoc.prx
	cp -Rf controls/pge.controls.prx release/modules/pge.controls.prx
	cp -Rf dir/pge.dir.prx release/modules/pge.dir.prx
	cp -Rf file/pge.file.prx release/modules/pge.file.prx
	cp -Rf font/pge.font.prx release/modules/pge.font.prx
	cp -Rf gfx/pge.gfx.prx release/modules/pge.gfx.prx
	cp -Rf math/pge.math.prx release/modules/pge.math.prx
	cp -Rf mp3/pge.mp3.prx release/modules/pge.mp3.prx
	cp -Rf net/pge.net.prx release/modules/pge.net.prx
	cp -Rf system/pge.system.prx release/modules/pge.system.prx
	cp -Rf texture/pge.texture.prx release/modules/pge.texture.prx
	cp -Rf timer/pge.timer.prx release/modules/pge.timer.prx
	cp -Rf usb/pge.usb.prx release/modules/pge.usb.prx
	cp -Rf utils/pge.utils.prx release/modules/pge.utils.prx
	cp -Rf wav/pge.wav.prx release/modules/pge.wav.prx
	cp -Rf zip/pge.zip.prx release/modules/pge.zip.prx
	cp -Rf EBOOT.PBP release/EBOOT.PBP
	cp -Rf pge.ini release/pge.ini
	cp -Rf logo.png release/logo.png
	cp -Rf verdana.ttf release/verdana.ttf
	cp -Rf samples /release/samples