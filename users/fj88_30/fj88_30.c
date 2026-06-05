#include QMK_KEYBOARD_H
#include "fj88_30.h"

#if defined(COMBO_ENABLE)
#    include "combos.h"
#endif

// ─────────────────────────────────────────────────────────────────
// Keymaps
// ─────────────────────────────────────────────────────────────────
//
// key-positions:
//       |  0  |  1  |  2  |  3  |    |  4  |  5  |  6  |  7  |
// |  8  |  9  | 10  | 11  | 12  |    | 13  | 14  | 15  | 16  | 17  |
// | 18  | 19  | 20  | 21  |                | 22  | 23  | 24  | 25  |
//                         | 26  | 27  |    | 28  | 29  |

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //      L     U     F     .          G     W     R     Y
    // E    I     A     O     -          K     T     N     S     H
    // Z/M  X/G   C     V/A              D/A   M     J/G   B/M
    //            muh/C spc/S      hen/P Tab/Hy
    [BAS_L] = LAYOUT_fj88_30(
                          KC_L,             KC_U,             KC_F,            KC_DOT,           KC_G,             KC_W,             KC_R,            KC_Y,
        KC_E,             KC_I,             KC_A,             KC_O,            JP_MINS,          KC_K,             KC_T,             KC_N,            KC_S,             KC_H,
        LT(MUS_L, KC_Z),  LGUI_T(KC_X),     KC_C,             LALT_T(KC_V),                                        RALT_T(KC_D),     KC_M,            RGUI_T(KC_J),    LT(MUS_L, KC_B),
                                            CK_MUHN_CTL,      LSFT_T(KC_SPC),                    CK_HENK_PAD,      MT(ZMK_HYPR, KC_TAB)
    ),

    //      1     2     3     "          `     <     =     >
    // 0    4/S   5/C   6/A   '          ←     ↓     ↑     →     :
    // %    7     8     9                      HOME  END   {     }
    //                  BS/C  ___        PRS   DEL
    [PAD_L] = LAYOUT_fj88_30(
                          KC_1,             KC_2,            KC_3,           JP_DQUO,           JP_GRV,           JP_LABK,          JP_EQL,          JP_RABK,
        KC_0,             LSFT_T(KC_4),    LCTL_T(KC_5),     LALT_T(KC_6),   JP_QUOT,       KC_LEFT,          KC_DOWN,          KC_UP,           KC_RGHT,         JP_COLN,
        JP_PERC,          KC_7,            KC_8,             KC_9,                                                KC_HOME,          KC_END,          JP_LCBR,         JP_RCBR,
                                           LCTL_T(KC_BSPC),  _______,                           XXXXXXX,          KC_DEL
    ),

    //      ←S    →S    V-    V+         ↑S    MB4   ↑M    MB5
    // B-   Sft   Ctl   Alt   Gui        ↓S    ←M    ↓M    →M    B+
    // O/E  F18   F20   F19              F18   F20   F19   O/E
    //            MB3   Sft        MB1   MB2
    [MUS_L] = LAYOUT_fj88_30(
                          KC_WH_L,          KC_WH_R,         KC_VOLD,         KC_VOLU,           KC_WH_U,          KC_MS_BTN4,       KC_MS_UP,        KC_MS_BTN5,
        KC_BRID,          KC_LSFT,         KC_LCTL,          KC_LALT,         KC_LGUI,           KC_WH_D,          KC_MS_LEFT,       KC_MS_DOWN,      KC_MS_RIGHT,     KC_BRIU,
        LT(OPT_L, KC_ESC), KC_F18,          KC_F20,           KC_F19,                                               KC_F18,           KC_F20,          KC_F19,          LT(OPT_L, KC_ESC),
                                           KC_MS_BTN3,       KC_LSFT,                            KC_MS_BTN1,       KC_MS_BTN2
    ),

    //      x     x     x     boot       boot  x     x     x
    // x    x     x     BAS   MUS_T      x     x     x     x     x
    // PRS  x     x     x                      x     x     x     PRS
    //                  x     x          x     x
    [OPT_L] = LAYOUT_fj88_30(
                          XXXXXXX,         XXXXXXX,          XXXXXXX,         QK_BOOT,          QK_BOOT,          XXXXXXX,          XXXXXXX,         XXXXXXX,
        XXXXXXX,          XXXXXXX,         XXXXXXX,          TO(BAS_L),       XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,          XXXXXXX,         XXXXXXX,          XXXXXXX,                                             XXXXXXX,          XXXXXXX,         XXXXXXX,         XXXXXXX,
                                           XXXXXXX,          XXXXXXX,                           XXXXXXX,          XXXXXXX
    ),
};
// clang-format on


