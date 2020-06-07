// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include "EEPROM.h"

uint8_t EEPROM_t::MEM[];

EEPROM_t::EEPROM_t(){
  // A fresh EEPROM has bits all high
  memset(MEM, 0xff, 1024);
}

uint8_t EEPROM_t::read(int address) {
  return MEM[address];
}
void EEPROM_t::update(int address, uint8_t value) {
  MEM[address] = value;
}

uint8_t EEPROM_t::get(int address, uint8_t &value){
  return MEM[address];
}
void EEPROM_t::put(int address, uint8_t value){
   MEM[address] = value;
}

uint8_t EEPROM_t::get(int address, uint16_t &value){
  return *((uint16_t*)&MEM[address]);
}
void EEPROM_t::put(int address, uint16_t value){
  *((uint16_t*)&MEM[address]) = value;
}

// Global instance
EEPROM_t EEPROM;
