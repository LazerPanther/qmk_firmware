#include QMK_KEYBOARD_H
#include "muse.h"

/* TapDance Aliases */
#define TD_LBRK TD(TD_BRACKETS_LEFT)
#define TD_RBRK TD(TD_BRACKETS_RIGHT)
#define TD_PLEQ TD(TD_PLUS_EQUALS)
#define TD_SCOL TD(TD_SEMICOLON_COLON)
#define TD_SLQU TD(TD_SLASH_QUESTION)
#define TD_SQDQ TD(TD_QUOTE_DOUBLEQUOTE)
#define TD_USMI TD(TD_UNDERSCORE_MINUS)

/* Sentinel value for invalid tap dance exit */
#define TAP_DANCE_NO_MATCH 64

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT
};

enum tapdance_keycodes {
    TD_BRACKETS_LEFT,
    TD_BRACKETS_RIGHT,
    TD_PLUS_EQUALS,
    TD_QUOTE_DOUBLEQUOTE,
    TD_SEMICOLON_COLON,
    TD_SLASH_QUESTION,
    TD_UNDERSCORE_MINUS,
};

typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD,
} t_tap_state;

typedef struct {
    t_tap_state left_brackets;
    t_tap_state right_brackets;
} t_tap;

t_tap_state get_tapdance_state(qk_tap_dance_state_t *state);

void td_brackets_left_finished(qk_tap_dance_state_t *state, void *user_data);
void td_brackets_left_reset(qk_tap_dance_state_t *state, void *user_data);
void td_brackets_right_finished(qk_tap_dance_state_t *state, void *user_data);
void td_brackets_right_reset(qk_tap_dance_state_t *state, void *user_data);

