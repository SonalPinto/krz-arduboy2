/*
  DEMO: siNe DeMo

  TEAM a.r.g.: http://www.team-arg.com/demos.html

  2015 - JO3RI

  Demo License: MIT : https://opensource.org/licenses/MIT

*/

// All of this could have been done with precaculated values
// even with bitmaps, but what is the fun in that. I wanted to see
// how fast the demo can run with pure calculation.


#include <Arduboy2.h>
#include "bitmaps.h"

Arduboy2Base arduboy;

int i = 0;
float d = 0.0;
int c = 129;

void setup() {
  // Cleanup the display
  //______________________________
  arduboy.begin();
  arduboy.clear();
  arduboy.display();

  // first we'll show some bitmaps
  //______________________________

  // JO3RI Logo
  arduboy.drawBitmap(20, 4, JO3RI, 88, 56, WHITE);
  arduboy.display();
  delay(1500);
  arduboy.clear();

  //member
  arduboy.drawBitmap(3, 16, memberOf, 122, 32, WHITE);
  arduboy.display();
  delay(1500);
  arduboy.clear();

  // TEAM a.r.g. Logo
  arduboy.drawBitmap(34, 4, T_arg, 60, 56, WHITE);
  arduboy.display();
  delay(1500);
  arduboy.clear();

  //presents
  arduboy.drawBitmap(18, 4, presents, 92, 24, WHITE);

  //SiNe-DeMo
  arduboy.drawBitmap(0, 36, sineDemo, 128, 24, WHITE);
  arduboy.display();
  delay(3000);
  arduboy.clear();
}

void loop() {

  float p = 2 * sink(d);
  float q = 2 * sink(-d);
  arduboy.clear();

  for (byte k = 2; k < 15; k++) {
    // some calculations are used multiple times
    // so better caclutate them once and reuse
    // the results.
    float r = sink(d + (k * 0.4));
    float t = sink(d + 3 + (k * 0.4));

    // First lets draw the top 12 bals
    arduboy.fillCircle(k * 8 + p, 12 + (r * 10), 2, 1);
    // and now the bottom 12 balls
    arduboy.fillCircle(k * 8 + q, 12 + (t * 10), 2, 1);

    // now we draw a line from the top ball to the bottom ball
    arduboy.drawLine(k * 8 + p, 10 + (r * 10), k * 8 + q, (10 + t * 10), 1);

    // and finally we need a line from ball to ball on the top part
    arduboy.drawLine((k * 8 + p), 12 + (r * 10), 6 + (k * 8 + p), (12 + sink(d + ((k + 1) * 0.4)) * 10), 1);

    // and the bottom part
    arduboy.drawLine((k * 8 + q), 12 + (t * 10), 6 + (k * 8 + q), (12 + sink(d + 3 + ((k + 1) * 0.4)) * 10), 1);
  }

  // begin wobbling text
  //____________________

  // We could use font, but it's to small, so I made
  // little bitmaps for each letter. Next to that, if
  // we would use font, we need each letter to separated
  // in an array.
  // Now let's put each letter on the sine wave
  // int c makes the letters move right to left
  // and sine calculation makes them go up an down
  arduboy.drawBitmap(c, 32 - sink(d + (0 * 0.4)) * 5, LetterH, 8, 8, 1);
  arduboy.drawBitmap(c + 10, 32 - sink(d + (1 * 0.4)) * 5, LetterE, 8, 8, 1);
  arduboy.drawBitmap(c + 20, 32 - sink(d + (2 * 0.4)) * 5, LetterL, 8, 8, 1);
  arduboy.drawBitmap(c + 30, 32 - sink(d + (3 * 0.4)) * 5, LetterL, 8, 8, 1);
  arduboy.drawBitmap(c + 40, 32 - sink(d + (4 * 0.4)) * 5, LetterO, 8, 8, 1);
  arduboy.drawBitmap(c + 50, 32 - sink(d + (5 * 0.4)) * 5, Letter, 8, 8, 1);
  arduboy.drawBitmap(c + 60, 32 - sink(d + (6 * 0.4)) * 5, LetterA, 8, 8, 1);
  arduboy.drawBitmap(c + 70, 32 - sink(d + (7 * 0.4)) * 5, LetterR, 8, 8, 1);
  arduboy.drawBitmap(c + 80, 32 - sink(d + (8 * 0.4)) * 5, LetterD, 8, 8, 1);
  arduboy.drawBitmap(c + 90, 32 - sink(d + (9 * 0.4)) * 5, LetterU, 8, 8, 1);
  arduboy.drawBitmap(c + 100, 32 - sink(d + (10 * 0.4)) * 5, LetterB, 8, 8, 1);
  arduboy.drawBitmap(c + 110, 32 - sink(d + (11 * 0.4)) * 5, LetterO, 8, 8, 1);
  arduboy.drawBitmap(c + 120, 32 - sink(d + (12 * 0.4)) * 5, LetterY, 8, 8, 1);
  // end wobbling text


  // rotating lines
  //_______________

  // each line is devided in 16 small parts (byte k)
  // the small parts are actually rectangles growing bigger
  // and smaller so they seem to come in to the front and then
  // go to the background.

  // growing and shrinking of the rectangles is a sine calculation
  // and so is the moving of the lines too.
  for (byte k = 2; k < 20; k++) {
    // the first line
    arduboy.drawRect(k * 6 + (p / 2), 54 + (sink(d + (k * 0.1)) * 6), 4, 1 + (p / 2), 1);
    // the second line is actually the same line,
    // but evolved 1/3 further in the sine calculation
    arduboy.drawRect(k * 6 + (sink(d + 2)), 54 + (sink(d + 2 + (k * 0.1)) * 6), 4, 1 + sink(d + 2), 1);
    // the third line is actually the same line,
    // but evolved 2/3 further in the sine calculation
    arduboy.drawRect(k * 6 + (sink(d + 4)), 54 + (sink(d + 4 + (k * 0.1)) * 6), 4, 1 + sink(d + 4), 1);
  }
  // int c is supstracted to move those letters
  // right to left. If all letters are offscreen
  // let's start over
  c--;
  if (c == -130) c = 129;

  // float d goes 1 step further on the sine evolution
  d = d + 0.10;

  // update the screen so all those parts are drown
  arduboy.display();
}

