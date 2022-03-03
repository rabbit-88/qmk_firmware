/*

*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keycode.h"
// #include "config.h"
// #include "crkbd.h"
#include "color.h"
#include "rev1.h"
// #include "rgb_matrix.h"
// #include "rgb_matrix/rgb_matrix.h"

#define MUTE        KC_AUDIO_MUTE
#define VOLUP       KC_AUDIO_VOL_UP
#define VOLDN       KC_AUDIO_VOL_DOWN

#define M_PLAY1     DYN_MACRO_PLAY1
#define M_PLAY2     DYN_MACRO_PLAY2
#define M_REC1      DYN_REC_START1
#define M_REC2      DYN_REC_START2
#define M_RSTOP     DYN_REC_STOP


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

// #define TAPPING_TERM 375

#ifdef TAP_DANCE_ENABLE
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
};

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

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for left bracket, twice for left brace, thrice for left parenthesis
    [TD_BRACKETS_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_bracket_finished, l_bracket_reset),
    [TD_BRACKETS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_bracket_finished, r_bracket_reset),
    [TD_QUOTE_DOUBLEQUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
    [TD_SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
    [TD_BSLASH_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLASH, KC_PIPE),
};
    #define TD_QDQ      TD(TD_QUOTE_DOUBLEQUOTE)
    #define TD_LBRCKT   TD(TD_BRACKETS_LEFT)
    #define TD_RBRCKT   TD(TD_BRACKETS_RIGHT)
#else
    #define TD_QDQ      KC_QUOT
    #define TD_LBRCKT   KC_LBRACKET
    #define TD_RBRCKT   KC_RBRACKET

#endif //  TAP_DANCE_ENABLE

enum custom_keycodes {
    DUMMY = SAFE_RANGE,
    KC_T_SLASH,         // if true, KC_SLASH; if false, KC_UP
    RGB_RSET,
    KC_CAPSLCK,
};

enum _layers {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
  _LAST
};

const char _layer_names_str[7][2] = {
    "B", "L", "R", "A", "M", "r", "?"
 };
const char _layer_names_char[7]= {
    'B', 'L', 'R', 'A', 'M', 'r', '?'
 };

#define _PIPE      S(KC_PIPE)
#define KC_LDAQ    LALT(KC_BSLASH)
#define KC_RDAQ    LALT(S(KC_BSLASH))

#define BASE       TO(_BASE)
#define LOWER      MO(_LOWER)
#define RAISE      MO(_RAISE)
#define MOUSE      MO(_MOUSE)
#define ADJUST     MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
      KC_TAB,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MOUSE,   LOWER,  KC_SPC,     KC_SPC,   RAISE,   MOUSE
  ),
  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_GRAVE,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    _______,
      M_REC1,  KC_INS,  KC_HOME, KC_PGUP, XXXXXXX, KC_END,                       XXXXXXX, KC_4,   KC_5,    KC_6,    KC_LDAQ, TD_LBRCKT,
     M_PLAY1,  KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_1,   KC_2,    KC_3,    KC_BSLASH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,   KC_0,    _______, _______
  ),
  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TILDE,KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
     M_REC2,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_UNDS, KC_PLUS, KC_EQUAL,KC_RDAQ, TD_RBRCKT,
     M_PLAY2, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, RGB_TOG,                      RGB_TOG, KC_RCTL, KC_RALT, KC_RCMD, _PIPE,   _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,   _______, _______, _______
  ),
  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, RESET,
     M_RSTOP, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                       KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F11, XXXXXXX,   // KC_F20 not available on macOS
     XXXXXXX, KC_ASRP, KC_ASON, KC_ASOFF,KC_ASUP, KC_ASDN,                      LSFT(XXXXXXX), XXXXXXX, XXXXXXX, XXXXXXX, KC_F12, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
  ),
  [_MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_HUI, XXXXXXX, MS_BTN1, MS_UP,  MS_BTN2, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, RGB_HUD,
      RGB_VAI, XXXXXXX, MS_LEFT, MS_DOWN,MS_RIGHT,XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, RGB_VAD,
      RGB_SAI, RGB_SPI, XXXXXXX,XXXXXXX, XXXXXXX, RGB_MOD,                      RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPD, RGB_SAD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
  ),
};

// #define KEYBOARD_SYNC_A
// #define KEYBOARD_SYNC_B
// #define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC_A, KEYBOARD_SYNC_B

// keyrecord_t record {
//   keyevent_t event {
//     keypos_t key {
//       uint8_t col
//       uint8_t row
//     }
//     bool     pressed
//     uint16_t time
//   }
// }

static bool keyboard_is_active = false;
static bool b_LSFT = false;


////////////////////////////////////////////////////////
//
//  DEBUG LOGIC
//
uint16_t flags = 0;
#if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
char* get_buffer(void);
void clear_buffer(void);
void update_buffer( uint16_t keycode, keyrecord_t *record, char c);
#endif
#ifdef OLED_ENABLE
void oled_render_logo(void);
void oled_render_buffer(void);
#endif



///////////////////////////////////////////////////////
//
//  QMK callbacks
//
void keyboard_pre_init_kb(void) {
    // setPinOutput(B0) ... etc.
    keyboard_pre_init_user();
    return;
}

void keyboard_pre_init_user(void) {
    return;
}

//  keyboard_post_init_
//  gets called at the end of all QMK processing, before starting the next iteration.
//  You can safely assume that QMK has dealt with the last matrix scan at the time that
//  these functions are invoked – layer states have been updated, USB reports have been
//  sent, LEDs have been updated, and displays have been drawn.


extern debug_config_t debug_config;
bool keyboard_post_init_b = false;

void keyboard_post_init_user(void) {
    debug_config.enable=true;
    debug_config.mouse=true;
    #if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
    clear_buffer();
    #endif
    #ifdef OLED_ENABLE
    oled_render_logo();
    #endif
    #ifdef RGB_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR); // ****
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    flags = flags | 0x01;
      // Call the post init code.
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
    #endif
}

// void suspend_power_down_user(void) {
//     // code will run multiple times while keyboard is suspended
// }

// void suspend_wakeup_init_user(void) {
//     // code will run on keyboard wakeup
// }

// void housekeeping_task_kb(void) {
// }

void keyboard_post_init_kb(void) {
    flags = flags | 0x02;
    keyboard_post_init_user();
}

void housekeeping_task_user(void) {
    if (keyboard_post_init_b == false) {
        keyboard_post_init_user();
        flags = flags | 0x04;
        #ifdef CONSOLE_ENABLE
        dprintf("housekeeping: %x\n", flags);
        #endif
        keyboard_post_init_b = true;
        debug_config.enable = true;
        debug_config.matrix = false;
        debug_config.mouse = false;
        debug_config.keyboard = false;

    }
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}
bool oled_task_kb(void) {
    if (keyboard_is_active) {
        oled_clear();
        oled_render_buffer();
    } else {
        oled_render_logo();
    }
    return true;
}
#endif // OLED_ENABLE

struct _last_event_t {
    uint8_t  row, col, pressed;
    uint16_t keycode;
} _last_event;

layer_state_t layer_state_set_user(layer_state_t state) {
    // QMK documentation indicates rgblight_setrgb( red, green, blue) can be called here
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

#ifdef RGB_MATRIX_ENABLE
// extern bool rgb_matrix_get_suspend_state(void); // { return g_suspend_state; }
extern void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
extern void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

// quantum/action_layer.h: #define get_highest_layer(state) biton(state)

// what is g_led_config.matrix_co ??

// void rgb_matrix_indicators_advanced_xxx(uint8_t led_min, uint8_t led_max) { ... }
/*

    IS_LAYER_ON_STATE(state, layer)
    IS_LAYER_OFF_STATE(state, layer)
    IS_LAYER_ON(layer)
    IS_LAYER_OFF(layer)

    layer_state_t layer_state_set_kb(layer_state_t state)
    layer_state_t layer_state_set_user(layer_state_t state)
    state is the bitmask of active layers

    This sets up a 32 bit structure that we can store settings with in memory,
    and write to the EEPROM. Using this removes the need to define variables,
    since they’re defined in this structure

    typedef union {
        uint32_t raw;
        struct {
            bool rgb_layer_change :1;
        };
    } user_config_t;

    user_config_t user_config;

    user_config.raw = eeconfig_read_user();
    if (user_config.rgb_layer_change) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom_cyan();
        rgblight_mode_noeeprom(1);
    }

    void eeconfig_init_user(void) {  // EEPROM is getting reset!
        user_config.raw = 0;
        user_config.rgb_layer_change = true; // We want this enabled by default
        eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

        // use the non noeeprom versions, to write these values to EEPROM too
        rgblight_enable(); // Enable RGB by default
        rgblight_sethsv_cyan();  // Set it to CYAN by default
        rgblight_mode(1); // set to solid by default
    }
    see https://docs.qmk.fm/#/custom_quantum_functions?id=example-keyboard_pre_init_user-implementation

    deferred executor callbacks available!
*/