/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for left parenthesis, twice for left bracket, thrice for left brace */
    [TD_BRACKETS_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_left_finished, td_brackets_left_reset),
    /* Tap once for right parenthesis, twice for right bracket, thrice for right brace */
    [TD_BRACKETS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_brackets_right_finished, td_brackets_right_reset),
    /* Tap once for plus, twice for equals */
    [TD_PLUS_EQUALS] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_EQUAL),
    /* Tap once for single quote, twice for double quote */
    [TD_QUOTE_DOUBLEQUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
    /* Tap once for semicolon, twice for colon */
    [TD_SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
    /* Tap once for slash, twice for question mark */
    [TD_SLASH_QUESTION] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_QUESTION),
    /* Tap once for underscore, twice for minus */
    [TD_UNDERSCORE_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_UNDERSCORE, KC_MINUS),
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* qwerty
    * ,-----------------------------------------------------------------------------------.
    * | `    |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   | Del  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Tab  |  q   |  w   |  e   |  r   |  t   |  y   |  u   |  i   |  o   |  p   | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | C/Esc|  a   |  s   |  d   |  f   |  g   |  h   |  j   |  k   |  l   |  ;   | Enter|
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|  z   |  x   |  c   |  v   |  b   |  n   |  m   |  ,   |  .   |  /   |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Mouse| Ctrl |  Alt |  OS  |Lower |    Space    | Raise| Left | Down |  Up  | Right|
    * `-----------------------------------------------------------------------------------'
    */
	
	[_QWERTY] = LAYOUT_preonic_1x2uC(
		KC_GRV,         KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_DEL, 
		KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, 
		LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    TD_SCOL, KC_SFTENT, 
		OSM(MOD_LSFT),  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  TD_SLQU, TD_SQDQ, 
		TT(_MOUSE),     KC_LCTL, KC_LALT, KC_LGUI, LOWER,     KC_SPC,     RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	),

	/* Colemak */
	[_COLEMAK] = LAYOUT_preonic_1x2uC(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_DEL, KC_ESC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_SFTENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT, TT(_MOUSE), KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

	/* Dvorak */
	[_DVORAK] = LAYOUT_preonic_1x2uC(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_DEL, KC_ESC, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SFTENT, KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_SLSH, TT(_MOUSE), KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

    /* Lower
    * ,-----------------------------------------------------------------------------------.
    * | VMute| Prev |VDown |  VUp | Next | Play |      |      |      |      |      | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  !   |  @   |  #   |  $   |      |      |  -   |  +   |  {   |  }   | Del  |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      | MLeft| MDown|  MUp |MRight| CLeft|      |  _   |  =   |{ [ ( | ) ] }|  |   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |  %   |  ^   |  &   |  *   |      |      |  ~   |  <   |  >   |  \   |  "   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Home |PDown | PUp  | End  |
    * `-----------------------------------------------------------------------------------'
    */
	[_LOWER] = LAYOUT_preonic_1x2uC(
		KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, 
		KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_TRNS, KC_TRNS, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_DEL, 
		KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_TRNS, KC_UNDS, KC_EQL,  TD_LBRK, TD_RBRK, KC_PIPE, 
		KC_TRNS, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_TRNS, KC_TRNS, KC_TILD, KC_LT,   KC_GT,   KC_BSLS, KC_DQUO, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END
	),


    /* Raise
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |  7   |  8   |  9   |  +   | Del  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  1   |  2   |  3   |  4   |  5   |      |  4   |  5   |  6   |  -   | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  1   |  2   |  3   |  *   |RS/Ent|
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |      |  0   |  .   |  \   | Menu |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Left | Down |  Up  | Right|
    * `-----------------------------------------------------------------------------------'
    */
	[_RAISE] = LAYOUT_preonic_1x2uC(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_DEL, 
		KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_BSPC, 
		KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PAST, KC_SFTENT, 
		KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,   KC_NO,   KC_P0,   KC_PDOT, KC_PSLS, KC_APP, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	),

	/* Adjust (Lower + Raise) 
    * ,-----------------------------------------------------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  Esc | Reset| Debug|      |RGBTog|BLCycl|      |TERMOn|TERMOf|      |      | Del  |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |CAPSLK|      |MU_MOD| AU_ON|AU_OFF|RevAG |SwapAG| DF(0)| DF(1)| DF(2)|      |NumLck|
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |MUV_DE|MUV_IN| MU_ON|MU_OFF|MI_ON |MI_OFF|      | Brite|      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | BL_T |BL_DEC|BL_INC| BL_ST|
    * `-----------------------------------------------------------------------------------'
	*/
	[_ADJUST] = LAYOUT_preonic_1x2uC(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12, 
		KC_ESC,  RESET,   DEBUG,   KC_TRNS, RGB_TOG, BL_STEP, KC_TRNS, TERM_ON, TERM_OFF, KC_TRNS, KC_TRNS, KC_DEL, 
		KC_CAPS, KC_TRNS, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, DF(0),   DF(1),    DF(2),   KC_TRNS, KC_NLCK, 
		KC_TRNS, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  BACKLIT, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, BL_TOGG, BL_DEC,   BL_INC,  BL_STEP
	),

	/* MOUSE - Navigation / Movement 
    * ,-----------------------------------------------------------------------------------.
    * |MEHspc|  Q   |  W   |  E   |  R   |  F   |      |      |      |      |      |NumLck|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Tab  |LC(N4)|LC(N2)|LC(N8)|LC(N6)|  M1  |      |      |      |      |PScrn | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |C/Esc |MLeft |MDown | Mup  |MRight|  M1  |      |  M1  |LC(N2)|LC(N8)|  M1  |RS/Ent|
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |Shift |MWLeft|MWDown| MWUp |MWRight| M2  |      |  W   |  E   |  R   |  F   |MEHspc|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |MO(0) |             |TG(6) |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
	*/
	[_MOUSE] = LAYOUT_preonic_1x2uC(
		MEH_T(KC_SPC),  KC_Q,        KC_W,        KC_E,        KC_R,        KC_F,    KC_NO,   KC_NO,        KC_NO,       KC_NO,       KC_NO,   KC_NLCK, 
		KC_TAB,         LCTL(KC_P4), LCTL(KC_P2), LCTL(KC_P8), LCTL(KC_P6), KC_BTN1, KC_NO,   KC_NO,        KC_NO,       KC_NO,       KC_PSCR, KC_BSPC, 
		LCTL_T(KC_ESC), KC_MS_L,     KC_MS_D,     KC_MS_U,     KC_MS_R,     KC_BTN1, KC_NO,   KC_BTN1,      LCTL(KC_P2), LCTL(KC_P8), KC_BTN1, KC_SFTENT, 
		OSM(MOD_LSFT),  KC_WH_L,     KC_WH_D,     KC_WH_U,     KC_WH_R,     KC_BTN2, KC_NO,   KC_W,         KC_E,        KC_R,        KC_F,    MEH_T(KC_SPC), 
		KC_TRNS,        KC_TRNS,     KC_TRNS,     KC_TRNS,     MO(_QWERTY),     KC_TRNS,      TG(_MOUSE),   KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS
	)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgblight_step();
        #endif
        #ifdef __AVR__
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef __AVR__
          writePinHigh(E6);
        #endif
      }
      return false;
  }
  return true;
};


