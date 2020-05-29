/*
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

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

  // --------------------------
  Modified 2020 by Sonal Pinto
*/

#include <Arduino.h>

static inline uint32_t read_mcycle(void) {
  uint32_t tmp;
  asm volatile("csrr %0, mcycle": "=r" (tmp));
  return tmp;
}

void delayMicroseconds(uint32_t us) {
  uint32_t start, delay;
  start = read_mcycle();
  delay = us * clockCyclesPerMicrosecond();
  while(read_mcycle() - start < delay);
}

void delay(uint32_t ms) {
  for (uint32_t i=0; i<ms; i++) delayMicroseconds(1000);
}

uint32_t micros(void) {
  return clockCyclesToMicroseconds(read_mcycle());
}

uint32_t millis(void) {
  return (micros() / 1000);
}

void printk(const char *fmt, ...) {
  int len;

  // Format using mini-printf
  va_list va;
  va_start(va, fmt);
  len = mini_vsnprintf((char*)uart_buffer, UART_BUFFER_SIZE, fmt, va);
  va_end(va);

  // guard against overflows or null strings
  if (len <= 0) return;

  // transmit over UART
  uint8_t *p = uart_buffer;
  for (uint8_t i=0; i<len; i++) {
    // Wait until there's space in the UART TX Queue
    while ((KRZ_UART_STATUS & 0x00ff) > UART_TXQ_SIZE);
    MMPTR8(KRZ_UART) = *p;
    p++;
  }
}
