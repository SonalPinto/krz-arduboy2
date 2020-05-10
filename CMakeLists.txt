# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.10)

project(krz-arduboy2 C CXX ASM)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(UTILS "${CMAKE_CURRENT_LIST_DIR}/utils")

set(BIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(LIB_OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib")

file(MAKE_DIRECTORY ${BIN_OUTPUT_DIR})
file(MAKE_DIRECTORY ${LIB_OUTPUT_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})

# =============================================================

include(macros)

set(tools /opt/riscv32i)
set(CMAKE_C_COMPILER ${tools}/bin/riscv32-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/riscv32-unknown-elf-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/riscv32-unknown-elf-gcc)
set(OBJCOPY ${tools}/bin/riscv32-unknown-elf-objcopy)
set(OBJDUMP ${tools}/bin/riscv32-unknown-elf-objdump)

add_compile_options(
  -Wall
  -O2
  -march=rv32i
  -mabi=ilp32
  -static
  -nostartfiles
  -fdata-sections -ffunction-sections
  --specs=nano.specs
  --specs=nosys.specs
)

set(LINKER_SCRIPT core/link.ld)
set_realpath(LINKER_SCRIPT)

add_link_options(
  -Wl,--gc-sections
  -T ${LINKER_SCRIPT}
  -static
  -nostartfiles
  --specs=nano.specs
  --specs=nosys.specs 
)

set(CORE_SRC
  core/crt0.S
  core/krz.c
  core/WMath.cpp
  core/mini-printf.c
  core/main.cpp
)

set(ARDUBOY2_SRC
  src/Arduboy2Core.cpp
  src/Arduboy2Audio.cpp
  src/Arduboy2Beep.cpp
  src/SpritesB.cpp
  src/Sprites.cpp
  src/Arduboy2.cpp
)

set_realpath(CORE_SRC)
set_realpath(ARDUBOY2_SRC)

include_directories(SYSTEM
  core
  src
)

function(add_riscv_executable target)
  add_executable(${target}
    ${ARGN}
  )

  set_target_properties(
    ${target}
    PROPERTIES 
      OUTPUT_NAME "${target}"
      SUFFIX ".elf"
  )

  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND
      ${OBJDUMP} -D "${target}.elf" > "${target}.objdump"
    COMMAND
      ${OBJCOPY} -O binary "${target}.elf" "${target}.bin"
    COMMAND
      python3 ${UTILS}/krzprog.py --bin "${target}.bin"
    WORKING_DIRECTORY
      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
endfunction()

# =============================================================

add_subdirectory(examples/basic)
add_subdirectory(examples/HelloWorld)
add_subdirectory(examples/Buttons)
add_subdirectory(examples/ArduBreakout)
