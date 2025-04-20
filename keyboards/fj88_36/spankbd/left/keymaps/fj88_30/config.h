#pragma once

// clang-format off
#define LAYOUT_fj88_30( \
               L01   ,L02   ,L03   ,L04          ,R04   ,R03   ,R02   ,R01   ,        \
        L10   ,L11   ,L12   ,L13   ,L14          ,R14   ,R13   ,R12   ,R11   ,R10   , \
        L20   ,L21   ,L22   ,L23                        ,R23   ,R22   ,R21   ,R20   , \
                             L30   ,L31          ,R31   ,R30                          \
    ) \
    LAYOUT_split_3x5_3( \
        KC_NO ,L01   ,L02   ,L03   ,L04          ,R04   ,R03   ,R02   ,R01   ,KC_NO , \
        L10   ,L11   ,L12   ,L13   ,L14          ,R14   ,R13   ,R12   ,R11   ,R10   , \
        L20   ,L21   ,L22   ,L23   ,KC_NO        ,KC_NO ,R23   ,R22   ,R21   ,R20   , \
                      L30   ,L31   ,KC_NO        ,KC_NO ,R31   ,R30                   \
    )
// clang-format on
