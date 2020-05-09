// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <krz.h>

int main(void) {

  memset(uart_buffer, 0x00, UART_BUFFER_SIZE);

  setup();
    
  for (;;) {
    loop();
  }
        
  return 0;
}
