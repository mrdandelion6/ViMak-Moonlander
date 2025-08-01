#include "action.h"
#include "action_layer.h"
#include "keycodes.h"
#include "matrix.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "send_string_keycodes.h"
#include "timer.h"
#include <stdint.h>
#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE
#define HOLD_ON_OTHER_KEY_PRESS

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  WIN_LEFT,
  WIN_RIGHT,
  WIN_UP,
  WIN_DOWN,
  FORWARD_WORD,
  BACKWARD_WORD,
  RECORD,
  CLIP,
  FUZZY_FIND,
  SNIP_SCREEN,
  LOCK_SYSTEM,
  TERMINAL,
  CLAUDE,
  FILES,
  SPOTIFY,
  BROWSER,
  DISCORD,
  ESC_MACRO,
  ALT_F4,
  VIM_MODE,
};

enum tap_dance_codes {
  MEDIA,
  VOLUME,
  NUM_TOGGLE,
  SYM_APP_TOGGLE,
  SHIFT_CAPS,
  TD_COUNT,
};

enum LAYERS {
  CMK,
  QTY,
  SYM,
  NUM,
  VIM,
  APP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // colemak layout
  [CMK] = LAYOUT_moonlander(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,
    KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_F13,         KC_F14,

    KC_LGUI,        KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           TO(QTY),
    KC_TRANSPARENT, KC_J,           KC_L,           KC_U,           KC_Y,           KC_MINUS,       KC_RGUI,

    KC_LEFT_SHIFT,  KC_A,           KC_R,           KC_S,           KC_T,           KC_G,           TD(NUM_TOGGLE),
    TD(NUM_TOGGLE), KC_K,           KC_N,           KC_E,           KC_I,           KC_O,           KC_QUOTE,

    KC_LEFT_CTRL,   KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,
    KC_M,           KC_H,           KC_COMMA,       KC_DOT,         KC_BSLS,        KC_RIGHT_CTRL,

    KC_LEFT_ALT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_SCLN,        KC_DELETE,
    TD(SYM_APP_TOGGLE), // left thumb

    ESC_MACRO, // right thumb
    KC_SLASH,       KC_COLN,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_SPACE,       KC_BSPC,        LT(VIM,KC_TAB),
    KC_RIGHT_ALT,   TD(SHIFT_CAPS), KC_ENTER
  ),

  // qwerty layout
  [QTY] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           TO(CMK),
    KC_TRANSPARENT, KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_TRANSPARENT,

    KC_TRANSPARENT, KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_TRANSPARENT,

    KC_TRANSPARENT, KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,
    KC_N,           KC_M,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,

    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // special character layout
  [SYM] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_AT,          KC_PERC,        KC_HASH,        KC_AMPR,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LABK,        KC_MINUS,       KC_PLUS,        KC_RABK,        KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TILD,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_PIPE,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_DQUO,        KC_LCBR,        KC_RCBR,        KC_UNDS,        KC_QUES,        KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_EXLM,        KC_CIRC,        KC_EQUAL,       KC_TRANSPARENT,
    KC_ASTR,        KC_LBRC,        KC_RBRC,        KC_GRAVE,       KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(CMK),

    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // numpad + navigation layout
  [NUM] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(MEDIA),      TD(VOLUME),     ALT_F4,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_DOT,         KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, WIN_LEFT,       WIN_UP,         WIN_DOWN,       WIN_RIGHT,      TO(CMK),
    TO(CMK),        KC_0,           KC_4,           KC_5,           KC_6,           KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_COMMA,       KC_1,           KC_2,           KC_3,           KC_PLUS,        KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,

    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // vim layout
  [VIM] = LAYOUT_moonlander( // all other keys are disabled
    KC_ESCAPE, KC_NO,        KC_NO,        KC_NO, KC_NO,    KC_NO,         KC_NO,
    KC_NO,     KC_NO,        KC_NO,        KC_NO, KC_NO,    KC_NO,         KC_NO,

    KC_NO,     KC_NO,        FORWARD_WORD, KC_NO, KC_NO,    BACKWARD_WORD, KC_NO,
    KC_NO,     FORWARD_WORD, VIM_MODE,     KC_NO, KC_NO,    KC_NO,         KC_NO,

    KC_NO,     KC_NO,        KC_NO,        KC_NO, KC_NO,    KC_NO,         KC_NO,
    KC_NO,     KC_LEFT,      KC_DOWN,      KC_UP, KC_RIGHT, KC_NO,         KC_NO,

    KC_NO,     KC_NO,        KC_NO,        KC_NO, KC_NO,    KC_NO,
    KC_NO,     KC_NO,        KC_NO,        KC_NO, KC_NO,    KC_NO,

    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,

    VIM_MODE,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

    KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO
  ),

