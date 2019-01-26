/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 * Copyright 2018      Sebastian Stolzenberg <https://github.com/sebastianstolzenberg>
 * Copyright 2018      BenDroid    <ben@graef.in>
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

#include "crypto/CryptoNight.h"

#include "crypto/CryptoNight_arm.h"

#include "crypto/CryptoNight_test.h"

template <size_t NUM_HASH_BLOCKS>
static void cryptonight_aesni(AsmOptimization asmOptimization, PowVariant powVersion, const uint8_t* input, size_t size, uint8_t* output, ScratchPad** scratchPad) {
    CryptoNightMultiHash<0x40000, POW_DEFAULT_INDEX_SHIFT, MEMORY, 0x1FFFF0, false, NUM_HASH_BLOCKS>::hashPowV3(input, size, output, scratchPad);
}

template <size_t NUM_HASH_BLOCKS>
static void cryptonight_softaes(const uint8_t* input, size_t size, uint8_t* output, ScratchPad** scratchPad) {
    CryptoNightMultiHash<0x40000, POW_DEFAULT_INDEX_SHIFT, MEMORY, 0x1FFFF0, false, NUM_HASH_BLOCKS>::hashPowV3(input, size, output, scratchPad);
}

void (*cryptonight_hash_ctx[MAX_NUM_HASH_BLOCKS])(const uint8_t* input, size_t size, uint8_t* output, ScratchPad** scratchPad);

template <size_t HASH_FACTOR>
void setCryptoNightHashMethods(bool aesni)
{
     if (aesni) {
        cryptonight_hash_ctx[HASH_FACTOR - 1] = cryptonight_aesni<HASH_FACTOR>;
    } else {
        cryptonight_hash_ctx[HASH_FACTOR - 1] = cryptonight_softaes<HASH_FACTOR>;
    }
    // next iteration
    setCryptoNightHashMethods<HASH_FACTOR-1>(aesni);
}

template <>
void setCryptoNightHashMethods<0>(bool aesni)
{
    // template recursion abort
};

bool CryptoNight::init(bool aesni)
{
    for (int i = 0; i < 256; ++i)
    {
        const uint64_t index = (((i >> POW_DEFAULT_INDEX_SHIFT) & 6) | (i & 1)) << 1;
        const uint64_t index_xtl = (((i >> POW_XLT_V4_INDEX_SHIFT) & 6) | (i & 1)) << 1;

        variant1_table[i] = i ^ ((0x75310 >> index) & 0x30);
        variant_xtl_table[i] = i ^ ((0x75310 >> index_xtl) & 0x30);
    }

    setCryptoNightHashMethods<MAX_NUM_HASH_BLOCKS>(aesni);
    return selfTest(algo);
}

void CryptoNight::hash(const uint8_t* input, size_t size, uint8_t* output, ScratchPad** scratchPad)
{
    cryptonight_hash_ctx[factor-1](input, size, output, scratchPad);
}

bool CryptoNight::selfTest()
{
    if (cryptonight_hash_ctx[0] == nullptr
    #if MAX_NUM_HASH_BLOCKS > 1
        || cryptonight_hash_ctx[1] == nullptr
    #endif
    #if MAX_NUM_HASH_BLOCKS > 2
        || cryptonight_hash_ctx[2] == nullptr
    #endif
    #if MAX_NUM_HASH_BLOCKS > 3
        || cryptonight_hash_ctx[3] == nullptr
    #endif
    #if MAX_NUM_HASH_BLOCKS > 4
        || cryptonight_hash_ctx[4] == nullptr
    #endif
    )
    {
        return false;
    }

    uint8_t output[160];

    ScratchPad* scratchPads [MAX_NUM_HASH_BLOCKS];

    for (size_t i = 0; i < MAX_NUM_HASH_BLOCKS; ++i) {
        ScratchPad* scratchPad = static_cast<ScratchPad *>(_mm_malloc(sizeof(ScratchPad), 4096));
        scratchPad->memory     = (uint8_t *) _mm_malloc(MEMORY * 6, 16);

        scratchPads[i] = scratchPad;
    }

    bool result = true;

    // cnv8 + xtl aka cn-fast2

    cryptonight_hash_ctx[0](test_input, 76, output, scratchPads);
    result = result && memcmp(output, test_output_xtl_v9, 32) == 0;

    #if MAX_NUM_HASH_BLOCKS > 1
    cryptonight_hash_ctx[1](test_input, 76, output, scratchPads);
    result = result && memcmp(output, test_output_xtl_v9, 64) == 0;
    #endif

    for (size_t i = 0; i < MAX_NUM_HASH_BLOCKS; ++i) {
        _mm_free(scratchPads[i]->memory);
        _mm_free(scratchPads[i]);
    }

    return result;
}