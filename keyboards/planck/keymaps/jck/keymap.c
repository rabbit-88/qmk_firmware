// planck/ez/glow:jck-sf

#include QMK_KEYBOARD_H
// #include "rgb_matrix.h"
// #include "planck.h"
// #include "glow.h"
// #include "jck-sf.h"
// #include "muse.h"
// #include "eeprom.h"
// #include "color.h"
//#include "music.h"
// #include "hebrew.h"
// #include "rgblight_list.h"
#include "raw_hid.h"

// #define TAPPING_TERM 375 // ToDo: fixme

enum custom_keycodes {
    DUMMY = SAFE_RANGE,
    RGB_SLD,
    KC_TOGGLE,
    KC_CAPSLCK,
};

typedef enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    TRIPLE_TAP,
    TRIPLE_HOLD,
    TAP_DANCE_NO_MATCH,
} _t_tap_state;

typedef struct {
    _t_tap_state state;
    _t_tap_state is_press_action;
    _t_tap_state left_brackets;
    _t_tap_state right_brackets;
    _t_tap_state right_shift;
} _t_tap;

enum tapdance_index {
    TD_BRACKETS_LEFT,
    TD_BRACKETS_RIGHT,
    TD_QUOTE_DOUBLEQUOTE,
    TD_SEMICOLON_COLON,
    TD_BSLASH_PIPE,
//    TD_SHIFT_LOCK,
};


typedef struct {
    bool active;        // true if tap-dance in progress
    uint16_t km;        //
    uint16_t kc;        // keycode
    uint32_t timer32;   // milliseconds
} _tap_mod_t;

static _tap_mod_t tm =  { .active = false,  .kc = 0, .km = 0, .timer32 = 0 } ;

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void);


uint8_t cur_dance(qk_tap_dance_state_t *state);

void l_bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void l_bracket_reset(qk_tap_dance_state_t *state, void *user_data);

void r_bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void r_bracket_reset(qk_tap_dance_state_t *state, void *user_data);

void dq_quote_finished(qk_tap_dance_state_t *state, void *user_data);
void dq_quote_reset(qk_tap_dance_state_t *state, void *user_data);

void semi_colon_finished(qk_tap_dance_state_t *state, void *user_data);
void semi_colon_reset(qk_tap_dance_state_t *state, void *user_data);

void slash_pipe_finished(qk_tap_dance_state_t *state, void *user_data);
void slash_pipe_reset(qk_tap_dance_state_t *state, void *user_data);

