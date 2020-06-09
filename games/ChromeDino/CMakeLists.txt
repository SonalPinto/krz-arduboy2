# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(ChromeDino
  ChromeDino.cpp
)

target_link_libraries(ChromeDino
  PUBLIC
    arduboy2
)
