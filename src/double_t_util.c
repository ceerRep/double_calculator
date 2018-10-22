#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "double_t_util.h"
#include "uint128_util.h"

//FIXME: BUGGY CONST
#define DOUBLE_T_UINT128_MASK 0xF000000000000000ULL
#define DOUBLE_T_UINT128_RESERVE_BIT_WIDTH 4
#define DOUBLE_T_UINT128_HIGEST 0x0800000000000000ULL

DOUBLET float10ToDOUBLET(const char* int_part, const char* frac_part, signed expo)
{
    DOUBLET ans;
    memset(&ans, 0, sizeof ans);

    signed    expo_2  = 0;
    uint128_T u128tmp = UINT128_ZERO;

    for (char const* p = int_part; p && isdigit(*p); p++) {
        u128tmp = UINT128Add(UINT128Add(UINT128Shl(u128tmp, 3), UINT128Shl(u128tmp, 1)), UINT128Make(0, *p - '0'));
        while (u128tmp.high & DOUBLE_T_UINT128_MASK) {
            u128tmp = UINT128Shr(u128tmp, 1);
            expo_2 += 1;
        }
    }

    for (char const* p = frac_part; p && isdigit(*p); p++) {
        expo--;
        u128tmp = UINT128Add(UINT128Add(UINT128Shl(u128tmp, 3), UINT128Shl(u128tmp, 1)), UINT128Make(0, *p - '0'));
        while (u128tmp.high & DOUBLE_T_UINT128_MASK) {
            u128tmp = UINT128Shr(u128tmp, 1);
            expo_2 += 1;
        }
    }

    if (uint128IsZero(u128tmp))
        expo = 0;
    else
        while (!(u128tmp.high & DOUBLE_T_UINT128_HIGEST)) {
            u128tmp = UINT128Shl(u128tmp, 1);
            expo_2 -= 1;
        }

    while (expo < 0) {
        u128tmp = UINT128Shl(u128tmp, DOUBLE_T_UINT128_RESERVE_BIT_WIDTH);
        u128tmp = UINT64Div(u128tmp, 10, NULL);
        expo_2 -= DOUBLE_T_UINT128_RESERVE_BIT_WIDTH;
        expo++;
        while (u128tmp.high & DOUBLE_T_UINT128_MASK) {
            u128tmp = UINT128Shr(u128tmp, 1);
            expo_2 += 1;
        }
    }
    while (expo > 0) {
        u128tmp = UINT128Add(UINT128Shl(u128tmp, 3), UINT128Shl(u128tmp, 1));
        u128tmp = UINT128Shr(u128tmp, DOUBLE_T_UINT128_RESERVE_BIT_WIDTH - 1);
        expo_2 += DOUBLE_T_UINT128_RESERVE_BIT_WIDTH - 1;
        expo--;
        while (u128tmp.high & DOUBLE_T_UINT128_MASK) {
            u128tmp = UINT128Shr(u128tmp, 1);
            expo_2 += 1;
        }
    }

    doubleTSetVal(&ans, u128tmp, expo_2 + VAL_WIDTH, NULL);

    return ans;
}