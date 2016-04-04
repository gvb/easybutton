
#include <avr/sleep.h>
#include <PCM.h>

#include "Bart_Ididntdoit.h"
#include "Bart_CoolMan.h"
#include "Homer_Doh.h"
#include "Homer_Woohoo.h"
#include "Nelson_Ha_ha.h"
#include "Lisa_Noooo.h"
#include "Homer_EveryoneIsStupid.h"
#include "Homer_Giggles.h"

const uint8_t buttonPin = 2;
const uint8_t shutdownPin = 7;

#define _countof(a)  (sizeof(a) / sizeof(a[0]))

int index;

#define SAMPLE_RATE 6000

// With no audio, the program takes 1,698 bytes of 30,720
// Remainder: 29000 bytes

struct {
  const unsigned char *audio;
  const int len;
  const int sampleRate;
} a[] = {
  {Bart_Ididntdoit, sizeof(Bart_Ididntdoit), SAMPLE_RATE}, // 5158 @8000
//  {Bart_CoolMan, sizeof(Bart_CoolMan), SAMPLE_RATE}, // 10062 @8000
  {Homer_Doh, sizeof(Homer_Doh), SAMPLE_RATE}, // 2824 @8000
  {Homer_Woohoo, sizeof(Homer_Woohoo), SAMPLE_RATE}, // 7294 @8000
//  {Nelson_Ha_ha, sizeof(Nelson_Ha_ha), SAMPLE_RATE}, // 7726 @8000
  {Lisa_Noooo, sizeof(Lisa_Noooo), SAMPLE_RATE}, // 19564 @8000
// Too large:
//  {Homer_EveryoneIsStupid, sizeof(Homer_EveryoneIsStupid), SAMPLE_RATE}, // 27836 @8000
//  {Homer_Giggles, sizeof(Homer_Giggles), SAMPLE_RATE}, // 45344 @8000
};

void wakeup(void)
{
  if (!playing) {
    digitalWrite(shutdownPin, 1);
    startPlaybackSpeed(a[index].audio, a[index].len, a[index].sampleRate);
    if (index < _countof(a) - 1)
      index++;
    else
      index = 0;
  }
}

void shutdown(void)
{
  if (!playing) {
    digitalWrite(shutdownPin, 0);

    /*
     * The 5 different modes are:
     * SLEEP_MODE_IDLE         -the least power savings
     * SLEEP_MODE_ADC
     * SLEEP_MODE_PWR_SAVE
     * SLEEP_MODE_STANDBY
     * SLEEP_MODE_PWR_DOWN     -the most power savings
     */
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable(); // Go to sleep here, resume after here.
  }
}

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(shutdownPin, OUTPUT);
  digitalWrite(shutdownPin, 0);

  // Falling edge of interrupt 0 (pin 2) wakes us up
  attachInterrupt(0, wakeup, FALLING);
  index = 0;

  // Register our shutdown function for end of playback
  donePlaying = shutdown;

  shutdown();
}

void loop()
{
  // Nothing to do in the loop so save power
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable(); // Go to sleep here, resume after here.
}

