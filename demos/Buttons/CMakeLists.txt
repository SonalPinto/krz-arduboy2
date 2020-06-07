# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(Buttons
  Buttons.cpp
)

target_link_libraries(Buttons
  PUBLIC
    arduboy2
)
