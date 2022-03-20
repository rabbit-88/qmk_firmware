/*
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
// #include "quantum.h"

// qmk/quantum/config_common.h
#ifndef __ASSEMBLER__
#  include "pin_defs.h"
#endif

/* diode directions */
#define COL2ROW 0
#define ROW2COL 1

#define VENDOR_ID    0x4653
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER rabbit-88
#define PRODUCT      Maize

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS  8
#define MATRIX_COLS  6
#define MATRIX_ROW_PINS \
    { D4, C6, D7, E6 }

// wiring of each half
#define MATRIX_COL_PINS \
    { F4, F5, B1, B3, B2, B6 }

#define DEBOUNCE 5
#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D2
// is D2 same as TX (PIN 2)
// is D1 same as RX (PIN 1)
#define RGB_DI_PIN      D1
// is ProMicro PIN 1 assigned label D1?
#define MAIZE_RGB_VCC_ENABLE B5

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_SPLIT  { 27, 27 }
#    define RGBLED_NUM          54
#    define SPLIT_TRANSPORT_MIRROR
#endif

#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif // OLED_ENABLE

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define FORCED_SYNC_THROTTLE_MS 100
#define SPLIT_MAX_CONNECTION_ERRORS 10
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#define SPLIT_LED_STATE_ENABLE

#define has_usb() is_keyboard_master()
#define is_master is_keyboard_master()

// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION

/*
    PIN 1 = TX ==> USB-C connector SBU2/B8
    PIN 2 = RX ==> USB-C connector SBU1/A8
    PIN 5 = SDA (no change from crkbd)
    PIN 6 = SCL (no change from crkbd)
    PIN 7-10 => row0, row1 row2, row3
    PIN 8 = RGB data
    PIN 9 = RGB enable
    PIN 20,19,16,15,14,13 = col0,col1,col2,col3,col4,col5
*/

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT

#define MASTER_LEFT
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 250

