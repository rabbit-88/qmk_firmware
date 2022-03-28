/*

*/

#pragma once

#include "rev1/config.h"

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT
// #define LAYER_STATE_16BIT
//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 250
#define DIODE_DIRECTION COL2ROW
#define USE_SERIAL_PD2
#define SOFT_SERIAL_PIN D2

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define FORCED_SYNC_THROTTLE_MS 100
#define SPLIT_MAX_CONNECTION_ERRORS 10
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#define SPLIT_LED_STATE_ENABLE
//#define SPLIT_WPM_ENABLE

// #ifdef OLED_ENABLE
#define SPLIT_OLED_ENABLE
// #endif // OLED_ENABLE


#define RGB_DI_PIN      D3
#define RGBLIGHT_SPLIT

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
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    // #define RGB_DISABLE_WHEN_USB_SUSPENDED
    // #define RGB_MATRIX_TYPING_MEATMAP_DECREASE_DELAY_MS 50
    #define ENABLE_RGB_MATRIX_BREATHING
#endif

// Corne logo
//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
// QMK logo
#define OLED_FONT_H "keyboards/crkbd/keymaps/jck/glcdfont.c"
