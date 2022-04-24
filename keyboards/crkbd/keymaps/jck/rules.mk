
BOOTMAGIC_ENABLE = yes		# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = no		# Console for debug
COMMAND_ENABLE = no 		# Commands for debug and configuration
NKRO_ENABLE = no			# Enable N-Key Rollover
BACKLIGHT_ENABLE = no		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no		# Enable keyboard RGB underglow
AUDIO_ENABLE = no			# Audio output
UNICODE_ENABLE = no

TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no

LTO_ENABLE = yes

OLED_DRIVER_ENABLE  = no
OLED_ENABLE = no			# can not enable CONSOLE and OLED at the same time
OLED_DRIVER = SSD1306

# RGBLIGHT is for underglow.
# RGB_MATRIX is for per-key RGB.

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
RGBLIGHT_ENABLE = yes		# enables six RGBs
RGB_MATRIX_ENABLE = yes		# enables twenty-seven RGBs
RGB_MATRIX_SPLIT = yes

# RGB_MATRIX_ENABLE && RGB_MATRIX_SPLIT ... rgb_matrix_drivers
# RGB_MATRIX_KEYREACTIVE_ENABLED = yes

TAPPING_TERM = 250
BLINK_RATE = 500
AUTOREPEAT_RATE = 125
EXTRAFLAGS += -flto

CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = no
AUTO_SHIFT_ENABLE = no
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE =yes		# requires 1800 bytes
#---
GET_AUTO_SHIFT_REPEAT = no
GET_AUTO_REPEAT_PER_KEY = no

DEFAULT_FOLDER = crkbd/rev1
