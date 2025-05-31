#include QMK_KEYBOARD_H
#include "sendstring_japanese.h"
#include "fj88_30_o24.h"

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
        case L_PAD(BSPC):
        case L_SYM(TAB):
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case C_S_T(KC_E):
        case C_S_T(KC_H):
        case SFT_T(KC_I):
        case SFT_T(KC_S):
        case CTL_T(KC_A):
        case CTL_T(KC_N):
        case ALT_T(KC_O):
        case ALT_T(KC_T):
        case GUI_T(JP_MINS):
        case GUI_T(KC_K):
        case L_FNC(C):
        case L_FNC(M):
            return true;
        default:
            return false;
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BAS_L] = LAYOUT_fj88_30(
                      KC_L        , KC_U        , KC_F        , KC_COMMA         , KC_G      , KC_W        , KC_R        , KC_Y        ,
        C_S_T(KC_E) , SFT_T(KC_I) , CTL_T(KC_A) , ALT_T(KC_O) , GUI_T(JP_MINS)   ,GUI_T(KC_K), ALT_T(KC_T) , CTL_T(KC_N) , SFT_T(KC_S) , C_S_T(KC_H)  ,
        L_MUS(Z)    , KC_X        , L_FNC(C)    , KC_V        ,                                KC_D        , L_FNC(M)    , KC_J        , L_MUS(B)     ,
                                                  L_PAD(BSPC) , SFT_T(KC_SPC)    , HENK_ENT  , L_SYM(TAB)
    ),

    [JPN_L] = LAYOUT_fj88_30(
                      KC_L        , KC_U       , KC_F         , KC_COMMA         , KC_G      , KC_W        , KC_R        , KC_Y        ,
        KC_E        , KC_I        , KC_A       , KC_O         , JP_MINS          , KC_K      , KC_T        , KC_N        , KC_S        , KC_H         ,
        L_MUS(Z)    , KC_X        , KC_C       , KC_V         ,                                KC_D        , KC_M        , KC_J        , L_MUS(B)     ,
                                                 _______      , _______          , XXXXXXX   , _______
    ),

    [PAD_L] = LAYOUT_fj88_30(
                      KC_1        , KC_2        , KC_3        , JP_SCLN          , JP_COLN   , JP_TILD     , JP_UNDS     , JP_SLSH     ,
        KC_0        , SFT_T(KC_4) , CTL_T(KC_5) , ALT_T(KC_6) , KC_DOT           , KC_LEFT   , KC_DOWN     , KC_UP       , KC_RIGHT    ,C_S_T(JP_EXLM),
        JP_PERC     , KC_7        , L_FNC(8)    , KC_9        ,                                KC_HOME     , JP_HASH     , KC_END      , JP_QUES      ,
                                                  XXXXXXX     , S(KC_SPC)        , KC_ENTER  , KC_DEL
    ),

    [SYM_L] = LAYOUT_fj88_30(
                      JP_LBRC     , JP_DQUO     , JP_RBRC     , JP_AMPR          , JP_CIRC   , JP_LABK     , JP_EQL      , JP_RABK     ,
        JP_AT       , JP_LPRN     , JP_QUOT     , JP_RPRN     , JP_PIPE          , JP_DLR    , JP_PLUS     , JP_ASTR     , JP_MINS     , XXXXXXX      ,
        JP_BSLS     , JP_LCBR     , JP_GRV      , JP_RCBR     ,                                JP_PIPE     , JP_AMPR     , XXXXXXX     , XXXXXXX      ,
                                                  KC_BSPC     , SFT_T(KC_SPC)    , KC_ENTER  , KC_DEL
    ),

    [FNC_L] = LAYOUT_fj88_30(
                      KC_F2       , KC_F3       , KC_F4       , KC_F5            , KC_VOLU   , KC_PGUP     , XXXXXXX     , XXXXXXX     ,
        KC_F6       , SFT_T(KC_F7),CTL_T(KC_F8) , ALT_T(KC_F9), KC_F10           , KC_VOLD   , KC_RALT     , KC_RCTL     , KC_RSFT     , KC_BRIU      ,
        KC_F11      , KC_F12      , KC_INT5     , KC_APP                                     , KC_PGDN     , KC_INT4     , XXXXXXX     , KC_BRID      ,
                                                  _______     , _______          , _______   , _______
    ),

    [MUS_L] = LAYOUT_fj88_30(
                      KC_WH_L     , KC_WH_R    , XXXXXXX      , XXXXXXX          , KC_WH_U   ,LALT(KC_LEFT), KC_MS_U     ,LALT(KC_RGHT),
        XXXXXXX     , KC_LSFT     , KC_LCTL    , KC_LALT      , XXXXXXX          , KC_WH_D   , KC_MS_L     , KC_MS_D     , KC_MS_R     , XXXXXXX      ,
        L_OPT(ESC)  , KC_F22      , KC_F24     , KC_F23       ,                                KC_F22      , KC_F24      , KC_F23      , L_OPT(ESC)   ,
                                                 KC_MS_BTN3   , KC_LSFT          , KC_MS_BTN1,KC_MS_BTN2
    ),

    [OPT_L] = LAYOUT_fj88_30(
                      XXXXXXX     , XXXXXXX    , XXXXXXX      , QK_BOOT          , QK_BOOT   , XXXXXXX     , XXXXXXX     , XXXXXXX     ,
        XXXXXXX     , XXXXXXX     , XXXXXXX    , XXXXXXX      , XXXXXXX          , XXXXXXX   , XXXXXXX     , XXXXXXX     , XXXXXXX     , XXXXXXX      ,
        XXXXXXX     , XXXXXXX     , XXXXXXX    , XXXXXXX      ,                                XXXXXXX     , XXXXXXX     , XXXXXXX     , XXXXXXX      ,
                                                 XXXXXXX      , XXXXXXX          , XXXXXXX   , XXXXXXX
    ),
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
