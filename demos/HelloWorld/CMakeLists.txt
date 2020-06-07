# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(HelloWorld
  HelloWorld.cpp
)

target_link_libraries(HelloWorld
  PUBLIC
    arduboy2
)
