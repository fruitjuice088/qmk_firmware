#pragma once

#include QMK_KEYBOARD_H

void shingeta_type(void);
void shingeta_clear(void);

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    BAS_L = 0,
    SYM_L,
    SFT_L,
    FNC_L,
    MUS_L,
    SGT_L,
    SGX_L,
};

typedef enum shingeta_keycodes {
    SG_Q = SAFE_RANGE,
    SG_W,
    SG_E,
    SG_R,
    SG_T,

    SG_Y,
    SG_U,
    SG_I,
    SG_O,
    SG_P,

    SG_A,
    SG_S,
    SG_D,
    SG_F,
    SG_G,

    SG_H,
    SG_J,
    SG_K,
    SG_L,
    SG_SEMI,

    SG_Z,
    SG_X,
    SG_C,
    SG_V,
    SG_B,

    SG_N,
    SG_M,
    SG_COMMA,
    SG_DOT,
    SG_SLASH,

    SG_1,
    SG_2,
    SG_3,
    SG_4,
    SG_5,
    SG_6,
    SG_7,
    SG_8,
    SG_9,
    SG_0,
    SG_AT,

    HENK_ENT,
    ESC_INT5,
} SGKEYS;
