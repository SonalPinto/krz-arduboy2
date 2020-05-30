/*
  main.cpp - Main loop for Arduino sketches
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

#include <Arduino.h>

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
