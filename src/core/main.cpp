// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <krz.h>

extern "C" {
__attribute__ ((interrupt)) void trap_handler(void);
}

void trap_handler(void) {
  uint32_t mcause, mtval, mepc;

  asm("csrr %0, mcause" : "=r" (mcause));
  asm("csrr %0, mtval" : "=r" (mtval));
  asm("csrr %0, mepc" : "=r" (mepc));

  printk("\n\n-= TRAP =-\n");
  printk("mcause = %x\n", mcause);
  printk("mtval = %x\n", mtval);
  printk("mepc = %x\n", mepc);
  while(1);
}

void init() {
  /*
  [NOTE]

  newlibc's crt0 only sets up the global pointer and initializes the bss.
  It expects the "host envioronment" to setup the critical stack pointer
  before entering the application, which on most embedded solutions is
  non existant. Hence, almost everyone rolls their own crt0.

  However, picolibc brings a breath of fresh air to the embedded libc world
  with a crt0 that actually _initializes_ the stack pointer. Hence, now all
  I need to do is setup the trap handler vector. Done.

  This is merely one of its attractive features. There's also the fine tuned stdlib
  with TLS, and tinystdio. I have no doubt that picolibc will replace newlibc-nano
  for embedded applications.
  */

  // Setup trap handler
  asm("csrw mtvec, %0" : : "r" (trap_handler));
  // Clear out UART Buffer
  memset(uart_buffer, 0x00, UART_BUFFER_SIZE);
}

int main(void) {

  init();

  setup();

  for (;;) {
    loop();
  }

  return 0;
}
