/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Wiring project - http://wiring.org.co
  Copyright (c) 2004-06 Hernando Barragan
  Modified 13 August 2006, David A. Mellis for Arduino - http://www.arduino.cc/
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

extern "C" {
  #include "stdint.h"
  #include "stdlib.h"
}

static uint32_t random_seed = 0;

static inline uint32_t read_mcycle(void) {
  uint32_t tmp;
  asm volatile(
      "csrr %0, mcycle \n"
      : "=r" (tmp)
  );
  return tmp;
}

void randomSeed(uint32_t seed)
{
  if (seed != 0) {
    random_seed = seed;
  }
}

uint32_t random(uint32_t howbig)
{
  if (howbig == 0) {
    return 0;
  }
  return (read_mcycle() ^ random_seed) % howbig;
}

uint32_t random(uint32_t howsmall, uint32_t howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  uint32_t diff = howbig - howsmall;
  return random(diff) + howsmall;
}