  // app + system shortcuts
  [APP] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    AU_TOGG,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RECORD,         CLIP,
    KC_TRANSPARENT, KC_TRANSPARENT, DISCORD,        FILES,          SPOTIFY,        KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, FUZZY_FIND,     SNIP_SCREEN,    LOCK_SYSTEM,
    KC_TRANSPARENT, KC_TRANSPARENT, TERMINAL,       CLAUDE,         BROWSER,        KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,

    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
  [1] = { {211,229,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

  [2] = { {0,0,0}, {211,229,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

  [3] = { {0,0,0}, {0,0,0}, {211,229,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

  [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {211,229,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

  [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {211,229,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
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
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

// find an existing window running "name" app or launch new one if none found.
#define APP_LAUNCH_TIME_PRE 50
#define APP_LAUNCH_TIME_POST 300
void launch_app(char* name) {
  SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
  wait_ms(APP_LAUNCH_TIME_PRE);
  send_string(name);
  wait_ms(APP_LAUNCH_TIME_POST);
  SEND_STRING(SS_TAP(X_ENTER));
}

/**
 * @brief True when we swap into VIM layer fully , not just when LT is held ,
 * otherwise false. Set in process_record_user().
 */
static bool toggled_in_vim = false;

/**
 * @brief True when the FORWARD_WORD macro on the VIM layer is held down. Set in
 * process_record_user() and used in matrix_scan_user() to repeatedly send the
 * forward movement key stroke: CTRL + RIGHT ARROW.
 */
static bool forward_word_held = false;

/// @brief Same as forward_world_held but for BACKWORD_WORD macro.
static bool backward_word_held = false;

/**
 * @brief Timer for the FORWARD_WORD macro which is used to determine when to
 * send the next forward movement key stroke in matrix_scan_user() while holding
 * the macro down.
 */
static uint16_t forward_word_timer = 0;

/// @brief Same as forward_world_held but for BACKWORD_WORD macro.
static uint16_t backward_word_timer = 0;

/**
 * @brief How often (in milliseconds) to send a macro key while holding it down.
 * Used for macros such as the ones on the VIM layer like FORWARD_WORD.
 */
#define REPEAT_HOLD_EVERY 150

/**
 * @brief Called every matrix scan cycle (~1000 times per second) for custom
 * user logic. Use timers to throttle expensive operations - avoid blocking
 * code.
 */
void matrix_scan_user(void) {
  if (forward_word_held && timer_elapsed(forward_word_timer) > REPEAT_HOLD_EVERY) {
    SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
    forward_word_timer = timer_read();
  }
  if (backward_word_held && timer_elapsed(backward_word_timer) > REPEAT_HOLD_EVERY) {
    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
    forward_word_timer = timer_read();
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // general
    case ESC_MACRO:
      if (record->event.pressed) {
        // disable caps whenever this button is pressed
        if (host_keyboard_led_state().caps_lock) {
          tap_code(KC_CAPS);
        }
        tap_code16(KC_ESCAPE);
      }
      return false;

    // window manipulation
    case WIN_LEFT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
      }
      return false;
    case WIN_RIGHT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
      }
      return false;
    case WIN_UP:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_UP)));
      }
      return false;
    case WIN_DOWN:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
      }
      return false;
    case ALT_F4:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));
      }
      return false;

    // vim
    case VIM_MODE:
      if (record->event.pressed) {
        if (get_highest_layer(layer_state) == VIM && toggled_in_vim) { // toggle back to CMK
          toggled_in_vim = false;
          layer_move(CMK);
        } else { // lock into VIM mode
          toggled_in_vim = true;
          layer_move(VIM);
        }
      }
      return false;
    case LT(VIM,KC_TAB): // when letting go of the temp VIM key
      if (!record->event.pressed) {
        if (toggled_in_vim) {
          return false;
        }
      }
      break;

    case FORWARD_WORD:
      if (record->event.pressed) {
        backward_word_held = false;
        forward_word_held = true;
        forward_word_timer = timer_read();
        SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
      } else {
        forward_word_held = false;
      }
      return false;
    case BACKWARD_WORD:
      if (record->event.pressed) {
        forward_word_held = false;
        backward_word_held = true;
        backward_word_timer = timer_read();
        SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
      } else {
        backward_word_held = false;
      }
      return false;

    // screen tools
    case RECORD:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_F9)));
      }
      return false;
    case CLIP:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_F10)));
      }
      return false;
    case SNIP_SCREEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_S))));
      }
      return false;

    // system utils
    case FUZZY_FIND:
      if (record->event.pressed) {
        // alt + space: powertoys on windows or krunner on arch kde
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
      }
      return false;
    case LOCK_SYSTEM:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_L)));
      }
      return false;

    // launch apps
    case TERMINAL:
      // open a NEW terminal
      if (record->event.pressed) {
        switch (detected_host_os()) {
          case OS_WINDOWS:
            launch_app("wezterm");
            break;
          case OS_LINUX:
            // ctrl + alt + t
            SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_T))));
            break;
          default:
            break;
        }
      }
      return false;
    case CLAUDE:
      // open EXISTING claude session. if no existing , launch new one
      if (record->event.pressed) {
        launch_app("claude");
      }
      return false;
    case FILES:
      // open EXISTING file explorer. if no existing , launch new one
      if (record->event.pressed) {
        launch_app("file explorer");
      }
      return false;
    case SPOTIFY:
      // open EXISTING spotify. if no existing , launch new one
      if (record->event.pressed) {
        launch_app("spotify");
      }
      return false;
    case BROWSER:
      // open EXISTING browser. if no existing , launch new one
      if (record->event.pressed) {
        switch (detected_host_os()) {
          case OS_LINUX:
            launch_app("falkon");
            break;
          case OS_WINDOWS:
            launch_app("chrome");
            break;
          default:
            break;
        }
      }
      return false;
    case DISCORD:
      // open EXISTING discord. if no existing , launch new one
      if (record->event.pressed) {
        launch_app("discord");
      }
      return false;

    // other
    case RGB_SLD:
      if (rawhid_state.rgb_control) {
        return false;
      }
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  MORE_TAPS
};

