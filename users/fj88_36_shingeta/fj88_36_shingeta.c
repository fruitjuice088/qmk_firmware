#include QMK_KEYBOARD_H
#include "sendstring_japanese.h"
#include "fj88_36_shingeta.h"

#if defined(COMBO_ENABLE)
#    include "combos.h"
#endif

// refer to
// https://github.com/funatsufumiya/qmk_firmware_k3pro/blob/main/keyboards/keychron/k3_pro/jis/white/keymaps/naginata_v15_and_shingeta/keymap.c
#define B_Q ((uint64_t)1 << 0)
#define B_W ((uint64_t)1 << 1)
#define B_E ((uint64_t)1 << 2)
#define B_R ((uint64_t)1 << 3)
#define B_T ((uint64_t)1 << 4)

#define B_Y ((uint64_t)1 << 5)
#define B_U ((uint64_t)1 << 6)
#define B_I ((uint64_t)1 << 7)
#define B_O ((uint64_t)1 << 8)
#define B_P ((uint64_t)1 << 9)

#define B_A ((uint64_t)1 << 10)
#define B_S ((uint64_t)1 << 11)
#define B_D ((uint64_t)1 << 12)
#define B_F ((uint64_t)1 << 13)
#define B_G ((uint64_t)1 << 14)

#define B_H ((uint64_t)1 << 15)
#define B_J ((uint64_t)1 << 16)
#define B_K ((uint64_t)1 << 17)
#define B_L ((uint64_t)1 << 18)
#define B_SEMI ((uint64_t)1 << 19)

#define B_Z ((uint64_t)1 << 20)
#define B_X ((uint64_t)1 << 21)
#define B_C ((uint64_t)1 << 22)
#define B_V ((uint64_t)1 << 23)
#define B_B ((uint64_t)1 << 24)

#define B_N ((uint64_t)1 << 25)
#define B_M ((uint64_t)1 << 26)
#define B_COMMA ((uint64_t)1 << 27)
#define B_DOT ((uint64_t)1 << 28)
#define B_SLASH ((uint64_t)1 << 29)

#define B_1 ((uint64_t)1 << 30)
#define B_2 ((uint64_t)1 << 31)
#define B_3 ((uint64_t)1 << 32)
#define B_4 ((uint64_t)1 << 33)
#define B_5 ((uint64_t)1 << 34)
#define B_6 ((uint64_t)1 << 35)
#define B_7 ((uint64_t)1 << 36)
#define B_8 ((uint64_t)1 << 37)
#define B_9 ((uint64_t)1 << 38)
#define B_0 ((uint64_t)1 << 39)
#define B_AT ((uint64_t)1 << 40)

#define SGBUFFER 5 // バッファのサイズ

// HENK_ENT: Enterキーを押している間、かなとINT4が有効になる
static uint16_t lang1_ent_timer;
static bool     kana_key_pressed = false;
static bool     enter_key_held   = false;

static uint8_t  sg_chrcount = 0;
static uint64_t keycomb     = (uint64_t)0;
static uint16_t ninputs[SGBUFFER];

#define SG0 (SG_Q)
// clang-format off
const uint64_t sg_key[] = {
    [SG_A - SG0] = B_A, [SG_B - SG0] = B_B, [SG_C - SG0] = B_C, [SG_D - SG0] = B_D, [SG_E - SG0] = B_E,
    [SG_F - SG0] = B_F, [SG_G - SG0] = B_G, [SG_H - SG0] = B_H, [SG_I - SG0] = B_I, [SG_J - SG0] = B_J,
    [SG_K - SG0] = B_K, [SG_L - SG0] = B_L, [SG_M - SG0] = B_M, [SG_N - SG0] = B_N, [SG_O - SG0] = B_O,
    [SG_P - SG0] = B_P, [SG_Q - SG0] = B_Q, [SG_R - SG0] = B_R, [SG_S - SG0] = B_S, [SG_T - SG0] = B_T,
    [SG_U - SG0] = B_U, [SG_V - SG0] = B_V, [SG_W - SG0] = B_W, [SG_X - SG0] = B_X, [SG_Y - SG0] = B_Y,
    [SG_Z - SG0] = B_Z, [SG_SEMI - SG0] = B_SEMI, [SG_COMMA - SG0] = B_COMMA, [SG_DOT - SG0] = B_DOT,
    [SG_SLASH - SG0] = B_SLASH, [SG_AT - SG0] = B_AT,
    [SG_1 - SG0] = B_1, [SG_2 - SG0] = B_2, [SG_3 - SG0] = B_3, [SG_4 - SG0] = B_4, [SG_5 - SG0] = B_5,
    [SG_6 - SG0] = B_6, [SG_7 - SG0] = B_7, [SG_8 - SG0] = B_8, [SG_9 - SG0] = B_9, [SG_0 - SG0] = B_0
};
// clang-format on

