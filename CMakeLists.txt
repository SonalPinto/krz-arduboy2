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

set(tools $ENV{RISCV_TOOLCHAIN_DIR})
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
  -ffunction-sections
  -fdata-sections
  -fno-exceptions
  --specs=picolibc.specs
)

set(LINKER_SCRIPT src/core/link.ld)
set_realpath(LINKER_SCRIPT)

add_link_options(
  -Wl,--gc-sections
  -static
  --specs=picolibc.specs
  -T ${LINKER_SCRIPT}
)

add_subdirectory(src)

# =============================================================

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
      ${OBJDUMP} -drC "${target}.elf" > "${target}.objdump"
    COMMAND
      ${OBJCOPY} -O binary "${target}.elf" "${target}.bin"
    COMMAND
      python3 ${UTILS}/krzprog.py --bin "${target}.bin"
    WORKING_DIRECTORY
      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
endfunction()

# =============================================================

add_subdirectory(demos)
add_subdirectory(games)
