# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

add_library(core STATIC
  common/mini-printf.c
  core/wiring.cpp
  core/WMath.cpp
  core/Print.cpp
  core/main.cpp
)

target_include_directories(core SYSTEM
  PUBLIC
    common
    core
)