uint8_t previous_layer = 255; //
void set_layer_color(uint8_t layer) {
    switch(layer) {
        case _BASE:   rgb_matrix_set_color_all(0x00, 0x00, 0xFF);    break;    // blue
        case _LOWER:  rgb_matrix_set_color_all(0x00, 0xFF, 0x00);    break;    // green
        case _RAISE:  rgb_matrix_set_color_all(0xFF, 0xFF, 0x00);    break;    // yellow
        case _ADJUST: rgb_matrix_set_color_all(0x00, 0xFF, 0xFF);    break;    // cyan
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                rgb_matrix_set_color_all(0, 0, 0);
            else
                rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
    }
}
void rgb_matrix_indicators_kb(void) {
    // kb() implementations responsible for calling user()
    uint8_t j = get_highest_layer(layer_state);
    if (j != previous_layer) {
        previous_layer = j;
        #ifdef CONSOLE_ENABLE
        uprintf("Layer: %d \n", j);
        #endif
        set_layer_color(j);
    }
}

// void rgb_matrix_indicators_user(void) {
// }
#endif // RGB_MATRIX_ENABLE

////////////////////////////////////////////////////////
//
//  PROCESS RECORD

uint16_t deltaTau16(uint16_t t0, uint16_t t1) {
    return (t1 > t0) ? t1 - t0 : t0 - t1;
}

