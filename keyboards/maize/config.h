/*

*/

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER rabbit-88
#define PRODUCT      maize

/* key matrix size */
#define MATRIX_ROWS  8
#define MATRIX_COLS  6
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, B1, B3, B2, B6 }
#define UNUSED_PINS   F7, F6, B5
#define DEBOUNCE 5
#define DIODE_DIRECTION COL2ROW

// When using serial, define as D0 or D1,D2,D3,E6.
//  ./platforms/avr/drivers/serial.c:
//  ./platforms/chibios/drivers/serial.c:
/*
    if you are using serial and I2C on the board, you will need to set SOFT_SERIAL_PIN
    to something other than D0 and D1 (as these are used for I2C communication).
*/
#define SOFT_SERIAL_PIN D3  // Pin 2 aka RX aka D2
#define SELECT_SOFT_SERIAL_SPEED 1  // default, 137 kps
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
#   //define RGBLIGHT_SPLIT
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
#define SPLIT_LED_STATE_ENABLE
// #define SPLIT_POINTING_ENABLE
#define SPLIT_MODS_ENABLE

#ifdef OLED_ENABLE
#define SPLIT_OLED_ENABLE
#endif // OLED_ENABLE

#define FORCED_SYNC_THROTTLE_MS 100
#define SPLIT_MAX_CONNECTION_ERRORS 10
#define SPLIT_CONNECTION_CHECK_TIMEOUT 1000
//  normally 500 ms, not 30 seconds
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
