CFLAGS += $(shell $(PSPBIN)/bin/freetype-config --cflags) -D__PSP__
LIBS += -lpge -lpspgum_vfpu -lpspvfpu -lpspgu -lpspsdk -lpspaudio -lpspaudiocodec -lpsprtc -lpspwlan -lpng -lz -lpsppower -lm -lpspnet_adhoc -lpspnet_adhocctl -lpspnet_adhocmatching -lpsphttp -lpspusb -lpspusbstor -lpspopenpsid
PSPBIN = $(shell psp-config --psp-prefix)
LIBS += $(shell $(PSPBIN)/bin/freetype-config --libs)