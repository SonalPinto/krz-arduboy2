// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <cstdint>
#include <cstring>

/*
"EEPROM" class to mimic config and save-game storage in Arduboy

ref: https://forum.arduino.cc/index.php?topic=312645.0
*/

class EEPROM_t {
public:
  // 1KB in RAM
  static uint8_t MEM[1024];

  EEPROM_t();
  uint8_t read(int address);
  void update(int address, uint8_t value);
};

// Global instance
extern EEPROM_t EEPROM;

#endif
