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

typedef struct {
    bool active;        // true if tap-dance in progress
    uint16_t km;        //
    uint16_t kc;        // keycode
    uint32_t timer32;   // milliseconds
} _tap_mod_t;

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
    #define TD_QDQ      KC_NO
    #define TD_LBRCKT   KC_NO
    #define TD_RBRCKT   KC_NO

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
  _RGB,
  _LAST
};

const char _layer_names[7][2] = {
    "B", "L", "R", "A", "M", "r", "?"
 };

#define _PIPE      S(KC_PIPE)
#define KC_LDAQ    LALT(KC_BSLASH)
#define KC_RDAQ    LALT(S(KC_BSLASH))

#define BASE       TO(_BASE)
#define LOWER      MO(_LOWER)
#define RAISE      MO(_RAISE)
#define MOUSE      MO(_MOUSE)
#define ADJUST     MO(_ADJUST)
#define TO_RGB     TO(_RGB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
      KC_TAB,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MOUSE,   LOWER,  KC_SPC,     KC_ENT,   RAISE,   MOUSE
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
     XXXXXXX, KC_ASRP, KC_ASON, KC_ASOFF,KC_ASUP, KC_ASDN,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,  _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         TO_RGB,  _______, _______,    _______, _______, TO_RGB
  ),
  [_MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, MS_BTN1,  MS_WUP, MS_BTN2, XXXXXXX,                      XXXXXXX, MS_BTN1,   MS_UP, MS_BTN2, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, MS_WLEFT,MS_WDOWN,MS_WRGHT,XXXXXXX,                      XXXXXXX, MS_LEFT, MS_DOWN,MS_RIGHT, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD,                      RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
  ),
  [_RGB] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,RGB_TOG, RGB_M_R, RGB_M_B, XXXXXXX, RGB_RSET,                     XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX,RGB_SPI, RGB_HUI, RGB_VAI, RGB_SAI, RGB_MOD,                      XXXXXXX, RGB_SPI, RGB_HUI, RGB_VAI, RGB_SAI, RGB_MOD,
      XXXXXXX,RGB_SPD, RGB_HUD, RGB_VAD, RGB_SAD, RGB_RMOD,                     XXXXXXX, RGB_SPD, RGB_HUD, RGB_VAD, RGB_SAD, RGB_RMOD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, BASE,      BASE,    _______, _______
  )
};
/*
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
  ),
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
  ),
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, _______, KC_RALT
  ),
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
  )
};
*/


// #define KEYBOARD_SYNC_A
// #define KEYBOARD_SYNC_B
// #define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC_A, KEYBOARD_SYNC_B

////////////////////////////////////////////////////////
//
//  DEBUG LOGIC
//
#if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
char* get_buffer(void);
void clear_buffer(void);
void update_buffer( uint16_t keycode, keyrecord_t *record);
#endif
#ifdef OLED_ENABLE
void oled_render_logo(void);
void oled_render_buffer(void);
#endif
struct _last_event_t {
    uint8_t  row, col, pressed;
    uint16_t keycode;
} _last_event;

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_mouse=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    #if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
    clear_buffer();
    #endif
    #ifdef OLED_ENABLE
    oled_render_logo();
    #endif
}

bool _active = false;

// #ifdef RGB_MATRIX_ENABLE
// void set_layer_color(int layer);
// extern bool rgb_matrix_get_suspend_state(void); // { return g_suspend_state; }
// #endif // RGB_MATRIX_ENABLE

// void keyboard_post_init_kb(void) {}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}
bool oled_task_kb(void) {
    if (_active) {
        oled_clear();
        oled_render_buffer();
    } else {
        oled_render_logo();
    }
    return true;
}
#endif // OLED_ENABLE

// void housekeeping_task_user(void) {
// }
// void housekeeping_task_kb(void) {
// }
// void keyboard_pre_init_kb(void) {
// }

