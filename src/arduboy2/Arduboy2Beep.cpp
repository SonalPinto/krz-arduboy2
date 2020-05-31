/**
 * @file Arduboy2Beep.cpp
 * \brief
 * Classes to generate simple square wave tones on the Arduboy speaker pins.
 */

#include <krz.h>
#include "Arduboy2Beep.h"

uint8_t BeepPin1::duration = 0;

void BeepPin1::begin()
{
}

void BeepPin1::tone(uint16_t count)
{
  // TODO: Implement BeepPin1::tone(uint16_t count)

  //tone(count, 0);
}

void BeepPin1::tone(uint16_t count, uint8_t dur)
{
  // Intentionally unused
  static_cast<void>(count);

  duration = dur;
}

void BeepPin1::timer()
{
  if(duration > 0)
    --duration;
}

void BeepPin1::noTone()
{
  duration = 0;
}


uint8_t BeepPin2::duration = 0;

void BeepPin2::begin()
{
}

void BeepPin2::tone(uint16_t count)
{
  // TODO: Implement BeepPin2::tone(uint16_t count)

  //tone(count, 0);
}

void BeepPin2::tone(uint16_t count, uint8_t dur)
{
  // Intentionally unused
  static_cast<void>(count);

  duration = dur;
}

void BeepPin2::timer()
{
  if(duration > 0)
    --duration;
}

void BeepPin2::noTone()
{
  duration = 0;
}