/**
 * @brief This is a very important global array that keeps track of the dance
 * states for difference tap dances. This is needed particularly for when we
 * have a *_td_reset function that needs to remember what step was found in the
 * corresponding *_td_fin function.
 */
static uint8_t dance_states[TD_COUNT];

// tweak this as you want , it helps to do some experimentation with uprintf
#define MIN_HOLD_TIME 130
static uint16_t td_press_timer = 0;
static bool td_timer_active = false;

/**
 * @brief This function processes tap dance states and how they should be
 * interpreted as.
 *
 * Normally , interrupted presses are counted as holds by the HOLD_ON_KEY_PRESS
 * macro. However , when td_timer_active is true , this function may count
 * interrupted presses as just a tap if the interrupted key was not held down
 * for long enough (MIN_HOLD_TIME). This is only when td_timer_active is true ,
 * as that is the case for tap dances where I find myself typing too fast and
 * unintentionally causing an app to launch. For example , pressing pressing SYM
 * and immediately pressing { before SYM releases , triggering an accidental app
 * launch for terminal , when I just meant to go to previous paragraph in Vim.
 */
uint8_t dance_step(tap_dance_state_t *state) {
  if (state->count == 1) {

    if (!state->pressed) {
      td_timer_active = false;
      return SINGLE_TAP;
    }

    // for timed dances , check if key was held for long enough , otherwise tap
    if (state->interrupted && td_timer_active) {

        uint16_t held_time = timer_elapsed(td_press_timer);
        td_timer_active = false;

        if (held_time < MIN_HOLD_TIME) {
          return SINGLE_TAP;
        }

    }

    // either have an uninterrupted hold , or interrupted late enough
    return SINGLE_HOLD;
  }

  // move this into other counts if we ever want to check time for them
  td_timer_active = false;

  if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }

  if (state->count == 3) return TRIPLE_TAP;
  return MORE_TAPS;
}

void media_finished(tap_dance_state_t *state, void *user_data) {
  dance_states[MEDIA] = dance_step(state);
  switch (dance_states[MEDIA]) {

    // play or pause
    case SINGLE_TAP: tap_code16(KC_MPLY); break;

    // next in track
    case DOUBLE_TAP: tap_code16(KC_MNXT); break;

    // previous in track
    case TRIPLE_TAP: tap_code16(KC_MPRV); break;
    default: break;
  }
}