// 順序なし
typedef struct {
    uint64_t key; // 新下駄
    char     kana[6];
} shingeta_keymap;

// clang-format off
const PROGMEM shingeta_keymap sgmap[] = {
    {.key = B_1, .kana = "1"},
    {.key = B_2, .kana = "2"},
    {.key = B_3, .kana = "3"},
    {.key = B_4, .kana = "4"},
    {.key = B_5, .kana = "5"},
    {.key = B_6, .kana = "6"},
    {.key = B_7, .kana = "7"},
    {.key = B_8, .kana = "8"},
    {.key = B_9, .kana = "9"},
    {.key = B_0, .kana = "0"},

    {.key = B_Q, .kana = "-"},
    {.key = B_W, .kana = "ni"},
    {.key = B_E, .kana = "ha"},
    {.key = B_R, .kana = ","},
    {.key = B_T, .kana = "ti"},
    {.key = B_Y, .kana = "gu"},
    {.key = B_U, .kana = "ba"},
    {.key = B_I, .kana = "ko"},
    {.key = B_O, .kana = "ga"},
    {.key = B_P, .kana = "hi"},
    {.key = B_AT, .kana = "ge"},

    {.key = B_A, .kana = "no"},
    {.key = B_S, .kana = "to"},
    {.key = B_D, .kana = "ka"},
    {.key = B_F, .kana = "nn"},
    {.key = B_G, .kana = "xtu"},
    {.key = B_H, .kana = "ku"},
    {.key = B_J, .kana = "u"},
    {.key = B_K, .kana = "i"},
    {.key = B_L, .kana = "si"},
    {.key = B_SEMI, .kana = "na"},

    {.key = B_Z, .kana = "su"},
    {.key = B_X, .kana = "ma"},
    {.key = B_C, .kana = "ki"},
    {.key = B_V, .kana = "ru"},
    {.key = B_B, .kana = "tu"},
    {.key = B_N, .kana = "te"},
    {.key = B_M, .kana = "ta"},
    {.key = B_COMMA, .kana = "de"},
    {.key = B_DOT, .kana = "."},
    {.key = B_SLASH, .kana = "bu"},

    // 中指シフト
    {.key = B_K | B_Q, .kana = "fa"},
    {.key = B_K | B_W, .kana = "go"},
    {.key = B_K | B_E, .kana = "hu"},
    {.key = B_K | B_R, .kana = "fi"},
    {.key = B_K | B_T, .kana = "fe"},
    {.key = B_D | B_Y, .kana = "wi"},
    {.key = B_D | B_U, .kana = "pa"},
    {.key = B_D | B_I, .kana = "yo"},
    {.key = B_D | B_O, .kana = "mi"},
    {.key = B_D | B_P, .kana = "we"},
    {.key = B_5 | B_AT, .kana = "uxo"},

    {.key = B_K | B_A, .kana = "ho"},
    {.key = B_K | B_S, .kana = "ji"},
    {.key = B_K | B_D, .kana = "re"},
    {.key = B_K | B_F, .kana = "mo"},
    {.key = B_K | B_G, .kana = "yu"},
    {.key = B_D | B_H, .kana = "he"},
    {.key = B_D | B_J, .kana = "a"},
    {.key = B_D | B_K, .kana = ""},
    {.key = B_D | B_L, .kana = "o"},
    {.key = B_D | B_SEMI, .kana = "e"},

    {.key = B_K | B_Z, .kana = "du"},
    {.key = B_K | B_X, .kana = "zo"},
    {.key = B_K | B_C, .kana = "bo"},
    {.key = B_K | B_V, .kana = "mu"},
    {.key = B_K | B_B, .kana = "fo"},
    {.key = B_D | B_N, .kana = "se"},
    {.key = B_D | B_M, .kana = "ne"},
    {.key = B_D | B_COMMA, .kana = "be"},
    {.key = B_D | B_DOT, .kana = "pu"},
    {.key = B_D | B_SLASH, .kana = "vu"},

    {.key = B_K | B_1, .kana = "xa"},
    {.key = B_K | B_2, .kana = "xi"},
    {.key = B_K | B_3, .kana = "xu"},
    {.key = B_K | B_4, .kana = "xe"},
    {.key = B_K | B_5, .kana = "xo"},

    // 薬指シフト
    {.key = B_L | B_Q, .kana = "di"},
    {.key = B_L | B_W, .kana = "me"},
    {.key = B_L | B_E, .kana = "ke"},
    {.key = B_L | B_R, .kana = "texi"},
    {.key = B_L | B_T, .kana = "dexi"},
    {.key = B_S | B_Y, .kana = "sye"},
    {.key = B_S | B_U, .kana = "pe"},
    {.key = B_S | B_I, .kana = "do"},
    {.key = B_S | B_O, .kana = "ya"},
    {.key = B_S | B_P, .kana = "je"},

    {.key = B_L | B_A, .kana = "wo"},
    {.key = B_L | B_S, .kana = "sa"},
    {.key = B_L | B_D, .kana = "o"},
    {.key = B_L | B_F, .kana = "ri"},
    {.key = B_L | B_G, .kana = "zu"},
    {.key = B_S | B_H, .kana = "bi"},
    {.key = B_S | B_J, .kana = "ra"},
    {.key = B_S | B_K, .kana = ""},
    {.key = B_S | B_L, .kana = ""},
    {.key = B_S | B_SEMI, .kana = "so"},

    {.key = B_L | B_Z, .kana = "ze"},
    {.key = B_L | B_X, .kana = "za"},
    {.key = B_L | B_C, .kana = "gi"},
    {.key = B_L | B_V, .kana = "ro"},
    {.key = B_L | B_B, .kana = "nu"},
    {.key = B_S | B_N, .kana = "wa"},
    {.key = B_S | B_M, .kana = "da"},
    {.key = B_S | B_COMMA, .kana = "pi"},
    {.key = B_S | B_DOT, .kana = "po"},
    {.key = B_S | B_SLASH, .kana = "che"},

    {.key = B_L | B_1, .kana = "xya"},
    {.key = B_L | B_2, .kana = "mya"},
    {.key = B_L | B_3, .kana = "myu"},
    {.key = B_L | B_4, .kana = "myo"},
    {.key = B_L | B_5, .kana = "xwa"},

    {.key = B_I | B_E, .kana = "sho"},
    {.key = B_I | B_W, .kana = "shu"},
    {.key = B_I | B_R, .kana = "kyu"},
    {.key = B_I | B_F, .kana = "kyo"},
    {.key = B_I | B_V, .kana = "kya"},
    {.key = B_I | B_C, .kana = "sha"},
    {.key = B_I | B_Q, .kana = "hyu"},
    {.key = B_I | B_A, .kana = "hyo"},
    {.key = B_I | B_Z, .kana = "hya"},
    {.key = B_I | B_T, .kana = "chu"},
    {.key = B_I | B_G, .kana = "cho"},
    {.key = B_I | B_B, .kana = "cha"},

    {.key = B_I | B_1, .kana = "xyu"},
    {.key = B_I | B_2, .kana = "bya"},
    {.key = B_I | B_3, .kana = "byu"},
    {.key = B_I | B_4, .kana = "byo"},

    {.key = B_O | B_E, .kana = "jo"},
    {.key = B_O | B_W, .kana = "ju"},
    {.key = B_O | B_R, .kana = "gyu"},
    {.key = B_O | B_F, .kana = "gyo"},
    {.key = B_O | B_V, .kana = "gya"},
    {.key = B_O | B_C, .kana = "ja"},
    {.key = B_O | B_Q, .kana = "ryu"},
    {.key = B_O | B_A, .kana = "ryo"},
    {.key = B_O | B_Z, .kana = "rya"},
    {.key = B_O | B_T, .kana = "nyu"},
    {.key = B_O | B_G, .kana = "nyo"},
    {.key = B_O | B_B, .kana = "nya"},

    {.key = B_O | B_1, .kana = "xyo"},
    {.key = B_O | B_2, .kana = "pya"},
    {.key = B_O | B_3, .kana = "pyu"},
    {.key = B_O | B_4, .kana = "pyo"},

    // others
    {.key = B_E | B_F, .kana = "/"},
    {.key = B_X | B_F, .kana = "\\"},
    {.key = B_F | B_B, .kana = "!"},
    {.key = B_N | B_J, .kana = "?"},

    {.key = B_T | B_Y, .kana = "[]"SS_TAP(X_LEFT)}, // 「」←
    {.key = B_G | B_H, .kana = "()"SS_TAP(X_LEFT)}, // （）←
};
// clang-format off


