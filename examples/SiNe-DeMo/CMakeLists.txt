# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(SiNe-DeMo
  SiNe-DeMo.cpp
)

target_link_libraries(SiNe-DeMo
  PUBLIC
    arduboy2
)
