/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  // --------------------------
  Modified 2020 by Sonal Pinto
*/

/*
Minimal Port of the Arduino API for KRZ:Arduboy2
*/

#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mini-printf.h>

// ============================================================
// KRZ Memory Map

#define MMPTR32(x) (*((volatile uint32_t*)(x)))
#define MMPTR8(x)  (*((volatile uint8_t*)(x)))

// KRZ on iCEBreaker: 24MHz system clock using internal oscillator
#define F_CPU               24000000

// UART TX Queue
#define UART_TXQ_SIZE       128

// SPIM TX/RX Queue
#define SPIM_TXQ_SIZE       128
#define SPIM_RXQ_SIZE       128

// UART TX Buffer
#define UART_BUFFER_SIZE    64
static uint8_t uart_buffer[UART_BUFFER_SIZE];

#define KRZ_GPREG           0x800000
#define KRZ_UART            0x800100
#define KRZ_SPIM            0x800200

#define KRZ_SCRATCH         MMPTR32(KRZ_GPREG | (0<<2))
#define KRZ_BOOTVEC         MMPTR32(KRZ_GPREG | (1<<2))
#define KRZ_GPIO_DIR        MMPTR32(KRZ_GPREG | (2<<2))
#define KRZ_GPIO_WRITE      MMPTR32(KRZ_GPREG | (3<<2))
#define KRZ_GPIO_READ       MMPTR32(KRZ_GPREG | (4<<2))
#define KRZ_UART_CTRL       MMPTR32(KRZ_GPREG | (5<<2))
#define KRZ_UART_STATUS     MMPTR32(KRZ_GPREG | (6<<2))
#define KRZ_SPIM_CTRL       MMPTR32(KRZ_GPREG | (7<<2))
#define KRZ_SPIM_STATUS     MMPTR32(KRZ_GPREG | (8<<2))

#define GPIO0       0
#define GPIO1       1
#define GPIO2       2
#define GPIO3       3
#define GPIO4       4
#define GPIO5       5
#define GPIO6       6
#define GPIO7       7
#define GPIO8       8
#define GPIO9       9
#define GPIO10      10
#define GPIO11      11

#define LEDR        GPIO0
#define LEDG        GPIO1
#define FLASH_CS    GPIO2

// ============================================================
// Drivers

#define HIGH 0x1
#define LOW  0x0

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define INPUT 0x0
#define OUTPUT 0x1

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define DEFAULT 1
#define EXTERNAL 0

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000 )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define _BV(b) (1UL << (b))
#define bit(b) (1UL << (b))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

// Arduino Types
typedef uint16_t word;
typedef bool boolean;
typedef uint8_t byte;

// Time
uint32_t millis(void);
uint32_t micros(void);
void delay(uint32_t);
void delayMicroseconds(uint32_t us);

void init(void);
void setup(void);
void loop(void);

// #include "WString.h"

// WMath
int random(int);
int random(int, int);
void randomSeed(uint32_t);
int map(int, int, int, int, int);

extern "C" {
// Print
void printk(const char *fmt, ...);
__attribute__ ((interrupt)) void trap_handler(void);

}

#endif // _ARDUINO_H_
