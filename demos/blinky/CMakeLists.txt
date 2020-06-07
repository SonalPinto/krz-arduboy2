# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(blinky
  blinky.cpp
)

target_link_libraries(blinky
  PUBLIC
    core
)