void shingeta_clear(void) {
    for (int i = 0; i < SGBUFFER; i++) {
        ninputs[i] = 0;
    }
    sg_chrcount = 0;
}


void shingeta_type(void) {
    shingeta_keymap bsgmap;

    for (int i = 0; i < sizeof sgmap / sizeof bsgmap; i++) {
        // 一時バッファに定義配列を入れる
        memcpy_P(&bsgmap, &sgmap[i], sizeof(bsgmap));
        // 現在の入力が、今入れた定義と一致、つまり定義が見つかった
        if (keycomb == bsgmap.key) {
            send_string(bsgmap.kana);
            shingeta_clear();
            return;
        }
    }

    // その他の入力
    uint32_t skey = 0;
    for (int j = 0; j < sg_chrcount; j++) {
        skey = sg_key[ninputs[j] - SG0];
        for (int i = 0; i < sizeof sgmap / sizeof bsgmap; i++) {
            memcpy_P(&bsgmap, &sgmap[i], sizeof(bsgmap));
            if (skey == bsgmap.key) {
                send_string(bsgmap.kana);
                break;
            }
        }
    }

    shingeta_clear();
}


#define SFTD_I LT(SFT_L, KC_I)
#define SFTD_N LT(SFT_L, KC_N)
#define FUNC_C LT(FNC_L, KC_C)
#define FUNC_G LT(FNC_L, KC_G)
#define SYM_BS LT(SYM_L, KC_BSPC)
#define SYM_TB LT(SYM_L, KC_TAB)
#define MOUS_Z LT(MUS_L, KC_Z)
#define MOUS_B LT(MUS_L, KC_B)