// ─────────────────────────────────────────────────────────────────
// Tapping term
// ─────────────────────────────────────────────────────────────────
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return TAPPING_TERM;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_BSPC):
        case LSFT_T(KC_SPC):
        case MT(ZMK_HYPR, KC_TAB):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_X):
        case LALT_T(KC_V):
        case RALT_T(KC_D):
        case RGUI_T(KC_J):
        case LSFT_T(KC_4):
        case LCTL_T(KC_5):
        case LALT_T(KC_6):
        case LCTL_T(KC_BSPC):
        case LSFT_T(KC_SPC):
        case MT(ZMK_HYPR, KC_TAB):
            return true;
        default:
            return false;
    }
}


// ─────────────────────────────────────────────────────────────────
// Custom keycode processing
// ─────────────────────────────────────────────────────────────────
static uint16_t muhn_timer = 0;
static uint16_t henk_timer = 0;
static uint8_t  muhn_nested_keys = 0;
static bool     muhn_ctrl_registered = false;
static bool     muhn_hold_used = false;
static bool     muhn_unregister_pending = false;

static void unregister_muhn_ctrl(void) {
    unregister_code(KC_LCTL);
    muhn_ctrl_registered = false;
    muhn_unregister_pending = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != CK_MUHN_CTL && muhn_ctrl_registered) {
        if (record->event.pressed) {
            muhn_hold_used = true;
            if (muhn_nested_keys < 255) {
                muhn_nested_keys++;
            }
        } else if (muhn_nested_keys > 0) {
            muhn_nested_keys--;
        }
    }

    switch (keycode) {

        // hold: LCTRL  /  tap: 無変換 (INT5+LNG2)
        case CK_MUHN_CTL:
            if (record->event.pressed) {
                muhn_timer = timer_read();
                muhn_nested_keys = 0;
                muhn_hold_used = false;
                muhn_unregister_pending = false;
                register_code(KC_LCTL);
                muhn_ctrl_registered = true;
            } else {
                if (!muhn_hold_used && timer_elapsed(muhn_timer) < TAPPING_TERM) {
                    unregister_muhn_ctrl();
                    tap_code(KC_INT5);
                    tap_code(KC_LNG2);
                } else if (muhn_nested_keys > 0) {
                    muhn_unregister_pending = true;
                } else {
                    unregister_muhn_ctrl();
                }
            }
            return false;

        // hold: MO(PAD_L)  /  tap: 変換 (INT4+LNG1)
        case CK_HENK_PAD:
            if (record->event.pressed) {
                henk_timer = timer_read();
                layer_on(PAD_L);
            } else {
                layer_off(PAD_L);
                if (timer_elapsed(henk_timer) < TAPPING_TERM) {
                    tap_code(KC_INT4);
                    tap_code(KC_LNG1);
                }
            }
            return false;

        // 無変換+ESC
        case CK_MESC:
            if (record->event.pressed) {
                tap_code(KC_INT5);
                tap_code(KC_LNG2);
                tap_code(KC_ESC);
            }
            return false;

        // "exit" 文字列送信
        case CK_EXIT:
            if (record->event.pressed) {
                tap_code(KC_INT5);
                tap_code(KC_LNG2);
                SEND_STRING("exit");
            }
            return false;

        // jp_backslash_morph: shift→INT1 (¥=\), else Alt(INT3) (Mac用\)
        case CK_BSLH:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    uint8_t saved = get_mods();
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_INT1);
                    set_mods(saved);
                } else {
                    tap_code16(LALT(KC_INT3));
                }
            }
            return false;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != CK_MUHN_CTL && !record->event.pressed && muhn_unregister_pending && muhn_nested_keys == 0) {
        unregister_muhn_ctrl();
    }
}

// See: https://docs.qmk.fm/#/squeezing_avr?id=magic-functions
#if !defined(MAGIC_KEYCODE_ENABLE) && !defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)

uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}

#endif
