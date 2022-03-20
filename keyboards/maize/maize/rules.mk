MCU = atmega32u4
BOOTLOADER = caterina

SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = maize
LAYOUTS = split_3x6_3

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = mirror
SPLIT_TRANSPORT_MIRROR = yes

#DEFAULT_FOLDER = crkbd/maize
EXTRAFLAGS += -flto
LTO_ENABLE = yes

BOOTMAGIC_ENABLE = no		# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = no			# Console for debug
COMMAND_ENABLE = no			# Commands for debug and configuration
NKRO_ENABLE = no			# Enable N-Key Rollover
BACKLIGHT_ENABLE = no		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no		# Enable keyboard RGB underglow
AUDIO_ENABLE = no			# Audio output
UNICODE_ENABLE = no

TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes

OLED_ENABLE = no			# can not enable CONSOLE and OLED at the same time
OLED_DRIVER = SSD1306
OLED_DRIVER_ENABLE  = yes

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
RGB_MATRIX_SPLIT = yes

TAPPING_TERM = 250