//void shift_lock_finished(qk_tap_dance_state_t *state, void *user_data);
//void shift_lock_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for left bracket, twice for left brace, thrice for left parenthesis
    [TD_BRACKETS_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_bracket_finished, l_bracket_reset),
    [TD_BRACKETS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_bracket_finished, r_bracket_reset),
    [TD_QUOTE_DOUBLEQUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
    [TD_SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
    [TD_BSLASH_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLASH, KC_PIPE),
//    [TD_SHIFT_LOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_lock_finished, shift_lock_reset),
};

// keymap ---------------------------------------------------------------------

enum planck_layers {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
  _LAYER5,
//   _LAYER6,    // NumPad
//   _LAYER7,    // Evrite-base
//   _LAYER8,    // Evrite-lower
//   _LAYER9,    // Evrite-raise
//   _LAYER10,   // blank
};

// "ez.h"
// planck_ez_right_led_level(uint8 level)
// planck_ez_left_led_level(uint8 level)
// planck_ez_left_led_off()
// planck_ez_right_led_off()

#define TD_LBRACKET TD(TD_BRACKETS_LEFT)
#define TD_RBRACKET TD(TD_BRACKETS_RIGHT)

#define MUTE        KC_AUDIO_MUTE
#define VOLUP       KC_AUDIO_VOL_UP
#define VOLDN       KC_AUDIO_VOL_DOWN

#define M_PLAY1     DYN_MACRO_PLAY1
#define M_PLAY2     DYN_MACRO_PLAY2
#define M_REC1      DYN_REC_START1
#define M_REC2      DYN_REC_START2
#define M_RSTOP     DYN_REC_STOP

#define RGB_TEST    RGB_MODE_RGBTEST
#define RGB_TLC     TOGGLE_LAYER_COLOR

#define MS_WUP      KC_MS_WH_UP
#define MS_WLEFT    KC_MS_WH_LEFT
#define MS_WRGHT    KC_MS_WH_RIGHT
#define MS_WDOWN    KC_MS_WH_DOWN

#define MS_BTN1     KC_MS_BTN1
#define MS_BTN2     KC_MS_BTN2

#define MS_UP       KC_MS_UP
#define MS_LEFT     KC_MS_LEFT
#define MS_RIGHT    KC_MS_RIGHT
#define MS_DOWN     KC_MS_DOWN

#define KC_MS_ACC0  KC_MS_ACCEL0
#define KC_MS_ACC1  KC_MS_ACCEL1
#define KC_MS_ACC2  KC_MS_ACCEL2

#define _PIPE      S(KC_PIPE)

#define MUTE       KC_AUDIO_MUTE
#define VOLUP      KC_AUDIO_VOL_UP
#define VOLDN      KC_AUDIO_VOL_DOWN

#define KC_BSLSH   LSFT(KC_SLASH)

#define KC_LDAQ    LALT(KC_BSLASH)
#define KC_RDAQ    LALT(S(KC_BSLASH))

#define BASE       TO(_BASE)
#define LOWER      MO(_LOWER)
#define RAISE      MO(_RAISE)
#define MOUSE      MO(_MOUSE)
#define ADJUST     MO(_ADJUST)

// #define LDAQ UC(0x00AB)
// #define RDAQ UC(0x00BB)
// #define WEBUSB     WEBUSB_PAIR
// #define HYPR1(key)  (MOD_LSFT | MOD_LALT | MOD_LGUI | key)
// #define HYPR2(key) (MOD_RSFT | MOD_RALT | MOD_RGUI | key)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_planck_grid(
//  KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_SLASH,   // TD(TD_BSLASH_PIPE)
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCOLON,  TD(TD_QUOTE_DOUBLEQUOTE),
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSFT, //KC_ENTER,
    MOUSE,      KC_LCTL,    KC_LALT,    KC_LGUI,    LOWER,      KC_SPC,     _______,    RAISE,      KC_CAPSLCK, KC_LEFT,    KC_DOWN,    KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
//  _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
    KC_GRAVE,   KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
    M_PLAY1,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_4,       KC_5,       KC_6,       KC_LDAQ,    TD_LBRACKET,
    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_1,       KC_2,       KC_3,       KC_BSLASH,  _______,
    KC_MEH,     _______,    _______,    _______,    _______,    KC_0,       _______,    _______,    KC_DOT,     KC_PLUS,    KC_MINS,    KC_EQUAL
  ),

  [_RAISE] = LAYOUT_planck_grid(
//  _______,    KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     _______,    _______,      // KC_F20 not available on macOS
    KC_TILDE,   KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,   KC_BSPACE,
    M_PLAY2,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_RDAQ,   TD_RBRACKET,
    _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_UNDS,    _PIPE,      KC_PGUP,   _______,
    KC_HYPR,    KC_RCTL,    KC_RALT,    KC_RGUI,    _______,    KC_SPC,     _______,    _______,    MS_BTN1,    KC_HOME,    KC_PGDN,   KC_END
  ),

  [_ADJUST] = LAYOUT_planck_grid(
//  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    RESET,      KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     RESET,
    RGB_TLC,    KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     XXXXXXX,    RGB_TLC,      // KC_F20 not available on macOS
    TO(5),      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_TOGGLE,  XXXXXXX,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    XXXXXXX,    M_REC1,     M_REC2,     M_RSTOP
  ),

   [_MOUSE] = LAYOUT_planck_grid(   // mouse aka action aka magic
//  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_MS_ACC2,
    XXXXXXX,    XXXXXXX,    MS_BTN1,    MS_WUP,     MS_BTN2,    XXXXXXX,    XXXXXXX,    MS_BTN1,    MS_UP,      MS_BTN2,    XXXXXXX,    KC_MS_ACC1,
    XXXXXXX,    XXXXXXX,    MS_WLEFT,   MS_WDOWN,   MS_WRGHT,   XXXXXXX,    XXXXXXX,    MS_LEFT,    MS_DOWN,    MS_RIGHT,   XXXXXXX,    KC_MS_ACC0,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_X,       KC_C,       KC_V,       KC_UP,      MS_BTN2,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    MS_BTN1,    KC_LEFT,    KC_DOWN,    KC_RIGHT
  ),

 [_LAYER5] = LAYOUT_planck_grid(   // rgb settings
    TO(0),      XXXXXXX,    RGB_HUI,    RGB_VAI,    RGB_SAI,    RGB_SPI,    RGB_M_P,    RGB_M_R,    XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_TOG,
    XXXXXXX,    XXXXXXX,    RGB_HUD,    RGB_VAD,    RGB_SAD,    RGB_SPD,    RGB_M_B,    RGB_M_SW,   XXXXXXX,    XXXXXXX,    XXXXXXX,    RGB_MOD,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
  ), /*
  [_LAYER7] = LAYOUT_planck_grid(   // Evrit-base
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_LGUI,    KC_LGUI,    KC_I,       KC_O,       KC_P,       _______,
    KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_COLN,    KC_QUOTE,
    OSM_LSFT,   KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_LABK,    KC_RABK,    KC_QUES,    _______,
    _______,    _______,    _______,    _______,    MO(8),      _______,    _______,    MO(9),      _______,    _______,    _______,    _______
  ),
  [_LAYER8] = LAYOUT_planck_grid(   // Evrit-lower
    TO(0),      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
  ),
  [_LAYER9] = LAYOUT_planck_grid(   // Evrit-raise
    TO(0),      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
  ),
 */
};
// void keyboard_post_init_user(void) {
//   rgb_matrix_enable();
// }