uint32_t deltaTau32(uint32_t t0, uint32_t t1) {
    return (t1 > t0) ? t1 - t0 : t0 - t1;
}

bool short_delay(uint32_t timer32) {
    return (timer_elapsed32(timer32) < TAPPING_TERM);
}

bool long_delay(uint32_t timer32) {
    return (timer_elapsed32(timer32) > TAPPING_TERM);
}

void send_kcode(uint16_t kc, uint16_t mods) {       // should we just OR the mods into the keycode instead?
    set_mods(mods);
    register_code16(kc);
    wait_ms(1);
    unregister_code16(kc);
    clear_mods();
}

    /*
        enum hid_keyboard_keypad_usage {
            KC_NO = 0x00,
            KC_ROLL_OVER,
            KC_POST_FAIL,
            KC_UNDEFINED,
            KC_A,
            ...
            KC_Z,
            ...
            KC_LEFT,  // 0x50
            ...
            KC_F21,  // 0x70
            ...
            // Modifiers
            KC_LEFT_CTRL = 0xE0,
            KC_LEFT_SHIFT,
            KC_LEFT_ALT,
            KC_LEFT_GUI,
            KC_RIGHT_CTRL,
            KC_RIGHT_SHIFT,
            KC_RIGHT_ALT,
            KC_RIGHT_GUI
        );
        //  modifiers: QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI | QK_RCTL | QK_RSFT | QK_RALT | QK_RGUI;
    */

////////////////////////////////////////////////////////
//
// Keyboard State Machine

typedef struct {
    bool active;        // true if state-machine is active
    uint16_t km;        //
    uint16_t kc;        // keycode
    uint32_t timer32;   // milliseconds
} _last_key_pressed;

