// preonic/rev3:jck-sf

#include QMK_KEYBOARD_H
#include "muse.h"
#include "eeprom.h"
//#include "music.h"
//#include "kaplan.h"
//#include "hebrew.h"
//#include "process_tap_dance.h"
//#include "quantum_keycodes.h"


// float capsOnSong[][2]                  = SONG(CAPS_ON);
// float capsOffSong[][2]                 = SONG(CAPS_OFF);

enum custom_keycodes {
    DUMMY = SAFE_RANGE,
    KC_TAP_MOD,
    KC_LSFT_CAPS,
    KC_LDAQ,
    KC_RDAQ,
    RGB_SLD,
    KC_CMDALT,
    KC_TOGGLE,
};

/* clang-format off */

//#define TAPPING_TERM 375

#define LDAQ UC(0x00AB)
#define RDAQ UC(0x00BB)

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

void keyboard_post_init_user(void);

uint8_t cur_dance(qk_tap_dance_state_t *state);

void l_bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void l_bracket_reset(qk_tap_dance_state_t *state, void *user_data);
void r_bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void r_bracket_reset(qk_tap_dance_state_t *state, void *user_data);
void shift_lock_finished(qk_tap_dance_state_t *state, void *user_data);
void shift_lock_reset(qk_tap_dance_state_t *state, void *user_data);

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


// keymap ---------------------------------------------------------------------

enum preonic_layers {
	_BASE = 0,
	_LOWER,
	_RAISE,
    _MOUSE,
	_ADJUST,
};

#define TD_LBRACKET TD(TD_BRACKETS_LEFT)
#define TD_RBRACKET TD(TD_BRACKETS_RIGHT)
//#define SHFT_LOCK TD(TD_LSHIFT_LOCK)

#define KC_TMOD KC_TAP_MOD
#define KC_TMOD_TAP QK_RSFT
#define KC_TMOD_HOLD KC_ENTER
#define KC_TMOD_DTAP KC_ENTER

#define OSM_LSFT OSM(MOD_LSFT)
#define _CAPSLCK KC_LSFT_CAPS

#define MUTE   KC_AUDIO_MUTE
#define VOLUP  KC_AUDIO_VOL_UP
#define VOLDN  KC_AUDIO_VOL_DOWN

#define M_PLAY1    DYN_MACRO_PLAY1
#define M_PLAY2    DYN_MACRO_PLAY2
#define M_REC1     DYN_REC_START1
#define M_REC2     DYN_REC_START2
#define M_RSTOP    DYN_REC_STOP

//#define RGB_TEST   RGB_MODE_RGBTEST
//#define RGB_TLC    TOGGLE_LAYER_COLOR

#define MS_WUP     KC_MS_WH_UP
#define MS_WLEFT   KC_MS_WH_LEFT
#define MS_WRGHT   KC_MS_WH_RIGHT
#define MS_WDOWN   KC_MS_WH_DOWN

#define MS_BTN1    KC_MS_BTN1
#define MS_BTN2    KC_MS_BTN2

#define MS_UP      KC_MS_UP
#define MS_LEFT    KC_MS_LEFT
#define MS_RIGHT   KC_MS_RIGHT
#define MS_DOWN    KC_MS_DOWN

#define MS_AC_0    KC_MS_ACCEL0
#define MS_AC_1    KC_MS_ACCEL1
#define MS_AC_2    KC_MS_ACCEL2

#define _PIPE       S(KC_PIPE)

#define MUTE   KC_AUDIO_MUTE
#define VOLUP  KC_AUDIO_VOL_UP
#define VOLDN  KC_AUDIO_VOL_DOWN

//#define RGB_TEST RGB_MODE_RGBTEST
//#define RGB_TLC TOGGLE_LAYER_COLOR

#define BASE   TO(_BASE)
#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define MOUSE  MO(_MOUSE)
#define ADJUST MO(_ADJUST)

#define _LDAQ LALT(KC_BSLASH)
#define _RDAQ LALT(S(KC_BSLASH))
#define KC_BSLSH  LSFT(KC_SLASH)