void volume_td_fin(tap_dance_state_t *state, void *user_data) {
  dance_states[VOLUME] = dance_step(state);
  switch (dance_states[VOLUME]) {

    // volume up
    case SINGLE_TAP: tap_code16(KC_VOLU); break;
    case SINGLE_HOLD: register_code16(KC_VOLU); break;

    // volume down
    case DOUBLE_HOLD: register_code16(KC_VOLD); break;

    // mute
    case DOUBLE_TAP: tap_code16(KC_MUTE); break;
    default: break;
  }
}

void volume_td_reset(tap_dance_state_t *state, void* user_data) {
  switch (dance_states[VOLUME]) {
    case SINGLE_HOLD: unregister_code16(KC_VOLU); break;
    case DOUBLE_HOLD: unregister_code16(KC_VOLD); break;
    default: break;
  }
}

/// @brief The previous layer we were on.
static uint8_t prev_layer;

/**
 * @brief This function acts as a wrapper around layer_move() while also keeping
 * track of the layer we are switching away from.
 *
 * Called by *_layer_td_fin functions.
 */
void layer_move_tracked(int layer) {
  prev_layer = get_highest_layer(layer_state);
  layer_move(layer);
}

void num_layer_td_fin(tap_dance_state_t *state, void* user_data) {
  dance_states[NUM_TOGGLE] = dance_step(state);
  layer_move_tracked(NUM);
}

void sym_app_layer_td_fin(tap_dance_state_t *state, void* user_data) {
  dance_states[SYM_APP_TOGGLE] = dance_step(state);
  switch (dance_states[SYM_APP_TOGGLE]) {
    case SINGLE_TAP: layer_move_tracked(SYM); break;
    case SINGLE_HOLD: layer_move_tracked(APP); break;
    default: break;
  }
}

/**
 * @brief Simple tap dance that sends CAPS if key pressed once , or holds down
 * SHIFT otherewise. Interrupts immediately trigger hold (no td_timer).
 */
void shift_caps_td_fin(tap_dance_state_t *state, void* user_data) {
  dance_states[SHIFT_CAPS] = dance_step(state);
  switch (dance_states[SHIFT_CAPS]) {
    case SINGLE_TAP:
      tap_code16(KC_CAPS);
      break;
    case SINGLE_HOLD:
      register_code16(KC_LEFT_SHIFT);
      break;
    default:
      break;
  }
}

/**
 * @brief This function swaps back to prev_layer if the stored tap dance step
 * was a single hold.
 *
 * Called by *_layer_td_reset functions.
 */
void hold_layer_reset(uint8_t step) {
  if (step == SINGLE_HOLD) {
    uint8_t temp = get_highest_layer(layer_state);
    layer_move(prev_layer);
    prev_layer = temp;
  }
}

void num_layer_reset(tap_dance_state_t *state, void* user_data) {
  hold_layer_reset(dance_states[NUM_TOGGLE]);
}

void sym_app_layer_td_reset(tap_dance_state_t *state, void* user_data) {
  // if we swapped to VIM layer while holding SYM key , don't swap back to CMK
  if (get_highest_layer(layer_state) != VIM) {
    hold_layer_reset(dance_states[SYM_APP_TOGGLE]);
  }
}

void shift_caps_td_reset(tap_dance_state_t *state, void* user_data) {
  if (dance_states[SHIFT_CAPS] == SINGLE_HOLD) {
    unregister_code16(KC_LEFT_SHIFT);
  }
}

/**
 * @brief This function starts a timer for tap dances which can be used later
 * to change whether a hold or tap was triggered in the dance_step() function.
 */
void time_td(tap_dance_state_t *state, void* user_data) {
  // start a timer if the state count is 1
  if (state->count == 1 && state->pressed) {
    td_timer_active = true;
    td_press_timer = timer_read();
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [MEDIA] = ACTION_TAP_DANCE_FN(media_finished),
  [VOLUME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, volume_td_fin, volume_td_reset),
  [NUM_TOGGLE] = ACTION_TAP_DANCE_FN_ADVANCED(time_td, num_layer_td_fin, num_layer_reset),
  [SYM_APP_TOGGLE] = ACTION_TAP_DANCE_FN_ADVANCED(time_td, sym_app_layer_td_fin, sym_app_layer_td_reset),
  [SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_caps_td_fin, shift_caps_td_reset)
};
