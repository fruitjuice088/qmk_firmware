#pragma once

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    BAS_L = 0,
    JPN_L,
    PAD_L,
    SYM_L,
    FNC_L,
    MUS_L,
    OPT_L,
};

enum my_keycode {
    HENK_ENT = SAFE_RANGE,
    ESC_INT5,
    EXIT_MACRO,
};

#define L_JPN(k) LT(JPN_L, KC_ ## k)
#define L_PAD(k) LT(PAD_L, KC_ ## k)
#define L_SYM(k) LT(SYM_L, KC_ ## k)
#define L_FNC(k) LT(FNC_L, KC_ ## k)
#define L_MUS(k) LT(MUS_L, KC_ ## k)
#define L_OPT(k) LT(OPT_L, KC_ ## k)