// {141,216,201}
#define hsv_pale_green  83,227,197
#define __pale_green     {hsv_pale_green}
#define __blue2          {154,255,255}
#define __orange         {14,255,255}
#define __yellow         {35,255,255}
#define __red            {HSV_RED}
#define __purple         {HSV_PURPLE}
#define __pink           {0,121,255}
#define __violet         {215,255,255}
#define __magenta        {HSV_MAGENTA}
#define __royal_blue     {161,181,225}
#define __blue           {HSV_BLUE}
#define __violet2        {205,113,227}
#define __orange2        { HSV_GOLDENROD }

#define __grey           {0,0,102}
#define __white          {0, 0, 255}
#define __white2         {0, 0, 254}
#define ____________     {0,0,0}

#define __teal          { HSV_TEAL }
#define  __goldenrod    { HSV_GOLDENROD }
#define __chartreuse    { HSV_CHARTREUSE }
#define __springgreen   { HSV_SPRINGGREEN }
#define __teal          { HSV_TEAL }
#define __cyan          { HSV_CYAN }
#define __azure         { HSV_AZURE }
#define __coral         { HSV_CORAL }

#define __c7     {161,181,225}
#define __c8     {43,251,250}
#define __c9     {24,247,244}
#define __cyan_  {128, 255, 255}
// #define RGB_CYAN 0x00, 0xFF, 0xFF

