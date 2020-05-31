# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_library(core STATIC
  common/mini-printf.c
  core/wiring.cpp
  core/WMath.cpp
  core/main.cpp
)

target_include_directories(core SYSTEM
  PUBLIC
    common
    core
)

add_library(arduboy2 STATIC
  EEPROM/EEPROM.cpp
  arduboy2/Arduboy2Core.cpp
  arduboy2/Arduboy2Audio.cpp
  arduboy2/Arduboy2Beep.cpp
  arduboy2/Sprites.cpp
  arduboy2/Arduboy2Print.cpp
  arduboy2/Arduboy2.cpp
)

target_include_directories(arduboy2 SYSTEM
  PUBLIC
    common
    core
    EEPROM
    arduboy2
)

target_link_libraries(arduboy2
  PUBLIC
    core
)
