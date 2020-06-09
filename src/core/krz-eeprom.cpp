// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#include "krz-eeprom.h"

uint8_t KRZ_EEPROM::MEM[];

KRZ_EEPROM::KRZ_EEPROM(){
  // A fresh EEPROM has bits all high
  memset(MEM, 0xff, 1024);
}

uint8_t KRZ_EEPROM::read(int address) {
  return MEM[address];
}
void KRZ_EEPROM::update(int address, uint8_t value) {
  MEM[address] = value;
}

uint8_t KRZ_EEPROM::get(int address, uint8_t &value){
  return MEM[address];
}
void KRZ_EEPROM::put(int address, uint8_t value){
   MEM[address] = value;
}

uint8_t KRZ_EEPROM::get(int address, uint16_t &value){
  return *((uint16_t*)&MEM[address]);
}
void KRZ_EEPROM::put(int address, uint16_t value){
  *((uint16_t*)&MEM[address]) = value;
}

// Global instance
KRZ_EEPROM EEPROM;
