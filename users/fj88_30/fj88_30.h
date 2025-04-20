#pragma once

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    BAS_L = 0,
    SYM_L,
    SFT_L,
    FNC_L,
    MUS_L,
    JPN_L,
};

enum my_keycode {
    HENK_ENT = SAFE_RANGE,
    ESC_INT5,
    EXIT_MACRO,
};
