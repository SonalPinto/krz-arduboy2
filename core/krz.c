// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <krz.h>

static inline uint32_t read_mcycle(void) {
  uint32_t tmp;
  asm volatile(
      "csrr %0, mcycle \n"
      : "=r" (tmp)
  );
  return tmp;
}

void delayMicroseconds(uint32_t us) {
  uint32_t start, delay;
  start = read_mcycle();
  delay = us * (F_CPU / 1000000);
  while(read_mcycle() - start < delay);
}

void delay(uint32_t ms) {
  for (uint32_t i=0; i<ms; i++) delayMicroseconds(1000);
}

uint32_t micros(void) {
  return (read_mcycle() / (F_CPU / 1000000));
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

void trap_handler (int mcause, int mtval, int mepc) {
  printk("\n\n-= TRAP =-\n");
  printk("mcause = %x\n", mcause);
  printk("mtval = %x\n", mcause);
  printk("mepc = %x\n", mcause);
  while(1);
}
