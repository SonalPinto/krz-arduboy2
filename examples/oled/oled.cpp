// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <Arduboy2Core.h>

Arduboy2Core arducore;

uint8_t c;
int pattern, iteration;

void setup () {
  arducore.boot();
  arducore.blank();

  iteration = 0;
  pattern = 1;
  c = pattern;
}

void loop() {
  delay(1);
  arducore.paint8Pixels(c);
  c = (c << 1) | (c >> 7);

  iteration++;
  if (iteration == 1024) {
    pattern++;
    c = pattern;

    delay(500);
    arducore.blank();
    iteration = 0;
    delay(500);
  }
}
