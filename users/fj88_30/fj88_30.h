#pragma once

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum layers {
    BAS_L = 0,
    PAD_L,
    MUS_L,
    OPT_L,
};

enum custom_keycodes {
    CK_MUHN_CTL = SAFE_RANGE, // hold: LCTRL, tap: INT5+LNG2 (無変換)
    CK_HENK_PAD,              // hold: MO(PAD_L), tap: INT4+LNG1 (変換)
    CK_MESC,                  // tap: 無変換+ESC
    CK_EXIT,                  // tap: "exit"
    CK_BSLH,                  // shift→INT1, else Alt(INT3)
    CK_QUOT_GUI,              // hold: LGUI, tap: JP_QUOT (S(KC_7))
};

// ZMK HYPER = Ctrl+Shift+GUI (QMKの HYPR とは異なる)
#define ZMK_HYPR (MOD_LCTL | MOD_LSFT | MOD_LGUI)
