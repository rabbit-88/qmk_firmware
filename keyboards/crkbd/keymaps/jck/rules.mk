
MCU = atmega32u4
BOOTLOADER = caterina

BOOTMAGIC_ENABLE = no		# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = no			# Console for debug
COMMAND_ENABLE = no			# Commands for debug and configuration
NKRO_ENABLE = yes			# Enable N-Key Rollover
BACKLIGHT_ENABLE = no		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no		# Enable keyboard RGB underglow
AUDIO_ENABLE = no			# Audio output
UNICODE_ENABLE = no

TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

LTO_ENABLE = yes

OLED_ENABLE = yes			# can not enable CONSOLE and OLED at the same time
OLED_DRIVER = SSD1306
OLED_DRIVER_ENABLE  = yes

# RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
RGB_MATRIX_SPLIT = yes

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = mirror
SPLIT_TRANSPORT_MIRROR = yes

# RGB_MATRIX_ENABLE && RGB_MATRIX_SPLIT ... rgb_matrix_drivers
# RGB_MATRIX_KEYREACTIVE_ENABLED = yes

TAPPING_TERM = 250

DEFAULT_FOLDER = crkbd/rev1
EXTRAFLAGS += -flto

CONSOLE_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
NKRO_ENABLE = no
DYNAMIC_MACRO_ENABLE = no

# CONSOLE_ENABLE = no
# MOUSEKEY_ENABLE = yes
# TAP_DANCE_ENABLE = yes
