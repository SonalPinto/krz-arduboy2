# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(oled
  oled.cpp
)

target_link_libraries(oled
  PUBLIC
    arduboy2
)
