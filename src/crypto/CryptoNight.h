/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CRYPTONIGHT_H__
#define __CRYPTONIGHT_H__


#include <stddef.h>
#include <stdint.h>

#include "Options.h"

#define MEMORY       2097152 /* 2 MiB */
#define MEMORY_LITE  1048576 /* 1 MiB */
#define MEMORY_SUPER_LITE  524288 /* 512 KiB */
#define MEMORY_ULTRA_LITE  262144 /* 256 KiB */
#define MEMORY_HEAVY 4194304 /* 4 MiB */

#define POW_DEFAULT_INDEX_SHIFT 3
#define POW_XLT_V4_INDEX_SHIFT 4


struct ScratchPad {
    alignas(16) uint8_t state[224]; // 224 instead of 200 to maintain aligned to 16 byte boundaries
    alignas(16) uint8_t* memory;

    // Additional stuff for asm impl
    uint8_t ctx_info[24];
    const void* input;
    uint8_t* variant_table;
    const uint32_t* t_fn;
};

alignas(64) static uint8_t variant1_table[256];
alignas(64) static uint8_t variant_xtl_table[256];

class Job;
class JobResult;

class CryptoNight
{
public:
    static bool init(bool aesni);
    static void hash(const uint8_t *input, size_t size, void *output, ScratchPad **ctx);

public:

private:
    static bool selfTest();
};