static _last_key_pressed SQ =  { .active = false,  .kc = 0, .km = 0, .timer32 = 0 } ;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
    if (record->event.pressed) {
        switch (keycode) {
            case KC_ESC: keyboard_is_active = false;
                update_buffer(keycode, record, 'E');
                break;
            case KC_TAB:
                rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
                update_buffer(keycode, record, 'T');
            default:
                keyboard_is_active = true;
        }
    }
    #endif
    if (!SQ.active) {
        if (record->event.pressed) {
            if  (b_LSFT == true) {
                if (keycode == RGB_HUI)
                        keycode = RGB_HUD;
                if (keycode == RGB_VAI)
                        keycode = RGB_VAD;
                if (keycode == RGB_SAI)
                        keycode = RGB_SAD;
                if (keycode == RGB_SPI)
                        keycode = RGB_SPD;
            }
            if (IS_MOD(keycode) || keycode == KC_LSFT || keycode == KC_RSFT) {
                SQ.kc = keycode;
                SQ.km = MOD_BIT(keycode);
                SQ.timer32 = timer_read32();
                SQ.active = true;
                #ifdef CONSOLE_ENABLE
                dprintf("M: %04x %x\n", SQ.kc, SQ.km);
                update_buffer(keycode, record, 'M'); //**
                #endif
                return false;
            } else {
                #ifdef CONSOLE_ENABLE
                update_buffer(keycode, record, 'A'); //**
                #endif
            }
        }
    } else {
        if (!record->event.pressed) {
            if (keycode == KC_ESC) {            // releasing ESC clears state-machine
                SQ.kc = SQ.km = 0;
                SQ.active = false;
                if (b_LSFT == true)
                    dprintf("caps-lock off 1\n");
                b_LSFT = false;
                //#ifdef CONSOLE_ENABLE
                update_buffer(keycode, record, 'e'); //**
                //#endif
            }
            if (keycode == KC_RSFT && SQ.kc == KC_RSFT && long_delay(SQ.timer32)) {
                send_kcode(KC_ENTER, SQ.km);    // releasing KC_RSFT long tap becomes KC_ENTER
                SQ.kc = SQ.km = 0;
                SQ.active = false;
                return false;
            }
            if (keycode == KC_LSFT && SQ.kc == KC_LSFT && long_delay(SQ.timer32)) {
                b_LSFT = true;                  // releasing KC_LSFT long tap becomes CAPS-LOCK
                //#ifdef CONSOLE_ENABLE
                dprintf("caps-lock 1\n");
                //#endif
            }
        } else {
            // keycode pressed, state-machine is active, last key pressed was SQ.kc
            if (short_delay(SQ.timer32)) {
                if (keycode == KC_RSFT) {
                    keycode = KC_ENTER;         // KC_RSFT double-tap becomes KC_ENTER
                }
                if (keycode == KC_LSFT) {
                    b_LSFT = true;              // KC_LSFT double-tap becomes CAPS-LOCK
                    //#ifdef CONSOLE_ENABLE
                    dprintf("caps-lock 2\n");
                    //#endif
                }
            }
            if IS_MOD(keycode) {
                SQ.kc = keycode;
                dprintf("m: %04x %x\n", SQ.kc, MOD_BIT(keycode));
                SQ.km = SQ.km | MOD_BIT(keycode);   // two or more modifiers have been sequentially tapped
                SQ.timer32 = timer_read32();        // restart the tap timer and wait for the next key-down event
                //#ifdef CONSOLE_ENABLE
                update_buffer(keycode, record, 'm'); //**
                //#endif
                return true;
            }
            if (b_LSFT == true || SQ.kc == KC_LSFT) {
                dprintf("l: %04x %x\n", SQ.kc, MOD_BIT(keycode));
                SQ.km = SQ.km | MOD_BIT(KC_LSFT);
                dprintf("caps-lock 3\n");
            }
            send_kcode(keycode, SQ.km);         // tap sequence ends (key other than modifier was tapped)
            SQ.kc = SQ.km = 0;                  // register the current keycode with accumulated modifiers
            SQ.active = false;                  // and reset state machine
            //#ifdef CONSOLE_ENABLE
            update_buffer(keycode, record, 'a'); //**
            //#endif
            return false;
        }
    }
    return true;
}


////////////////////////////////////////////////////////
//
//  DEBUG LOGIC

#if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)

