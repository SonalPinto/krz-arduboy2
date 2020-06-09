// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#ifndef _KRZ_EEPROM_H_
#define _KRZ_EEPROM_H_

#include <cstdint>
#include <cstring>

/*
"EEPROM" class to mimic config and save-game storage in Arduboy

ref: https://forum.arduino.cc/index.php?topic=312645.0
*/

class KRZ_EEPROM {
public:
  // 1KB in RAM
  static uint8_t MEM[1024];

  KRZ_EEPROM();
  uint8_t read(int address);
  void update(int address, uint8_t value);

  uint8_t get(int address, uint8_t &value);
  void put(int address, uint8_t value);

  uint8_t get(int address, uint16_t &value);
  void put(int address, uint16_t value);
};

// Global instance
extern KRZ_EEPROM EEPROM;

#endif // _KRZ_EEPROM_H_
