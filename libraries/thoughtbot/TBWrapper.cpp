
/*
 * TBWrapper.cpp - Library to wrap the setup and loop functions.
 * Created by Tony DiPasquale, February 11, 2014.
 * Released into the public domain.
 */

#include "Arduino.h"

// Libraries for power regulation
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

#include "TBWrapper.h"

volatile int __watch_dog_timer_flag = 1;

ISR(WDT_vect)
{
  if (__watch_dog_timer_flag == 0) {
    __watch_dog_timer_flag = 1;
  }
}

void enterSleepMode(void);

void setup()
{
  MCUSR &= ~(1<<WDRF);
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1 << WDP1 | 1 << WDP2;
  WDTCSR |= _BV(WDIE);

  clientSetup();
}

void loop()
{
  if (__watch_dog_timer_flag == 1) {
    __watch_dog_timer_flag = 0;
    clientLoop();
    enterSleepMode();
  }
}

void enterSleepMode()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  sleep_disable();
  power_all_enable();
}