const char _keycode_to_name[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'r', 'e', 'b', 't', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', 'c', ' ', ' ' };

    // also see https://docs.qmk.fm/#/squeezing_avr?id=oled-tweaks

uint8_t keycode2char(uint16_t keycode) {
    keycode = keycode & 0xFF;
    if (keycode < KC_CAPS) {
        return _keycode_to_name[keycode];
    }
    return _keycode_to_name[0];
}
#define bufferSize 64
char _buffer[bufferSize];
char* get_buffer(void) {
    return &_buffer[0];
};
void clear_buffer(void) {
  for (uint8_t i = 0; i < bufferSize ; i++) {
      _buffer[i] = ' ';
  }
}

void update_buffer( uint16_t keycode, keyrecord_t *record, char tag) {
    #if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
    uint8_t i = previous_layer;
    char p = (i < _LAST) ? _layer_names_char[i] : _layer_names_char[_LAST];
    char c = (char)(keycode2char( keycode));
    snprintf( get_buffer(), bufferSize,
        "%c: %d %c %1d:%02d K%04x : %c",
        tag, i, p, record->event.key.row, record->event.key.col, keycode, c);
    if (flags != 0) {
        dprintf("flags: %02X\n", flags);
        flags = 0;
    }
    dprintf("%s\n", get_buffer());
    #endif
}
#endif

////////////////////////////////////////////////////////
//
//  OLED LOGIC
//

#ifdef OLED_ENABLE

void oled_write(const char *data, bool invert);         // writes a char string
void oled_write_char(const char data, bool invert);     // writes a single char
void oled_write_ln(const char *data, bool invert);      // writes a line, advances page
void oled_write_ln_P(const char *data, bool invert);    // writes a PSTR line

void oled_render_buffer(void) {
    // called from oled_task_user or oled_task_kb
    oled_write_char( '>', true);
    oled_write_ln(get_buffer(),false);
}

void oled_render_logo(void) {
    static const char PROGMEM logo[] = {
        // logo sits instide of font file
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0x00
    };
    oled_clear();
    oled_write_P(logo, false);
}

// void render_bootmagic_status(bool status) {
//     /* Show Ctrl-Gui Swap options */
//     static const char PROGMEM logo[][2][3] = {
//         {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
//         {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
//     };
//     if (status) {
//         oled_write_ln_P(logo[0][0], false);
//         oled_write_ln_P(logo[0][1], false);
//     } else {
//         oled_write_ln_P(logo[1][0], false);
//         oled_write_ln_P(logo[1][1], false);
//     }
// }

#endif // OLED_ENABLE


#ifdef RGB_MATRIX_ENABLE
////////////////////////////////////////////////////////
//
//  RGB LOGIC   (keyboard dependent)
//

// uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);
// extern bool rgb_matrix_get_suspend_state(void); // { return g_suspend_state; }
// extern bool g_suspend_state;
// extern rgb_config_t rgb_matrix_config;

RGB _palete[13] = { { RGB_OFF },  { RGB_WHITE }, { RGB_RED }, { RGB_GREEN }, { RGB_BLUE },
                    { RGB_CYAN }, { RGB_MAGENTA }, { RGB_YELLOW },
                    { RGB_TEAL }, { RGB_ORANGE }, { RGB_GOLDENROD }, { RGB_CHARTREUSE },
                    { RGB_PURPLE }
 };

enum _colors {
    OFF, W, R, G, B, C, M, Y, T, O, GD, CE
};

uint8_t _layers[6][2][27] = {
    //    10: Space,  11: Lower, 12: Mouse                      13: ESC, 14: TAB, 15: SHFT
    //    20: Return, 21: Raise, 22: Mouse                      23: DEL, 24: Quote, 25: Return
    //    10 B  G  T  R  F  V  11 12 C  D  E  W  S  X  Z  A  Q  13 14 15 _  _  _  _  _  _
    //    20 N  H  Y  U  J  M  21 22 ,  K  I  O  L  .  /  ;  P  23 24 25 _  _  _  _  _  _
    [_BASE] =
    {   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    },
    [_LOWER] =
    {   { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
    },
    [_RAISE] =
    {   { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }
    },
    [_ADJUST] =
    {   { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
    },
    [_MOUSE]  =
    {   { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
        { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }
    },
};

#endif // RGB_MATRIX_ENABLE


/////////////////////////////////////////////////////////
//
//  TAP DANCE   (keyboard idependent code)
//
//  qmk-firmware/docs/feature_tap_dance.md

#ifdef TAP_DANCE_ENABLE

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

//  Note:   here is no need to optimize the SWITCH/CASE statements below to save a few bytes,
//          the gcc compiler optimizes the code itself -- it's amazingly efficient

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

#endif //  TAP_DANCE_ENABLE

/*
split_util.h:
    extern volatile bool isLeftHand;
    void matrix_master_OLED_init(void);
    void split_pre_init(void);
    void split_post_init(void);
    bool transport_master_if_connected(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]);
    bool is_transport_connected(void);

split_util.c:
    static bool usbIsActive(void);
    __attribute__((weak)) bool is_keyboard_left(void);
    __attribute__((weak)) bool is_keyboard_master(void);
*/
// EOF
