# Maize rules

MCU = atmega32u4
BOOTLOADER = caterina

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no           	# Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
UNICODE_ENABLE = no

OLED_ENABLE = no			# can not enable CONSOLE and OLED at the same time
OLED_DRIVER = SSD1306
OLED_DRIVER_ENABLE  = no

RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812

# link time optimization
LTO_ENABLE = yes

SPLIT_KEYBOARD = yes
RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_SPLIT = yes

LAYOUTS = split_3x6_3

TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no

TAPPING_TERM = 250
BLINK_RATE = 500
AUTOREPEAT_RATE = 125
EXTRAFLAGS += -flto

GET_AUTO_SHIFT_REPEAT = no
GET_AUTO_REPEAT_PER_KEY = no
