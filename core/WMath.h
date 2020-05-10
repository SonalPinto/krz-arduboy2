// Copyright (c) 2020 Sonal Pinto
// SPDX-License-Identifier: Apache-2.0

#ifndef _WMATH_H_
#define _WMATH_H_

#include <stdint.h>

uint32_t random(uint32_t howbig);
uint32_t random(uint32_t howsmall, uint32_t howbig);
void randomSeed(uint32_t seed);

#endif