// #define MS_UP       KC_MS_UP
// #define MS_DOWN     KC_MS_DOWN
// #define MS_LEFT     KC_MS_LEFT
// #define MS_RIGHT    KC_MS_RIGHT
// #define MS_BTN1     KC_MS_BTN1
// #define MS_BTN2     KC_MS_BTN2
// #define MS_BTN3     KC_MS_BTN3
// #define MS_W_UP     KC_MS_WH_UP
// #define MS_W_DOWN   KC_MS_WH_DOWN
// #define MS_W_LEFT   KC_MS_WH_LEFT
// #define MS_W_RIGHT  KC_MS_WH_RIGHT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_preonic_1x2uC (
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       TD(TD_BSLASH_PIPE),       // KC_BSLASH,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    ADJUST,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCOLON,  TD(TD_QUOTE_DOUBLEQUOTE), // KC_QUOT,
    OSM_LSFT,   KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_TMOD,
    KC_HYPR,    KC_LCTL,    KC_LALT,    KC_LGUI,    LOWER,      KC_SPC,                 RAISE,      MOUSE,      KC_LEFT,    KC_DOWN,    KC_RIGHT
    ),

  [_MOUSE] = LAYOUT_preonic_1x2uC(   // mouse
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    MS_AC_2,
    KC_HYPR,    _______,    MS_BTN1,    MS_WUP,     MS_BTN2,    _______,    _______,    MS_BTN1,    MS_UP,      MS_BTN2,    _______,    MS_AC_1,
    _______,    _______,    MS_WLEFT,   MS_WDOWN,   MS_WRGHT,   _______,    _______,    MS_LEFT,    MS_DOWN,    MS_RIGHT,   _______,    MS_AC_0,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_X,       KC_C,       KC_V,       KC_UP,      MS_BTN2,
    _______,    KC_HYPR,    KC_MEH,     _______,    _______,    _______,                _______,    MS_BTN1,    KC_LEFT,    KC_DOWN,    KC_RIGHT
  ),


  [_LOWER] = LAYOUT_preonic_1x2uC (
    KC_GRAVE,   KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
    M_PLAY1,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_COMMA,   KC_DOT,     _______,    TD_LBRACKET,
    _CAPSLCK,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_PLUS,    KC_MINUS,   KC_EQUAL,   _______,
    M_REC1,     _______,    _______,    _______,    _______,    KC_VOLD,                KC_0,       KC_DOT,     KC_PLUS,    KC_MINS,    KC_EQUAL

    ),

  [_RAISE] = LAYOUT_preonic_1x2uC (
    _______,    KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     _______,    _______,
    KC_TILDE,   S(KC_1),    S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0),    KC_BSPACE,
    M_PLAY2,    KC_Z,       KC_X,       KC_C,       _______,    _______,    _______,    _______,    _______,    _______,    _RDAQ,     TD_RBRACKET,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_UNDS,    _PIPE,      KC_PGUP,    _______,
    KC_MEH,     KC_RCTL,    KC_RALT,    KC_RGUI,    _______,    KC_VOLU,                _______,    MS_BTN1,    KC_HOME,    KC_PGDN,    KC_END
    ),

  [_ADJUST] = LAYOUT_preonic_1x2uC (
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    RESET,      KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     RESET,
    _______,    KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     _______,    _______,      // KC_F20 not available on macOS
    KC_CAPS,    _______,    _______,    _______,    _______,    TO(5),      _______,    _______,    _______,    _______,    KC_TOGGLE,  _______,
    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,    M_REC1,     M_REC2,     M_RSTOP
    )
};

//  ----------

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//#define short_tap (delay(tm_t0, record->event.time) <= TAPPING_TERM)
// void post_process_record_user(uint16_t keycode, keyrecord_t *record) { }

typedef struct {
    bool active;        // true if tap-dance in progress
    uint16_t kc;        // new keycode
    uint32_t timer32;   // milliseconds
} _tap_mod_t;

typedef struct {
    uint16_t key;
    uint16_t tap;
    uint16_t hold;
    uint16_t dtap;
} _tm_actions;