#define SFTD_4 LT(SFT_L, KC_4)
#define FUNC_8 LT(FNC_L, KC_8)
#define SYM_DL LT(SYM_L, KC_DEL)

#define GTEX_BS LT(SGX_L, KC_BSPC)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYM_BS:
        case SYM_TB:
        case SFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_E):
        case SFTD_I:
        case FUNC_C:
        case SFTD_N:
        case FUNC_G:
            return true;
        default:
            return false;
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BAS_L] = LAYOUT_fj88_36(
        KC_Q       , KC_Y     , KC_U        , KC_COMM     , KC_DOT           , KC_K      , KC_W        , KC_H        , KC_L        , KC_P         ,
        C_S_T(KC_O), SFTD_I   , CTL_T(KC_E) , ALT_T(KC_A) , KC_MINS          , KC_F      , ALT_T(KC_T) , CTL_T(KC_R) , SFTD_N      , C_S_T(KC_S)  ,
        MOUS_Z     , KC_X     , FUNC_C      , KC_V        , KC_SCLN          , KC_J      , KC_D        , FUNC_G      , KC_M        , MOUS_B       ,
                                              SYM_BS      , SFT_T(KC_SPC)    , HENK_ENT  , GUI_T(KC_TAB)
    ),

    [SYM_L] = LAYOUT_fj88_36(
        KC_ESC     , KC_1     , KC_2        , KC_3        , JP_CIRC          , KC_UP     , KC_PGUP     , KC_LEFT     , KC_RGHT     , JP_YEN       ,
        _______    , SFTD_4   , CTL_T(KC_5) , ALT_T(KC_6) , JP_BSLS          , JP_SCLN   , JP_COLN     , JP_SLSH     , JP_AT       ,C_S_T(JP_LBRC),
        KC_DEL     , KC_7     , FUNC_8      , KC_9        , KC_0             , KC_DOWN   , KC_PGDN     , KC_HOME     , KC_END      , JP_RBRC      ,
                                              XXXXXXX     , _______          , SFT_T(KC_SPC), KC_ESC
    ),

    [SFT_L] = LAYOUT_fj88_36(
        _______    , JP_EXLM  , JP_DQUO    , JP_HASH      , S(JP_CIRC)       , S(KC_UP)  , S(KC_PGUP)  , S(KC_LEFT)  , S(KC_RGHT)  , S(JP_YEN)    ,
        _______    , JP_DLR   , JP_PERC    , JP_AMPR      , S(JP_BSLS)       , S(JP_SCLN), S(JP_COLN)  , S(JP_SLSH)  , S(JP_AT)    , S(JP_LBRC)   ,
        _______    , JP_QUOT  , JP_LPRN    , JP_RPRN      , _______          , S(KC_DOWN), S(KC_PGDN)  , S(KC_HOME)  , S(KC_END)   , S(JP_RBRC)   ,
                                             _______      , _______          , _______   , _______
    ),

    [FNC_L] = LAYOUT_fj88_36(
        KC_F1      , KC_F2    , KC_F3      , KC_F4        , KC_F5            , KC_VOLU   , XXXXXXX     , XXXXXXX     , XXXXXXX     , KC_BRIU      ,
        KC_F6    ,SFT_T(KC_F7),CTL_T(KC_F8), ALT_T(KC_F9) , KC_F10           , KC_VOLD   , KC_RALT     , KC_RCTL     , KC_RSFT     , KC_BRID      ,
        KC_F11     , KC_F12   , KC_INT5    , KC_APP       , C(KC_INS)        , S(KC_INS) , XXXXXXX     , KC_INT4     , XXXXXXX     , XXXXXXX      ,
                                             _______      , _______          , _______   , _______
    ),

    [MUS_L] = LAYOUT_fj88_36(
        QK_BOOT    , XXXXXXX  , XXXXXXX    , XXXXXXX      , XXXXXXX          , KC_WH_U   ,LALT(KC_LEFT), KC_MS_U     ,LALT(KC_RGHT), QK_BOOT      ,
        XXXXXXX    , KC_LSFT  , KC_LCTL    , KC_LALT      , XXXXXXX          , KC_WH_D   , KC_MS_L     , KC_MS_D     , KC_MS_R     , XXXXXXX      ,
        KC_ESC     , XXXXXXX  , KC_F22     , KC_F24       , KC_F23           , KC_WH_L   , KC_F24      , XXXXXXX     , KC_WH_R     , XXXXXXX      ,
                                             KC_MS_BTN3 , KC_LSFT            , KC_MS_BTN1  , KC_MS_BTN2
    ),

    [SGT_L] = LAYOUT_fj88_36(
        SG_Q      , SG_W     , SG_E       , SG_R          , SG_T             , SG_Y      , SG_U        , SG_I        , SG_O        , SG_P         ,
        SG_A      , SG_S     , SG_D       , SG_F          , SG_G             , SG_H      , SG_J        , SG_K        , SG_L        , SG_SEMI      ,
        SG_Z      , SG_X     , SG_C       , SG_V          , SG_B             , SG_N      , SG_M        , SG_COMMA    , SG_DOT      , SG_SLASH     ,
                                            GTEX_BS    , SFT_T(KC_SPC)       , XXXXXXX   , KC_ESC
    ),

    [SGX_L] = LAYOUT_fj88_36(
        KC_ESC    , SG_1     , SG_2       , SG_3         , KC_LEFT           , KC_UP     , _______     , _______     , _______     , SG_AT        ,
        KC_TAB    , SG_4     , SG_5       , SG_6         , KC_RIGHT          , JP_SCLN   , _______     , _______     , _______     , JP_LBRC      ,
        S(KC_TAB) , SG_7     , SG_8       , SG_9         , SG_0              , KC_DOWN   , _______     , _______     , _______     , SFT_T(JP_RBRC),
                                            XXXXXXX      , S(KC_SPC)         , XXXXXXX   , KC_ENTER
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
                layer_on(SGT_L);
                keycomb          = (uint64_t)0; // 新下駄
                lang1_ent_timer  = timer_read();
                kana_key_pressed = false;
                enter_key_held   = true;
            } else {
                keycomb = (uint64_t)0;
                shingeta_clear();
                layer_off(SGT_L);
                if (timer_elapsed(lang1_ent_timer) < 200 && !kana_key_pressed) {
                    tap_code(KC_ENT);
                }
                if (kana_key_pressed) {
                    tap_code(KC_INT5); // Muhenkan
                }
                enter_key_held   = false;
                kana_key_pressed = false;
            }
            return false;

        // 新下駄配列対応
        case SG_Q ... SG_AT:
            if (!enter_key_held) {
                return false; // Unexpected behaviour
            }
            if (record->event.pressed) {
                // HENK_ENT後初めてかなキーを押した
                if (!kana_key_pressed) {
                    tap_code(KC_INT4); // Henkan
                    shingeta_clear();
                    kana_key_pressed = true;
                }
                ninputs[sg_chrcount++] = keycode;
                keycomb |= sg_key[keycode - SG0];
                // 2文字あれば処理
                if (sg_chrcount >= 2) {
                    shingeta_type();
                }

            } else { // key release
                // 何かしら入力が残っていれば処理する
                if (sg_chrcount > 0) {
                    shingeta_type();
                }
                keycomb &= ~sg_key[keycode - SG0]; // キーの重ね合わせ
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
