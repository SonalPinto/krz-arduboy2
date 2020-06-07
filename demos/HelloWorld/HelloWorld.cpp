// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <Arduboy2.h>

// make an instance of arduboy used for many functions
Arduboy2 arduboy;

uint8_t y;

void setup () {
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(15);

  y = 0;
}

void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();

  // we set our cursor 5 pixels to the right and 10 down from the top
  // (positions start at 0, 0)
  arduboy.setCursor(4, y++);

  if (y >= 64) y = 0;

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(F("Hello, world!"));

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}
