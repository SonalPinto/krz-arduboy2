# Copyright (c) 2020 Sonal Pinto
# SPDX-License-Identifier: Apache-2.0

subdirlist(subdirs ${CMAKE_CURRENT_LIST_DIR})

# foreach(subdir ${subdirs})
#   add_subdirectory($subdir)
# endforeach()

add_subdirectory(blinky)
add_subdirectory(oled)