//                 0               1               2               3               4               5               6               7               8               9               10              11              12              13              14              16              16              17              18              19              20              21              22              23              24              25              26              27              28              29              30              31              32              33              34              35              36              37              38              39              40              41              42              43              44              45              46
//                 ESC             Q               W               E               R               T               Y               U               I               O               P               DEL             TAB             A               S               D               F               G               H               J               K               L               ;               "               LSHIFT          Z               X               C               V               B               N               M               ,               .               ?               RETURN          HYPER           CTRL            ALT             CMD/OS          LOWER           SPACE           RAISE           LEFT (BLANK)    DOWN (LEFT)     UP (DOWN)       RIGHT
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
     [_BASE]   = { __yellow,        __goldenrod,    __chartreuse,  __pale_green,   __blue2,        __springgreen,  __teal,         __cyan,         __azure,        __c7,           __c8,           __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   ____________,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green  },
     [_LOWER]  = { __teal,         __teal,         __teal,         __teal,         __teal,         __teal,         __teal,         __teal,         __teal,         __teal,         __teal,         __pale_green,   __teal,         ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   __teal,         __teal,         __teal,         __teal,         __teal,         __pale_green,   __teal,         __teal,         __teal,         __teal,         __teal,         ____________,   __teal,         __teal,         __teal,         __teal,         __pale_green,   __teal,         __pale_green,   __pale_green,   __pale_green,   __pale_green,   __teal,         __pale_green,   __teal,         __teal,         __teal,         __teal        },
     [_RAISE]  = { __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   __orange2,      __orange2,      __pale_green,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   __orange2,      __orange2,      __orange2,      __pale_green,   __orange2,      __orange2,      __orange2,      __orange2,      __pale_green,   __orange2,      __pale_green,   ____________,   __orange2,      __orange2,      __orange2     },
     [_ADJUST] = { __red,          __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __red,          __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        __coral,        ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   __coral,        ____________,    ____________,   ____________,   ____________,   ____________,   ____________,  __coral,        ____________,   __coral,        __coral,        __coral,        __coral       },
     [_MOUSE]  = { ____________,   ____________,   __yellow,       __yellow,       __yellow,       ____________,   ____________,   __yellow,       __yellow,       __yellow,       ____________,   __yellow,       ____________,   ____________,   __yellow,       __yellow,       __yellow,       ____________,   ____________,   __yellow,       __yellow,       __yellow,       ____________,   __yellow,       __pale_green,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   __yellow,       __yellow,       __yellow,       __yellow,       __yellow,       __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __pale_green,   __yellow,       __yellow,       __yellow,       __yellow      },
     [_LAYER5] = { __violet,       ____________,   __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      __orange2,      ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________,   ____________  }
};

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color( i, 0, 0, 0 );
        } else {
            RGB rgb = hsv_to_rgb( hsv );
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
        }
    }
    if (tm.active) {
        rgb_matrix_driver.set_color( 0, 255, 0, 0 );
        // rgb_matrix_set_color( 0, 255, 0, 0 );
    } else {
        rgb_matrix_driver.set_color( 0, 0, 255, 0 );
        // rgb_matrix_set_color( 0, 0, 255, 0 );
    }
}
/*
//        void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
//            rgb_matrix_ws2812_array
//            rgb_matrix_driver
//            static inline void setled(int i, uint8_t r, uint8_t g, uint8_t b);

void set_led_hsv(uint8_t i, HSV hsv) {
    // HSV hsv = {.h = h0, .s = s0, .v = v0};
    // RGB rgb = hsv_to_rgb( hsv );
    // float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    // rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    // rgb_matrix_driver.set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
}

void tm_led(bool active) {
    if (active) {
        rgb_matrix_set_color( 0, 0, 255, 0 );
        // rgb_matrix_set_color( i, 0, 255, 0 );
        // rgb_matrix_set_color( 0, RGB_CYAN );
        // set_led_hsv(0, (HSV){ HSV_MAGENTA } );
    } else {
        rgb_matrix_set_color( 0, 255, 0, 0 );
        // rgb_matrix_set_color( i, 0, 255, 0 );
        // rgb_matrix_set_color( 0, RGB_RED );
        // set_led_hsv(0, (HSV){ hsv_pale_green } );
    }
}
*/

