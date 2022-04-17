
MCU = atmega32u4
BOOTLOADER = caterina

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

OLED_ENABLE = no			# can not enable CONSOLE and OLED at the same time
OLED_DRIVER_ENABLE  = no

SPLIT_TRANSPORT = mirror	# serial
SPLIT_TRANSPORT_MIRROR = yes

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_SPLIT = yes
# RGB_MATRIX_KEYREACTIVE_ENABLED = yes

# RGB_MATRIX_ENABLE && RGB_MATRIX_SPLIT ... rgb_matrix_drivers

TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

TAPPING_TERM = 250
EXTRAFLAGS += -flto

#--- 5600 bytes
# OLED_ENABLE = no
# EXTRAKEY_ENABLE = yes
#---
# GET_AUTO_SHIFT_REPEAT = yes
# GET_AUTO_REPEAT_PER_KEY = yes

#--- CONSOLE or TAP_DANCE but not both
CONSOLE_ENABLE = yes
TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no
#---

#---
# MOUSEKEY_ENABLE = no
# EXTRAKEY_ENABLE = no
#---

SPLIT_TRANSPORT = CUSTOM
