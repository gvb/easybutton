
SAMPLE_RATE=6000

.phony : all clean

all : Bart_CoolMan.h Bart_Ididntdoit.h Homer_Doh.h \
	Homer_EveryoneIsStupid.h Homer_Giggles.h Homer_Woohoo.h \
	Lisa_Noooo.h Nelson_Ha_ha.h

Bart_CoolMan.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Bart%20-%20Cool%20Man.wav"

Bart_Ididntdoit.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Bart%20-%20I%20didn't%20do%20it.wav"

Homer_Doh.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Homer%20-%20D'oh!%20(1).wav"

Homer_EveryoneIsStupid.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Homer%20-%20Everyone%20is%20stupid.wav"

Homer_Giggles.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Homer%20-%20Giggles.wav"

Homer_Woohoo.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Homer%20-%20Woohoo!%20(1).wav"

Lisa_Noooo.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Lisa%20-%20Noooo!.wav"

Nelson_Ha_ha.wav :
	curl -o $@ "http://www.richmolnar.com/Sounds/Nelson%20-%20Ha%20ha.wav"

Bart_CoolMan.h : Bart_CoolMan.wav

Bart_Ididntdoit.h : Bart_Ididntdoit.wav

Homer_Doh.h : Homer_Doh.wav

Homer_EveryoneIsStupid.h : Homer_EveryoneIsStupid.wav

Homer_Giggles.h : Homer_Giggles.wav

Homer_Woohoo.h : Homer_Woohoo.wav

Lisa_Noooo.h : Lisa_Noooo.wav

Nelson_Ha_ha.h : Nelson_Ha_ha.wav

clean :
	rm -f Bart_CoolMan.h Bart_Ididntdoit.h dohdoh.h Homer_Doh.h \
	Homer_EveryoneIsStupid.h Homer_Giggles.h Homer_Woohoo.h \
	Lisa_Noooo.h Nelson_Ha_ha.h

# Convert a wav audio file into a .h header file
%.h : %.wav
	@echo "Converting $^ to $@"
	@sox $^ -n stat -v 2> $(basename $@).gain
	@echo "const static unsigned char $(basename $@)[] PROGMEM = {" > $(basename $@).h
	@sox $^ -c 1 -r ${SAMPLE_RATE} -e unsigned-integer -b 8 -t wav - \
		gain `cat $(basename $@).gain` |\
		xxd -i - - >> $(basename $@).h
	@echo "};" >> $(basename $@).h
	@rm -f $(basename $@).gain