// static _tm_actions tma[] = {
//     [0] = { .key = KC_TMOD, .tap = KC_TMOD_TAP, .hold = KC_TMOD_HOLD, .dtap = KC_TMOD_HOLD },
//     [1] = { .key = KC_CAPS, .tap = KC_LSFT,     .hold = KC_LSFT,      .dtap = KC_CAPSLOCK},
// };

// static uint16_t _tm_actions_cnt = 2;

static bool _caps_lock = false;

void keyboard_post_init_user(void) {
    _caps_lock = false;
    // rgb_matrix_enable();
}

uint16_t delay(uint16_t t0, uint16_t t1) {
    return (t1 > t0) ? t1 - t0 : t0 - t1;
}

bool long_tap(uint32_t timer32) {
    return (timer_elapsed32(timer32) > TAPPING_TERM);
}

void process_capslock(void) {
    if (_caps_lock == true) {
        unregister_code16(KC_LSFT);
        _caps_lock = false;
    } else {
        register_code16(KC_LSFT);
        _caps_lock = true;
    }
}



void send_keycode(uint16_t kc) {
    register_code16(kc);
    wait_ms(1);
    unregister_code16(kc);
}

static _tap_mod_t tm = { .active = false, .kc = 0, .timer32 = 0 } ;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

//   if (keycode == RGB_SLD && record->event.pressed) {
//      rgblight_mode(1);
//      return false;
//  }
    if (keycode == KC_LSFT_CAPS && record->event.pressed) {
        process_capslock();
        return false;
    }
    if (!tm.active) {
        if (record->event.pressed) {
            if (keycode == KC_TMOD) {            // a new tap-mod has started
                tm.timer32 = timer_read32();
                tm.active = true;
                return false;
            }
        }
    } else {
        if (record->event.pressed) {
            // key-down
           switch (keycode) {
                case KC_TAP_MOD:
                   tm.kc = KC_TMOD_DTAP; break;
                default:
                   tm.kc = (long_tap(tm.timer32) == true) ? KC_TMOD_HOLD : (KC_TMOD_TAP | keycode) ;
           }
            send_keycode(tm.kc);
            tm.active = false;
            return false;
        } else {
            //key-up
           if (keycode == KC_TAP_MOD) {
                if (long_tap(tm.timer32) == true) {
                    tm.kc = KC_TMOD_HOLD;
                    send_keycode(tm.kc);
                    tm.active = false;
                    return false;
               }
            }
        }
    }
    return true;
}


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


/*
    ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)

    Tap Dance Definitions
       first function called on each key-down (tap),
         second fn called when dance finishess (see below),
           third fn called when dance is reset.

     The dance finishes when the tapping_term expires,
     or a different key is pressed and the dance is interrupted (state->interrupted)

     The dance is reset after the dance is finished (called after dance-finishes)
      OR when state->finished is set during the last tap (e.g. in case you want to skip 2nd fn call)

     dance-finished can be skipped, but dance-reset will always be called.
*/
/*
     register_code(<kc>) .... sends the KEY-DOWN event to the computer ... or D()
     unregister_code(<kc>) .. sends the KEY-UP event to the computer ..... or U()


    Why timer32?
     ... in theory, KC_TMOD could be held down for more than 65 seconds,
     so we need a 32 bit timer to be sure we handle an excessive hold interval.

    qmk_firmware/quantum/quantum_keycodes.h:

             enum quantum_keycodes {
               ...
               QK_LSFT = 0x0100
               QK_RSFT = 0x1200
               ...
             }

             #define OSM(mod) (QK_ONE_SHOT_MOD | ((mod)&0xFF))

    qmk_firmware/quantum/process_keycode/process_key_lock.c

            bool process_key_lock(uint16_t *keycode, keyrecord_t *record);



    qmk_firmware/quantum/process_keycode/process_tap_dance.h:

             typedef struct {
                 uint8_t  count;
                 uint8_t  oneshot_mods;
                 uint8_t  weak_mods;
                 uint16_t keycode;
                 uint16_t interrupting_keycode;
                 uint16_t timer;
                 bool     interrupted;
                 bool     pressed;
                 bool     finished;
             } qk_tap_dance_state_t;
*/
