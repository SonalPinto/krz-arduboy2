// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

/*
Drivers for KRZBOY SoC and Wrappers for Arduino API calls relevant to Arduboy2 library and games
*/

#ifndef _KRZ_H_
#define _KRZ_H_

#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cmath>
#include <mini-printf.h>

// ============================================================
// KRZ Memory Map

#define MMPTR32(x) (*((volatile uint32_t*)(x)))
#define MMPTR8(x)  (*((volatile uint8_t*)(x)))

#ifndef F_CPU
// KRZ on iCEBreaker: 24MHz system clock using internal oscillator
#define F_CPU               24000000
#endif

// UART TX Queue
#define UART_TXQ_SIZE       128

// SPIM TX/RX Queue
#define SPIM_TXQ_SIZE       128
#define SPIM_RXQ_SIZE       128

// UART TX Buffer
#define UART_BUFFER_SIZE    128
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
/*
riscv32-unknown-elf-g++ -march=rv32i -mabi=ilp32
---- TYPES ----
char = 1
int = 4
long = 4
float = 4
double = 8
*/

// ============================================================
// Drivers

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN
#undef BIN
#endif
#define BIN 2

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

#define PROGMEM
#define PGM_P const char *
#define PGM_VOID_P const void *
#define PSTR(s) ((const PROGMEM char *)(s))

#define pgm_read_byte(x) (*((const uint8_t *)(x)))

#define F

// Arduino Types
typedef unsigned int word;
typedef bool boolean;
typedef uint8_t byte;

// Time
unsigned long millis();
unsigned long micros();
void delay(unsigned long);
void delayMicroseconds(unsigned int us);

void init(void);
void setup(void);
void loop(void);

// #include "WString.h"

// WMath
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

// krz-math
float sink(float);
float cosk(float);

extern "C" {
// Print
void printk(const char *fmt, ...);
int sprintf(char* buffer, const char *fmt, ...);
}

#endif // _KRZ_H_