void rgb_matrix_indicators_user(void) {
    if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
    switch (biton32(layer_state)) {
        case  0:   set_layer_color( 0); break;
        case  1:   set_layer_color( 1); break;
        case  2:   set_layer_color( 2); break;
        case  3:   set_layer_color( 3); break;
        case  4:   set_layer_color( 4); break;
        case  5:   set_layer_color( 5); break;

        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
            rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}
// void matrix_init_user(void) {
//     set_unicode_input_mode(UC_OSX); }

uint32_t layer_state_set_user(uint32_t state) {
    // layer_state_set_kb(state);
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

static bool _caps_lock = false; // ***

bool set_capslock(void) {
    register_code16(KC_LSFT);
    return _caps_lock = true;
}

bool clear_capslock(void) {
    unregister_code16(KC_LSFT);
    return _caps_lock = false;
}

bool toggle_capslock(void) {
    return (_caps_lock == true) ? clear_capslock() : set_capslock();
}

void keyboard_post_init_user(void) {
    clear_capslock();
    rgb_matrix_enable();
}

uint16_t delay(uint16_t t0, uint16_t t1) {
    return (t1 > t0) ? t1 - t0 : t0 - t1;
}

uint32_t delay32(uint32_t t0, uint32_t t1) {
    return (t1 > t0) ? t1 - t0 : t0 - t1;
}

bool short_delay(uint32_t timer32) {
    return (timer_elapsed32(timer32) < TAPPING_TERM);
}

bool long_tap(uint32_t timer32) {
    return (timer_elapsed32(timer32) > TAPPING_TERM);
}

// void raw_hid_receive(uint8_t *data, uint8_t length) {}
//
    //  void send_unicode(uint32_t code_point) {
    // send Hyper+1 to tell macOS to set Input Source to "com.apple.keylayout.UnicodeHexInput"
    // call register_unicode() to send the code_point
    // send Hyper+2 to switch back to "com.apple.keylayout.US"
    // }

void send_code16(uint16_t kc, uint16_t mods) {
    if (mods != 0) {
        set_mods(mods);
    }
    register_code16(kc);
    wait_ms(1);
    unregister_code16(kc);
    if (mods != 0) {
        clear_mods();
    }
}

void send_keycode(uint16_t kc) {    // ToDo: move to kaplan.c
    register_code16(kc);
    wait_ms(1);
    unregister_code16(kc);
}

bool process_record_user0(uint16_t keycode, keyrecord_t *record) {
    if (!tm.active) {
        if (record->event.pressed) {
            if (keycode == KC_ENTER) {          // start tap-mod sequence for KC_ENTER
                tm.timer32 = timer_read32();    // defer registering KC_ENTER keycode
                tm.active = true;
                //tm_led(tm.active);
                return false;
            }
        }
    } else {
        if (!record->event.pressed) {            // tap-mod sequence is active
            if (keycode == KC_ENTER) {          // KC_ENTER up after long tap becomes KC_ENTER
                if (long_tap(tm.timer32)) {     //  all other key-up events handled normally...
                    send_keycode(KC_ENTER);
                    tm.active = false;
                    //tm_led(tm.active);
                    return false;
               }
            }
        } else {                                // previous KC_ENTER is still being held down
            tm.active = false;
            //tm_led(tm.active);
            if (keycode != KC_ENTER) {          // KC_ENTER held with any other key becomes (shift + keycode)
                send_keycode(LSFT(keycode)) ;
                return false;
            }
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!tm.active) {
        if (record->event.pressed) {
            switch (keycode) {                  // start tap-mod sequence
                case KC_LSFT:                   //  by saving keycode and deferring handlig
                case KC_LCTRL:
                case KC_LOPT:
                case KC_LCMD:
                case KC_RSFT:
                case KC_RCTRL:
                case KC_ROPT:
                case KC_RCMD:
                    tm.kc = keycode;
                    tm.km = MOD_BIT(keycode);
                    tm.timer32 = timer_read32();
                    tm.active = true;
                    //tm_led(tm.active);
                    return false;
                case KC_CAPSLCK:
                    toggle_capslock();
                    //tm_led(tm.active);
                    return false;
                case KC_ESC:
                    clear_capslock();           // releasing ESC clears special handling
                    tm.kc = tm.km = 0;
                    tm.active = false;
                    //tm_led(tm.active);
                    return true;
                default:
                    ; // return true; // redundant
            }
        }
    } else {
        if (!record->event.pressed) {
            if (keycode == KC_ESC) {
                clear_capslock();               // releasing ESC clears special handling
                tm.kc = tm.km = 0;
                tm.active = false;
                //tm_led(tm.active);
                return true;
            }
            if (keycode == KC_RSFT && tm.kc == KC_RSFT && long_tap(tm.timer32)) {
                send_code16(KC_ENTER, tm.km);   // KC_RSFT long tap becomes KC_ENTER
                tm.kc = tm.km = 0;
                tm.active = false;
                //tm_led(tm.active);
                return false;
            }
            // return true; // redundant
        } else {
            // record->event.pressed == true
            if (short_delay(tm.timer32)) {
                if (keycode == KC_RSFT && tm.kc == KC_RSFT) {
                    keycode = KC_ENTER;         // KC_RSFT double-tap becomes KC_ENTER
                }
            }
            switch (keycode) {
                case KC_LSFT:
                case KC_LCTRL:
                case KC_LOPT:
                case KC_LCMD:
                case KC_RSFT:
                case KC_RCTRL:
                case KC_ROPT:
                case KC_RCMD:
                    tm.kc = keycode;
                    tm.km = tm.km | MOD_BIT(keycode);   // two or more modifiers have been sequentially tapped
                    tm.timer32 = timer_read32();        // restart the tap timer and wait for the next key-down event
                    break;
                default:
                    send_code16(keycode, tm.km);        // tap sequence ends (key other than modifier was tapped)
                    tm.kc = tm.km = 0;                  // register the current keycode with accumulated modifiers
                    tm.active = false;                  // and reset state machine
                    //tm_led(tm.active);
            }
            return false;
        }
    }
    return true;
}

// tap dance logic and code snippets ... https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_tap_dance.md

static _t_tap tap_state = {
    .state = 0,
    .is_press_action = true,
    .left_brackets = 0,
    .right_brackets = 0,
    .right_shift = 0
};

_t_tap_state get_tap_dance_state(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    } else if (state->count == 3) {
        // Assumes no one is trying to type the same letter three times (at least not quickly).
        // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
        // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return TAP_DANCE_NO_MATCH; // Magic number. At some point this method will expand to work for more presses
}

void l_bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_LEFT_PAREN); break;
        case SINGLE_HOLD: register_code16( KC_LEFT_PAREN); break;
        case DOUBLE_TAP:  register_code16( KC_LBRACKET); break;
        case DOUBLE_HOLD: register_code16( KC_LBRACKET); break;
        case TRIPLE_TAP:  register_code16( KC_LEFT_CURLY_BRACE); break;
        case TRIPLE_HOLD: register_code16( KC_LEFT_CURLY_BRACE); break;
        default: break;
    }
}

