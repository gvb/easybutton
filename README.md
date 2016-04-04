# easybutton
Repurpose an easy button to say other things

# Software and Sounds

This uses a modified PCM audio driver: https://github.com/gvb/PCM

Create your own .wav files or download selected Simpsons' .wav files from http://www.richmolnar.com/simpsnd.htm (not included). There is a Makefile that uses sox to resample the .wav file(s) to 6KHz (or other rates) and xxd to convert the .wav file(s) to a C include file.

* [Bart - Cool Man](http://www.richmolnar.com/Sounds/Bart%20-%20Cool%20Man.wav)
* [Bart - I didn't do it](http://www.richmolnar.com/Sounds/Bart%20-%20I%20didn't%20do%20it.wav)
* [Homer - D'oh!](http://www.richmolnar.com/Sounds/Homer%20-%20D'oh!%20(1).wav)
* [Homer - Everyone is stupid except me](http://www.richmolnar.com/Sounds/Homer%20-%20Everyone%20is%20stupid.wav)
* [Homer - Giggles](http://www.richmolnar.com/Sounds/Homer%20-%20Giggles.wav)
* [Homer - Woohoo!](http://www.richmolnar.com/Sounds/Homer%20-%20Woohoo!%20(1).wav)
* [Lisa - Noooo!](http://www.richmolnar.com/Sounds/Lisa%20-%20Noooo!.wav)
* [Nelson - Ha ha!](http://www.richmolnar.com/Sounds/Nelson%20-%20Ha%20ha.wav)

# Hardware

* [Arduino Pro Mini 328 - 3.3V/8MHz](https://www.sparkfun.com/products/11114) - use the 3.3v one with the on-board linear regulator disabled. This allows it to run directly off the two AAA batteries of the easy button, minimizing current draw.
* [SparkFun Mono Audio Amp Breakout - TPA2005D1](https://www.sparkfun.com/products/11044) - Audio amp to drive the speaker from the Arduino output.

Pins:
* 2 - Button. The button input uses the weak pullup capability of the Arduino and needs it to be grounded when the switch is pressed. This is configured to interrupt when it goes low, waking up the Arduino and starting the playback.
* 7 - Wired to the amplifier shutdown pin. This is used to minimizing current draw when it isn't active.
* 11 - Audio output to drive the speaker (defined in PCM.c).
