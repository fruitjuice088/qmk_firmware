#include QMK_KEYBOARD_H
#include "sendstring_japanese.h"
#include "fj88_30.h"

#if defined(COMBO_ENABLE)
#    include "combos.h"
#endif


// HENK_ENT: Enterキーを押している間、かなとINT4が有効になる
static uint16_t lang1_ent_timer;
static bool     other_key_pressed = false;
static bool     enter_key_held = false;


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(SYM_L, KC_BSPC):
        case GUI_T(KC_TAB):
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case C_S_T(KC_E):
        case LT(SFT_L, KC_I):
        case CTL_T(KC_A):
        case ALT_T(KC_O):
        case ALT_T(KC_J):
        case CTL_T(KC_K):
        case LT(SFT_L, KC_L):
        case C_S_T(KC_N):
        case LT(FNC_L, KC_COMM):
        case LT(FNC_L, KC_B):
            return true;
        default:
            return false;
    }
}

#define L_SYM(k) LT(SYM_L, KC_ ## k)
#define L_SFT(k) LT(SFT_L, KC_ ## k)
#define L_FNC(k) LT(FNC_L, KC_ ## k)
#define L_MUS(k) LT(MUS_L, KC_ ## k)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BAS_L] = LAYOUT_fj88_30(
                      KC_R        , KC_U        , KC_Y        , KC_C             , KC_V      , KC_W        , KC_T        , KC_S        ,
        C_S_T(KC_E) , L_SFT(I)    , CTL_T(KC_A) , ALT_T(KC_O) , KC_G             , KC_H      , ALT_T(KC_J) , CTL_T(KC_K) , L_SFT(L)    , C_S_T(KC_N)  ,
        L_MUS(Z)    , KC_X        , L_FNC(COMM) , KC_DOT      ,                                KC_D        , L_FNC(B)    , KC_M        , L_MUS(F)     ,
                                                  L_SYM(BSPC) , SFT_T(KC_SPC)    , HENK_ENT  , GUI_T(KC_TAB)
    ),

    [SYM_L] = LAYOUT_fj88_30(
                      KC_1        , KC_2        , KC_3        , C(KC_INS)        , S(KC_INS) , XXXXXXX     , KC_COMM     , KC_SPC      ,
        KC_0        , L_SFT(4)    , CTL_T(KC_5) , ALT_T(KC_6) , KC_BSPC          , KC_LEFT   , KC_DOWN     , KC_UP       , KC_RIGHT    ,C_S_T(KC_DEL) ,
        KC_DOT      , KC_7        , L_FNC(8)    , KC_9        ,                                KC_HOME     , KC_PGUP     , KC_PGDN     , KC_END       ,
                                                  XXXXXXX     , S(KC_SPC)        , KC_ENTER  , KC_ESC
    ),

    [SFT_L] = LAYOUT_fj88_30(
                      S(KC_1)     , S(KC_2)     , S(KC_3)     , XXXXXXX          , S(KC_INS) , XXXXXXX     , XXXXXXX     , XXXXXXX     ,
        S(KC_4)     , S(KC_4)     , S(KC_5)     , S(KC_6)     , XXXXXXX          , S(KC_LEFT), S(KC_DOWN)  , S(KC_UP)    , S(KC_RIGHT) ,S(KC_RIGHT)   ,
        _______     , S(KC_7)     , S(KC_8)     , S(KC_9)                                    , S(KC_HOME)  , S(KC_PGUP)  , S(KC_PGDN)  , S(KC_END)    ,
                                                  XXXXXXX     , _______          , _______   , _______
    ),

    [FNC_L] = LAYOUT_fj88_30(
                      KC_F2       , KC_F3       , KC_F4       , KC_F5            , KC_VOLU   , XXXXXXX     , XXXXXXX     , XXXXXXX     ,
        KC_F6       , SFT_T(KC_F7),CTL_T(KC_F8) , ALT_T(KC_F9), KC_F10           , KC_VOLD   , KC_RALT     , KC_RCTL     , KC_RSFT     , KC_BRIU      ,
        KC_F11      , KC_F12      , KC_INT5     , KC_APP                                     , XXXXXXX     , KC_INT4     , XXXXXXX     , KC_BRID      ,
                                                  _______     , _______          , _______   , _______
    ),

    [MUS_L] = LAYOUT_fj88_30(
                      KC_WH_L     , KC_WH_R    , XXXXXXX      , XXXXXXX          , KC_WH_U   ,LALT(KC_LEFT), KC_MS_U     ,LALT(KC_RGHT),
        QK_BOOT     , KC_LSFT     , KC_LCTL    , KC_LALT      , XXXXXXX          , KC_WH_D   , KC_MS_L     , KC_MS_D     , KC_MS_R     , QK_BOOT      ,
        KC_ESC      , KC_F22      , KC_F23     , KC_F24       ,                                KC_F24      , KC_F22      , KC_F23      , KC_ESC       ,
                                                 KC_MS_BTN3   , KC_LSFT          , KC_MS_BTN1,KC_MS_BTN2
    ),

    [JPN_L] = LAYOUT_fj88_30(
                      KC_R        , KC_U       , KC_Y         , KC_C             , KC_V      , KC_W        , KC_T        , KC_S        ,
        KC_E        , KC_I        , KC_A       , KC_O         , KC_G             , KC_H      , KC_J        , KC_K        , KC_L        , KC_N         ,
        KC_Z        , KC_X        , KC_COMMA   , KC_DOT       ,                                KC_D        , KC_B        , KC_M        , KC_F         ,
                                                 L_SYM(BSPC)  , SFT_T(KC_SPC)    , XXXXXXX   , KC_ENTER
    )
    };
    // clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifndef MOUSEKEY_ENABLE
        // process KC_MS_BTN1~8 by myself
        // See process_action() in quantum/action.c for details.
        case KC_MS_BTN1 ... KC_MS_BTN3:
        case KC_MS_WH_UP ... KC_MS_WH_DOWN: {
            extern void register_mouse(uint8_t mouse_keycode, bool pressed);
            register_mouse(keycode, record->event.pressed);
            // to apply QK_MODS actions, allow to process others.
            return true;
        }
#endif

        case HENK_ENT:
            if (record->event.pressed) {
                layer_on(JPN_L);
                lang1_ent_timer = timer_read();
                other_key_pressed = false;
                enter_key_held = true;
            } else {
                layer_off(JPN_L);
                if (timer_elapsed(lang1_ent_timer) < 200 && !other_key_pressed) {
                    tap_code(KC_ENT);
                }
                if (other_key_pressed) {
                    tap_code(KC_INT5); // Muhenkan
                }
                enter_key_held = false;
                other_key_pressed = false;
            }
            return false;

        case ESC_INT5:
            if (!record->event.pressed) {
                tap_code(KC_INT5);
                tap_code_delay(KC_ESC, 10);
            }
            break;

        case EXIT_MACRO:
            if (!record->event.pressed) {
                send_string("exit");
            }
            break;

        default:
            if (record->event.pressed && enter_key_held) {
                // HENK_ENT後初めて他キーを押した
                if (!other_key_pressed) {
                    tap_code(KC_INT4); // Henkan
                    other_key_pressed = true;
                }
            }
            break;
    }

    return true;
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
