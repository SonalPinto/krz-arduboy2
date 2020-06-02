// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <krz.h>

// ============================================================
// wiring
// ============================================================

static inline uint32_t read_mcycle(void) {
  uint32_t tmp;
  asm volatile("csrr %0, mcycle": "=r" (tmp));
  return tmp;
}

void delayMicroseconds(unsigned int us) {
  unsigned int start, delay;
  start = read_mcycle();
  delay = us * clockCyclesPerMicrosecond();
  while(read_mcycle() - start < delay);
}

void delay(unsigned long ms) {
  for (unsigned long i=0; i<ms; i++) delayMicroseconds(1000);
}

unsigned long micros(void) {
  return clockCyclesToMicroseconds(read_mcycle());
}

unsigned long millis(void) {
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

int sprintf(char* buffer, const char *fmt, ...) {
  int len;

  // Format using mini-printf
  va_list va;
  va_start(va, fmt);
  len = mini_vsnprintf(buffer, UART_BUFFER_SIZE, fmt, va);
  va_end(va);

  return len;
}

// ============================================================
// WMath
// ============================================================
void randomSeed(unsigned long seed)
{
  if (seed != 0) {
    srand(seed);
  }
}

long random(long howbig)
{
  if (howbig == 0) {
    return 0;
  }
  return rand() % howbig;
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

