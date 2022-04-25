/*

*/

#pragma once

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT
// #define LAYER_STATE_16BIT
//#define USE_MATRIX_I2C


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
#define OLED_FONT_H "glcdfont.c"
