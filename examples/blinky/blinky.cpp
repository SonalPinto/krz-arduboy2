// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include <Arduino.h>

uint8_t ledr;
uint8_t ledg;

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
              | (1<<FLASH_CS);

  // Set outputs
  //  - turns the LEDs off
  //  - deselects flash chip
  KRZ_GPIO_WRITE = (1<<LEDR)
              | (1<<LEDG)
              | (1<<FLASH_CS);

  ledg = 0;
  ledr = 1;

  // print banner
  print_banner();

  printk("---- TYPES ----\n");
  printk("char = %d\n", sizeof(char));
  printk("int = %d\n", sizeof(int));
  printk("long = %d\n", sizeof(long));
  printk("float = %d\n", sizeof(float));
  printk("double = %d\n", sizeof(double));
}

void loop() {
  delay(200);

  // toggle LEDs
  ledr ^= 1;
  ledg ^= 1;

  bitWrite(KRZ_GPIO_WRITE, LEDR, ledr);
  bitWrite(KRZ_GPIO_WRITE, LEDG, ledg);
}

