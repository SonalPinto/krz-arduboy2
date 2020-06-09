// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#ifndef _KRZ_PRINT_H_
#define _KRZ_PRINT_H_

#include <krz.h>

class Print
{
  private:
    size_t printNumber(uint32_t, uint8_t);

  public:
    Print() {}

    virtual size_t write(uint8_t) = 0;

    size_t write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
    }

    size_t write(const uint8_t *buffer, size_t size) {
      size_t n = 0;
      while (size--) {
        if (write(*buffer++)) n++;
        else break;
      }
      return n;
    }

    size_t write(const char *buffer, size_t size) {
      return write((const uint8_t *)buffer, size);
    }

    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);

    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println();
};

#endif // _KRZ_PRINT_H_
