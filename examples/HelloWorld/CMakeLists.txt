# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_riscv_executable(HelloWorld
  ${CORE_SRC}
  ${ARDUBOY2_SRC}
  HelloWorld.cpp
)