// #ifdef RGB_MATRIX_ENABLE
// void keyboard_post_init_kb(void) {
//     // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
// }
// #endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ESC) {
        _active = false;
    }
    if (record->event.pressed) {
        _active = true;
        #if defined(OLED_ENABLE) || defined(CONSOLE_ENABLE)
        update_buffer(keycode, record);
        #endif
    }
    return true;
}
    // update_tri_layer(_LOWER, _RAISE, _ADJUST);
    // switch(biton32(layer_state)) {
    //     case _BASE:
    //         rgb_matrix_set_color_all(RGB_BLUE);     break;
    //     case _LOWER:
    //         rgb_matrix_set_color_all(RGB_GREEN);    break;
    //     case _RAISE:
    //         rgb_matrix_set_color_all(RGB_RED);      break;
    //     case _ADJUST:
    //         rgb_matrix_set_color_all(RGB_YELLOW);   break;
    // }

////////////////////////////////////////////////////////
//
//  PROCESS RECORD

static _tap_mod_t tm =  { .active = false,  .kc = 0, .km = 0, .timer32 = 0 } ;

static bool _caps_lock = false;       // ***
// static bool _toggle_slash = false;    // ToDo Fix Me

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

void send_kcode(uint16_t kc, uint16_t mods) {
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

// void send_keycode(uint16_t kc) {    // ToDo: move to kaplan.c
//     // tap_code_delay(1,kc);
//     register_code16(kc);
//     wait_ms(1);
//     unregister_code16(kc);
//}

bool process_record_local(uint16_t keycode, keyrecord_t *record) {
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
                    return false;
                case KC_CAPSLCK:
                    toggle_capslock();
                    return false;
                case KC_ESC:
                    clear_capslock();           // releasing ESC clears special handling
                    tm.kc = tm.km = 0;
                    tm.active = false;
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
                return true;
            }
            if (keycode == KC_RSFT && tm.kc == KC_RSFT && long_delay(tm.timer32)) {
                send_kcode(KC_ENTER, tm.km);   // releasing KC_RSFT long tap becomes KC_ENTER
                tm.kc = tm.km = 0;
                tm.active = false;
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
                    send_kcode(keycode, tm.km);        // tap sequence ends (key other than modifier was tapped)
                    tm.kc = tm.km = 0;                  // register the current keycode with accumulated modifiers
                    tm.active = false;                  // and reset state machine
            }
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
void update_buffer( uint16_t keycode, keyrecord_t *record) {
    uint16_t i = biton32(layer_state);
    // const char *p = _layer_names[0];
    // if (i < 7) {
    //     p = _layer_names[i];
    // };
    char c = (char)(keycode2char( keycode));
    snprintf( get_buffer(), bufferSize,
        ":%d: %1d:%02d : K%04x : %c",
        i, record->event.key.row, record->event.key.col, keycode, c);
    #ifdef CONSOLE_ENABLE
    uprintf("%s\n", get_buffer());
    #endif
}
#endif

////////////////////////////////////////////////////////
//
//  OLED LOGIC
//

#ifdef OLED_ENABLE

// #define L_BASE 0
// #define L_LOWER 2
// #define L_RAISE 4
// #define L_ADJUST 8
// #define L_MOUSE 16
// #define L_RGB 32

void oled_write(const char *data, bool invert);         // writes a char string
void oled_write_char(const char data, bool invert);     // writes a single char
void oled_write_ln(const char *data, bool invert);      // writes a line, advances page
void oled_write_ln_P(const char *data, bool invert);    // writes a PSTR line

// uint8_t const keylog_size = 24;
// char keylog_str[24] = {};

void oled_render_buffer(void) {
    // called from oled_task_user or oled_task_kb
    oled_write_char( '>', true);
    oled_write_ln(get_buffer(),false);
}

void oled_render_logo(void) {
    static const char PROGMEM logo[] = {
        // QMK logo
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
//  RGB LOGIC
//

//  uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);

// extern bool rgb_matrix_get_suspend_state(void); // { return g_suspend_state; }
// extern bool g_suspend_state;
// extern rgb_config_t rgb_matrix_config;

extern void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
extern void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

RGB _palete[10] = { { RGB_OFF },    { RGB_WHITE} ,  { RGB_RED },
                    { RGB_TEAL },   { RGB_ORANGE }, { RGB_MAGENTA },
                    { RGB_BLUE },   { RGB_GREEN },  { RGB_YELLOW },
                    { RGB_GOLDENROD }
 };

// void rgb_matrix_indicators_user(void) {
//     uint8_t layer = biton32(layer_state);
//     switch(layer) {
//         case 0: rgb_matrix_set_color_all( RGB_WHITE ); break;
//         case 1: rgb_matrix_set_color_all( RGB_RED ); break;
//         case 2: rgb_matrix_set_color_all( RGB_GREEN ); break;
//         case 3: rgb_matrix_set_color_all( RGB_BLUE ); break;
//         case 4: rgb_matrix_set_color_all( RGB_YELLOW ); break;
//         case 5: rgb_matrix_set_color_all( RGB_MAGENTA ); break;
//         default: break;
//     }
// }

// void set_layer_color(int layer) {
//     switch(layer) {
//         case 0: rgb_matrix_set_color_all( RGB_WHITE ); break;
//         case 1: rgb_matrix_set_color_all( RGB_RED ); break;
//         case 2: rgb_matrix_set_color_all( RGB_GREEN ); break;
//         case 3: rgb_matrix_set_color_all( RGB_BLUE ); break;
//         case 4: rgb_matrix_set_color_all( RGB_YELLOW ); break;
//         case 5: rgb_matrix_set_color_all( RGB_MAGENTA ); break;
//         case 6: rgb_matrix_set_color_all( RGB_TEAL ); break;
//         default:
//             if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
//                 rgb_matrix_set_color_all( RGB_GOLDENROD);
//             }
//     }
// }
uint8_t _layers[6][2][27] = {
    //    10: Space,  11: Lower, 12: Mouse                      13: ESC, 14: TAB, 15: SHFT
    //    20: Return, 21: Raise, 22: Mouse                      23: DEL, 24: Quote, 25: Return
    //    10 B  G  T  R  F  V  11 12 C  D  E  W  S  X  Z  A  Q  13 14 15 _  _  _  _  _  _
    //    20 N  H  Y  U  J  M  21 22 ,  K  I  O  L  .  /  ;  P  23 24 25 _  _  _  _  _  _
    // [_BASE] =
    {   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    },
    // [_LOWER]  =
    {   { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
    },
    // [_RAISE]  =
    {   { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
        { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }
    },
    // [_ADJUST] =
    {   { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
    },
    // [_MOUSE]  =
    {   { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
        { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }
    },
    // [_RGB]    =
    {   { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
        { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }
    }
};


// void set_layer_color(int layer) {
//     switch(layer) {
//         case 0: rgb_matrix_set_color_all( RGB_WHITE ); break;
//         case 1: rgb_matrix_set_color_all( RGB_RED ); break;
//         case 2: rgb_matrix_set_color_all( RGB_GREEN ); break;
//         case 3: rgb_matrix_set_color_all( RGB_BLUE ); break;
//         case 4: rgb_matrix_set_color_all( RGB_YELLOW ); break;
//         case 5: rgb_matrix_set_color_all( RGB_MAGENTA ); break;
//         case 6: rgb_matrix_set_color_all( RGB_TEAL ); break;
//         default:
//             if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
//                 rgb_matrix_set_color_all( RGB_GOLDENROD);
//             }
//     }
// }

#endif // RGB_MATRIX_ENABLE


/////////////////////////////////////////////////////////
//
//  TAP DANCE LOGIC
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
