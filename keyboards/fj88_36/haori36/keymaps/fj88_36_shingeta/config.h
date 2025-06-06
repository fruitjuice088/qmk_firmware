#pragma once

// clang-format off
#define LAYOUT_fj88_36( \
        L00   ,L01   ,L02   ,L03   ,L04          ,R04   ,R03   ,R02   ,R01   ,R00   , \
        L10   ,L11   ,L12   ,L13   ,L14          ,R14   ,R13   ,R12   ,R11   ,R10   , \
        L20   ,L21   ,L22   ,L23   ,L24          ,R24   ,R23   ,R22   ,R21   ,R20   , \
                             L30   ,L31          ,R31   ,R30                   \
    ) \
    LAYOUT( \
        L00   ,L01   ,L02   ,L03   ,L04          ,R04   ,R03   ,R02   ,R01   ,R00   , \
        L10   ,L11   ,L12   ,L13   ,L14          ,R14   ,R13   ,R12   ,R11   ,R10   , \
        L20   ,L21   ,L22   ,L23   ,L24          ,R24   ,R23   ,R22   ,R21   ,R20   , \
                      KC_NO ,L30   ,L31   ,KC_NO ,R31   ,R30   ,KC_NO                 \
    )
// clang-format on
