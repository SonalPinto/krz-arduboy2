#include "Arduboy2.h"

/** \Functions: Arduboy2Print
* \brief
* The `Print` functions are available for writing text to the screen
* buffer.
*
* \details
*
* Print will use the `write()` function to actually draw each character
* in the screen buffer.
*
* See:
* https://www.arduino.cc/en/Serial/Print
*
* Example:
* \code{.cpp}
* int value = 42;
*
* arduboy.println("Hello World"); // Prints "Hello World" and then moves the
*                                 // text cursor to the start of the next line
* arduboy.print(value);  // Prints "42"
* arduboy.print('\n');   // Moves the text cursor to the start of the next line
* arduboy.print(78, HEX) // Prints "4E" (78 in hexadecimal)
* \endcode
*
* \see Arduboy2::write()
*/

size_t Arduboy2::write(uint8_t c)
{
  if (c == '\n')
  {
    cursor_y += textSize * 8;
    cursor_x = 0;
  }
  else if (c == '\r')
  {
    // skip em
  }
  else
  {
    drawChar(cursor_x, cursor_y, c, textColor, textBackground, textSize);
    cursor_x += textSize * 6;
    if (textWrap && (cursor_x > (WIDTH - textSize * 6)))
    {
      // calling ourselves recursively for 'newline' is
      // 12 bytes smaller than doing the same math here
      write('\n');
    }
  }
  return 1;
}

size_t Arduboy2::write(const char *str) {
  if (str == NULL) return 0;
  return write((const uint8_t *)str, strlen(str));
}

size_t Arduboy2::write(const uint8_t *buffer, size_t size) {
  size_t n = 0;
  while (size--) {
    if (write(*buffer++)) n++;
    else break;
  }
  return n;
}

size_t Arduboy2::write(const char *buffer, size_t size) {
  return write((const uint8_t *)buffer, size);
}

size_t Arduboy2::print(const char str[])
{
  return write(str);
}

size_t Arduboy2::print(char c)
{
  return write(c);
}

size_t Arduboy2::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

size_t Arduboy2::print(int n, int base)
{
  return print((long) n, base);
}

size_t Arduboy2::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

size_t Arduboy2::print(long n, int base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t Arduboy2::print(unsigned long n, int base)
{
  if (base == 0) return write(n);
  else return printNumber(n, base);
}

size_t Arduboy2::println()
{
  return write("\r\n");
}

size_t Arduboy2::println(const char c[])
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Arduboy2::println(char c)
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Arduboy2::println(unsigned char b, int base)
{
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t Arduboy2::println(int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Arduboy2::println(unsigned int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Arduboy2::println(long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Arduboy2::println(unsigned long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Arduboy2::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return write(str);
}
