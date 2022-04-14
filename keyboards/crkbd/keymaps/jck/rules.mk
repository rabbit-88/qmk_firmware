
BOOTMAGIC_ENABLE = yes		# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = yes		# Console for debug
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

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
RGB_MATRIX_SPLIT = yes
RGB_MATRIX_ENABLE = yes

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = mirror
SPLIT_TRANSPORT_MIRROR = yes

# RGB_MATRIX_ENABLE && RGB_MATRIX_SPLIT ... rgb_matrix_drivers
# RGB_MATRIX_KEYREACTIVE_ENABLED = yes

TAPPING_TERM = 250
DEFAULT_FOLDER = crkbd/rev1
EXTRAFLAGS += -flto

EXTRAKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = no

#---
# GET_AUTO_SHIFT_REPEAT = yes
# GET_AUTO_REPEAT_PER_KEY = yes