void l_bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_LEFT_PAREN); break;
        case SINGLE_HOLD: unregister_code16( KC_LEFT_PAREN); break;
        case DOUBLE_TAP:  unregister_code16( KC_LBRACKET); break;
        case DOUBLE_HOLD: unregister_code16( KC_LBRACKET); break;
        case TRIPLE_TAP:  unregister_code16( KC_LEFT_CURLY_BRACE); break;
        case TRIPLE_HOLD: unregister_code16( KC_LEFT_CURLY_BRACE); break;
        default: break;
    }
    tap_state.state = 0;
}

void r_bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_RIGHT_PAREN); break;
        case SINGLE_HOLD: register_code16( KC_RIGHT_PAREN); break;
        case DOUBLE_TAP:  register_code16( KC_RBRACKET); break;
        case DOUBLE_HOLD: register_code16( KC_RBRACKET); break;
        case TRIPLE_TAP:  register_code16( KC_RIGHT_CURLY_BRACE); break;
        case TRIPLE_HOLD: register_code16( KC_RIGHT_CURLY_BRACE); break;
        default: break;
    }
}

void r_bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_RIGHT_PAREN); break;
        case SINGLE_HOLD: unregister_code16( KC_RIGHT_PAREN); break;
        case DOUBLE_TAP:  unregister_code16( KC_RBRACKET); break;
        case DOUBLE_HOLD: unregister_code16( KC_RBRACKET); break;
        case TRIPLE_TAP:  unregister_code16( KC_RIGHT_CURLY_BRACE); break;
        case TRIPLE_HOLD: unregister_code16( KC_RIGHT_CURLY_BRACE); break;
        default: break;
    }
    tap_state.state = 0;
}

