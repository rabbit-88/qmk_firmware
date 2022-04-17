
BOOTMAGIC_ENABLE = no		# Enable Bootmagic Lite
MOUSEKEY_ENABLE = no		# Mouse keys
EXTRAKEY_ENABLE = no		# Audio control and System control
CONSOLE_ENABLE = no			# Console for debug
COMMAND_ENABLE = no			# Commands for debug and configuration
NKRO_ENABLE = no			# Enable N-Key Rollover
BACKLIGHT_ENABLE = no		# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no		# Enable keyboard RGB underglow
AUDIO_ENABLE = no			# Audio output
UNICODE_ENABLE = no

TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

SPLIT_TRANSPORT = mirror	# serial
SPLIT_TRANSPORT_MIRROR = yes

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
RGB_MATRIX_SPLIT = yes
RGB_MATRIX_ENABLE = yes

TAPPING_TERM = 250
EXTRAFLAGS += -flto

CONSOLE_ENABLE = yes
TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = no

EXTRAKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = no

#---
# MOUSEKEY_ENABLE = no
# EXTRAKEY_ENABLE = no
#---

SPLIT_TRANSPORT = CUSTOM
