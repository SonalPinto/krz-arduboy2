// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#ifndef _KRZ_H_
#define _KRZ_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================
// KRZ Memory Map

#define MMPTR32(x) (*((volatile uint32_t*)(x)))
#define MMPTR8(x)  (*((volatile uint8_t*)(x)))

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

#define LEDR        0
#define LEDG        1
#define FLASH_CS    2
#define OLED_CS     3

#define GPIO0       4
#define GPIO1       5
#define GPIO2       6
#define GPIO3       7
#define GPIO4       8
#define GPIO5       9
#define GPIO6       10
#define GPIO7       11

#define LED2        4
#define LED3        5
#define LED5        6
#define BTN2        7
#define LED1        8
#define LED4        9
#define BTN1        10
#define BTN3        11

// ============================================================
// Drivers

#define HIGH 0x1
#define LOW  0x0

#define _BV(bit) (1UL<<(bit))
#define bit(b)   (1UL << (b))

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

// 24MHz system clock - internal oscillator
#define F_CPU               24000000

// UART TX Queue
#define UART_TXQ_SIZE       128

// SPIM TX/RX Queue
#define SPIM_TXQ_SIZE       128
#define SPIM_RXQ_SIZE       128

// UART TX Buffer
#define UART_BUFFER_SIZE    64
static uint8_t uart_buffer[UART_BUFFER_SIZE];

// GPIO
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

// Math
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))

// Time
uint32_t millis(void);
uint32_t micros(void);
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);

// Print
void printk(const char *fmt, ...);

void setup(void);
void loop(void);

#ifdef __cplusplus
}
#endif

#endif // _KRZ_H_
