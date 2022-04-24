/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x4653
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER rabbit88
#define PRODUCT      maize

#define MATRIX_ROWS  8
#define MATRIX_COLS  6
#define MATRIX_ROW_PINS \
    { D4, C6, D7, E6 }

#define MATRIX_COL_PINS \
    { F4, F5, B1, B3, B2, B6 }
#define DEBOUNCE 5
#define DIODE_DIRECTION COL2ROW

#define USE_SERIAL
#define USE_SERIAL_PD2
#define SOFT_SERIAL_PIN D2
#define RGB_DI_PIN      B4
//#define MAIZE_RGB_VCC_ENABLE B5

#define SPLIT_USB_DETECT
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#ifdef RGB_MATRIX_ENABLE
#   define RGBLED_NUM       54 // Number of LEDs
#   define DRIVER_LED_TOTAL RGBLED_NUM
#   define RGB_MATRIX_SPLIT { 27, 27 }
#   define SPLIT_TRANSPORT_MIRROR
#   define RGBLIGHT_SPLIT
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT

#define MASTER_LEFT
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 250

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_OLED_ENABLE

#define FORCED_SYNC_THROTTLE_MS 100
#define SPLIT_MAX_CONNECTION_ERRORS 10
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#define SPLIT_LED_STATE_ENABLE


// #define NO_DEBUG
// #define NO_PRINT
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
//*** #define USE_SERIAL


#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #define RGB_MATRIX_HUE_STEP 4
    #define RGB_MATRIX_SAT_STEP 4
    #define RGB_MATRIX_VAL_STEP 4
    #define RGB_MATRIX_SPD_STEP 10
    #define RGB_DISABLE_TIMEOUT 0
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
    // #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    // #define RGB_DISABLE_WHEN_USB_SUSPENDED
    // #define RGB_MATRIX_TYPING_MEATMAP_DECREASE_DELAY_MS 50
    // #define ENABLE_RGB_MATRIX_BREATHING
#endif
