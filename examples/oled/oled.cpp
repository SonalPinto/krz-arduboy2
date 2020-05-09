// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <Arduboy2Core.h>

Arduboy2Core acore;

uint8_t display[1024];
uint8_t line = 0x01;

void setup () {
  acore.boot();
  acore.paintScreen(display, true);
}

void loop() {
  acore.paint8Pixels(line);
  line = (line << 1) | (line>>7);
  delay(10);
}
