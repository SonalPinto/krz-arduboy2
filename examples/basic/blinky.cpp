// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <krz.h>

uint8_t ledr;
uint8_t ledg;
uint8_t b1, b2, b3;
uint32_t ticks;

static void print_banner(void){
  printk("\n\n");
  printk(" ____  __.                                  \n");
  printk("|    |/ _|______  ____   ____   ____  ______\n");
  printk("|      < \\_  __ \\/  _ \\ /    \\ /  _ \\/  ___/\n");
  printk("|    |  \\ |  | \\(  <_> )   |  (  <_> )___ \\ \n");
  printk("|____|__ \\|__|   \\____/|___|  /\\____/____  >\n");
  printk("        \\/                  \\/           \\/ \n\n");
}

void setup () {
  // Init GPIO
  KRZ_GPIO_DIR = (1<<LEDR)
              | (1<<LEDG)
              | (1<<FLASH_CS) 
              | (1<<OLED_CS) 
              | (1<<LED1)
              | (1<<LED2)
              | (1<<LED3)
              | (1<<LED4)
              | (1<<LED5);

  // Set outputs
  //  - turns the LEDs
  //  - deselects flash chips
  KRZ_GPIO_WRITE = (1<<LEDR)
              | (1<<LEDG)
              | (1<<FLASH_CS) 
              | (1<<OLED_CS) 
              | (0<<LED1)
              | (0<<LED2)
              | (0<<LED3)
              | (0<<LED4)
              | (0<<LED5);

  ticks = 0;
  ledg = 0;
  ledr = 1;

  // print banner
  print_banner();
}

void loop() {
  // read buttons, and set pmod LEDs, every 1ms
  b1 = bitRead(KRZ_GPIO_READ, BTN1);
  b2 = bitRead(KRZ_GPIO_READ, BTN2);
  b3 = bitRead(KRZ_GPIO_READ, BTN3);

  bitWrite(KRZ_GPIO_WRITE, LED4, b1);
  bitWrite(KRZ_GPIO_WRITE, LED1, b2);
  bitWrite(KRZ_GPIO_WRITE, LED5, b3);

  delay(1);
  ticks++;

  // then, every 200ms, print buttons and toggle LEDS
  if (ticks == 200) {
    // toggle LEDs
    ledr ^= 1;
    ledg ^= 1;

    bitWrite(KRZ_GPIO_WRITE, LEDR, ledr);
    bitWrite(KRZ_GPIO_WRITE, LEDG, ledg);

    printk("BTN[%u][%u][%u]\n", b1, b2, b3);

    // reset ticks
    ticks = 0;
  }
}

