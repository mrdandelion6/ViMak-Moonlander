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
  ESC_VIM,
  ESC_VIM,
};

enum tap_dance_codes {
  MEDIA,
  VOLUME,
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

    KC_TRANSPARENT, KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           TO(QTY),
    KC_TRANSPARENT, KC_J,           KC_L,           KC_U,           KC_Y,           KC_MINUS,       KC_TRANSPARENT,

    KC_LEFT_SHIFT,  KC_A,           KC_R,           KC_S,           KC_T,           KC_G,           TD(NUM_TOGGLE),
    TD(NUM_TOGGLE), KC_K,           KC_N,           KC_E,           KC_I,           KC_O,           KC_QUOTE,

    KC_LEFT_CTRL,   KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,
    KC_M,           KC_H,           KC_COMMA,       KC_DOT,         KC_BSLS,        KC_RIGHT_CTRL,

    KC_LEFT_ALT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_SCLN,        KC_DELETE,
    TD(SYM_APP_TOGGLE), // left thumb

    ESC_MACRO, // right thumb
    KC_SLASH,       KC_COLN,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_SPACE,       KC_BSPC,               LT(VIM,KC_TAB),
    KC_RIGHT_ALT,   MT(MOD_RSFT, KC_CAPS), KC_ENTER
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

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(MEDIA),      TD(VOLUME),     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_UNDS,        KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, WIN_LEFT,       WIN_UP,         WIN_DOWN,       WIN_RIGHT,      TO(CMK),
    TO(CMK),        KC_0,           KC_4,           KC_5,           KC_6,           KC_COMMA,       KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_PLUS,        KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,

    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // vim layout
  [VIM] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_ESCAPE,      KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT,  FORWARD_WORD,   KC_TRANSPARENT, KC_TRANSPARENT, BACKWARD_WORD,  KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT,  TO(CMK),        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LEFT,         KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_END,          KC_PGDN,        KC_PAGE_UP,     KC_HOME,        KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,

    TO(VIM),
    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
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
void launch_app(char* name) {
  SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
  wait_ms(100);
  send_string(name);
  SEND_STRING(SS_TAP(X_ENTER));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    // layer swapping
    case TO_NUM:
      if (record->event.pressed) {
        layer_move(NUM);
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

    // vim
    case COPY:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
      }
      return false;
    case PASTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
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
            SEND_STRING(SS_TAP(X_LGUI));
            wait_ms(100);
            SEND_STRING("wezterm" SS_TAP(X_ENTER));
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
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        wait_ms(100);
        SEND_STRING("spotify" SS_TAP(X_ENTER));
      }
      return false;
    case DISCORD:
      // open EXISTING discord. if no existing , launch new one
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
        wait_ms(100);
        SEND_STRING("discord" SS_TAP(X_ENTER));
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

uint8_t dance_step(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  } else if (state->count == 3) return TRIPLE_TAP;
  return MORE_TAPS;
}

void esc_vim_finished(tap_dance_state_t *state, void *user_data) {

   // disable caps whenver this button is pressed
  if (host_keyboard_led_state().caps_lock) {
    tap_code(KC_CAPS);
  }

  uint8_t step = dance_step(state);
  switch (step) {
    // escape
    case SINGLE_TAP: tap_code16(KC_ESCAPE); break;
    case SINGLE_HOLD: tap_code16(KC_ESCAPE); break;

    // vim mode
    case DOUBLE_TAP: layer_move(VIM); break;
    case DOUBLE_HOLD: layer_move(VIM); break;
  }

}

void media_finished(tap_dance_state_t *state, void *user_data) {
  uint8_t step = dance_step(state);
  switch (step) {

    // play or pause
    case SINGLE_TAP: tap_code16(KC_MPLY); break;

    // next in track
    case DOUBLE_TAP: tap_code16(KC_MNXT); break;

    // previous in track
    case TRIPLE_TAP: tap_code16(KC_MPRV); break;
    default: break;
  }
}

void volume_finished(tap_dance_state_t *state, void *user_data) {
  uint8_t step = dance_step(state);
  switch (step) {

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

void volume_reset(tap_dance_state_t *state, void* user_data) {
  uint8_t step = dance_step(state);
  switch (step) {
    case SINGLE_HOLD: unregister_code16(KC_VOLU); break;
    case DOUBLE_HOLD: unregister_code16(KC_VOLD); break;
    default: break;
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [ESC_VIM] = ACTION_TAP_DANCE_FN(esc_vim_finished),
  [MEDIA] = ACTION_TAP_DANCE_FN(media_finished),
  [VOLUME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, volume_finished, volume_reset),
};