const rgblight_segment_t PROGMEM qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, 0, 0, 0});

const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_RED});

const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_GREEN});

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLUE});

const rgblight_segment_t PROGMEM mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 5, HSV_WHITE});

// Later layers take precedence.
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    qwerty_layer,
    lower_layer,
    raise_layer,
    adjust_layer,
    mouse_layer
);

/* bool mouseActive = false; */
/*  */
/* float tone_mouse_on[][2] = SONG(NUM_LOCK_OFF_SOUND); */

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    rgblight_set_layer_state(0, true);
}

/* void matrix_scan_user (void) { */
/*   uint8_t layer = biton32(layer_state); */
/*  */
/*   switch (layer) { */
/*     case _MOUSE: */
/*       if (!mouseActive) { */
/*         mouseActive = true; */
/*         PLAY_SONG(tone_mouse_on); */
/*       } */
/*       break; */
/*     default: */
/*       if (mouseActive) { */
/*         mouseActive = false; */
/*       } */
/*   } */
/* }; */

/* Global TapDance State */
static t_tap qk_tap_state = {
    .left_brackets  = 0,
    .right_brackets = 0,
};

t_tap_state get_tapdance_state(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) {
            return DOUBLE_TAP;
        } else {
            return DOUBLE_HOLD;
        }
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            return TRIPLE_TAP;
        } else {
            return TRIPLE_HOLD;
        }
    } else
        return TAP_DANCE_NO_MATCH;
}

void td_brackets_left_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_state.left_brackets = get_tapdance_state(state);
    switch (qk_tap_state.left_brackets) {
        case SINGLE_TAP:
            register_code16(KC_LEFT_PAREN);
            break;
        case DOUBLE_TAP:
            register_code(KC_LBRACKET);
            break;
        case TRIPLE_TAP:
            register_code16(KC_LEFT_CURLY_BRACE);
            break;
        default:
            break;
    }
}

void td_brackets_left_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (qk_tap_state.left_brackets) {
        case SINGLE_TAP:
            unregister_code16(KC_LEFT_PAREN);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_LBRACKET);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_LEFT_CURLY_BRACE);
            break;
        default:
            break;
    }
    qk_tap_state.left_brackets = 0;
}

void td_brackets_right_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_state.right_brackets = get_tapdance_state(state);
    switch (qk_tap_state.right_brackets) {
        case SINGLE_TAP:
            register_code16(KC_RIGHT_PAREN);
            break;
        case DOUBLE_TAP:
            register_code(KC_RBRACKET);
            break;
        case TRIPLE_TAP:
            register_code16(KC_RIGHT_CURLY_BRACE);
            break;
        default:
            break;
    }
}

void td_brackets_right_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (qk_tap_state.right_brackets) {
        case SINGLE_TAP:
            unregister_code16(KC_RIGHT_PAREN);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_RBRACKET);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_RIGHT_CURLY_BRACE);
            break;
        default:
            break;
    }
    qk_tap_state.right_brackets = 0;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

/* void matrix_scan_user(void) { */
/* #ifdef AUDIO_ENABLE */
/*     if (muse_mode) { */
/*         if (muse_counter == 0) { */
/*             uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()]; */
/*             if (muse_note != last_muse_note) { */
/*                 stop_note(compute_freq_for_midi_note(last_muse_note)); */
/*                 play_note(compute_freq_for_midi_note(muse_note), 0xF); */
/*                 last_muse_note = muse_note; */
/*             } */
/*         } */
/*         muse_counter = (muse_counter + 1) % muse_tempo; */
/*     } else { */
/*         if (muse_counter) { */
/*             stop_all_notes(); */
/*             muse_counter = 0; */
/*         } */
/*     } */
/* #endif */
/* } */

bool led_update_user(led_t led_state) {
    // Turn on RBG for capslock.
    rgblight_set_layer_state(4, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Set RBG layer according to active keymap layer.
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 1) && layer_state_cmp(state, 2));
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
