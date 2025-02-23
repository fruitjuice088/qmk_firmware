# Fix after QMK Breaking Changes 2022 August 27: https://github.com/qmk/qmk_firmware/pull/17559/files
INTROSPECTION_KEYMAP_C = fj88_36_shingeta.c

EXTRAKEY_ENABLE = yes
COMBO_ENABLE = yes
OLED_ENABLE = yes
MOUSEKEY_ENABLE = yes
# Disable other features to squeeze firmware size
NKRO_ENABLE = no
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no
RGBRIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
SLEEP_LED_ENABLE = no
GRAVE_ESC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUDIO_ENABLE = no
VIA_ENABLE = no
MUSIC_ENABLE = no
TAP_DANCE_ENABLE = no

# To reduce size
LTO_ENABLE = yes