void semi_colon_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_SCOLON); break;
        case SINGLE_HOLD: register_code16( KC_SCOLON); break;
        case DOUBLE_TAP:  register_code16( KC_COLON); break;
        case DOUBLE_HOLD: register_code16( KC_COLON); break;
        default: break;
    }
}

void semi_colon_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_SCOLON); break;
        case SINGLE_HOLD: unregister_code16( KC_SCOLON); break;
        case DOUBLE_TAP:  unregister_code16( KC_COLON); break;
        case DOUBLE_HOLD: unregister_code16( KC_COLON); break;
        default: break;
    }
    tap_state.state = 0;
}

void dq_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_QUOTE); break;
        case SINGLE_HOLD: register_code16( KC_QUOTE); break;
        case DOUBLE_TAP:  register_code16( KC_DOUBLE_QUOTE); break;
        case DOUBLE_HOLD: register_code16( KC_DOUBLE_QUOTE); break;
        default: break;
    }
}

void dq_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_QUOTE); break;
        case SINGLE_HOLD: unregister_code16( KC_QUOTE); break;
        case DOUBLE_TAP:  unregister_code16( KC_DOUBLE_QUOTE); break;
        case DOUBLE_HOLD: unregister_code16( KC_DOUBLE_QUOTE); break;
        default: break;
    }
    tap_state.state = 0;
}

void slash_pipe_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_SLASH); break;
        case SINGLE_HOLD: register_code16( KC_SLASH); break;
        case DOUBLE_TAP:  register_code16( KC_PIPE); break;
        case DOUBLE_HOLD: register_code16( KC_PIPE); break;
        default: break;
    }
}

void slash_pipe_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_SLASH); break;
        case SINGLE_HOLD: unregister_code16( KC_SLASH); break;
        case DOUBLE_TAP:  unregister_code16( KC_PIPE); break;
        case DOUBLE_HOLD: unregister_code16( KC_PIPE); break;
        default: break;
    }
    tap_state.state = 0;
}

// void shift_lock_finished(qk_tap_dance_state_t *state, void *user_data) {
//     switch (tap_state.state) {
//         case SINGLE_TAP:  register_code16( OSM(MOD_LSFT)); break;
//         case SINGLE_HOLD: register_code16( KC_NO); break;
//         case DOUBLE_TAP:  register_code16( KC_NO); break;
//         case DOUBLE_HOLD: register_code16( KC_NO); break;
//         default: break;
//     }
//     tap_state.state = 0;
// }
// void shift_lock_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (tap_state.state) {
//         case SINGLE_TAP:  unregister_code16( KC_NO); break;
//         case SINGLE_HOLD: unregister_code16( KC_NO); break;
//         case DOUBLE_TAP:  unregister_code16( KC_NO); break;
//         case DOUBLE_HOLD: unregister_code16( KC_NO); break;
//         default: break;
//     }
//     tap_state.state = 0;
// }

/*
    See KC_LOCK in quantum/process_keycode/process_key_lock.c
*/
// EOF


