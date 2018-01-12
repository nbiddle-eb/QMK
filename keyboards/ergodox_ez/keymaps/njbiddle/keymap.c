#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  SHRUG = SAFE_RANGE, // can always be here
  FLIP,
  THINK,
  EPRM,
  VRSN,
  RGB_SLD
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case SHRUG:
                SEND_STRING("¯\_(ツ)_/¯");
                return false; break;
            case FLIP:
                SEND_STRING(SS_LCTRL("(╯°□°）╯︵ ┻━┻"));
                return false; break;
            case THINK:
                SEND_STRING(SS_LCTRL("U+1F914"));
                return false; break;
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = {
      {SHRUG, FLIP, THINK}
    }

/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |   1  |   2  |   3  |   4  |   5  |  [   |           |  ]   |   6  |   7  |   8  |   9  |   0  |  -_    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  `   |           |  =   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '"   |
 * |--------+------+------+------+------+------|bright|           |bright|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |  up  |           | down |   N  |   M  |   ,  |   .  |  /   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |:flip:|:thnk:|CapsLo| Opti | Cmd  |                                       | left |  up  | down | right| :shrug:|
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ~L1  | mute |       | Pause|   ~L2  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Volup|       |  Nxt |        |      |
 *                                 |Backsp|delete|------|       |------|  Enter |Space |
 *                                 | ace  |      |Voldwn|       | Prev |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LBRC,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_GRAVE,
        KC_LCTRL,       KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_F14,
        FLIP,          THINK,        KC_CAPSLOCK,  KC_LALT, KC_LGUI,
                                                     TG(SYMB), KC_MUTE,
                                                               KC_VOLU,
                                                KC_BSPC,KC_DEL,KC_VOLD,
        // right hand
             KC_RBRC,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_EQL,      KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          KC_QUOT,
             KC_F15,      KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,
                                  KC_LEFT, KC_UP,KC_DOWN,KC_RIGHT,          SHRUG,
             KC_MEDIA_PLAY_PAUSE, TG(MDIA),
             KC_MFFD,
             KC_MRWD, KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |esc      |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |  tab    |   !  |   @  |   {  |   }  |   |  |      |           |   =  |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  cntrl  |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |   +  |------+------+------+------+------+--------|
 * |   Lshft |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  | Rshift |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      | caps | opti | cmd  |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ~L0  | mute |       |Pause | ~L2  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | back |delete|volup |       | next |enter |space |
 *                                 | space|      |------|       |------|      |      |
 *                                 |      |      |voldwn|       | prev |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_ESC,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_NO,
       KC_TAB,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_NO,
       KC_LCTRL,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_LSFT,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_NO,
          KC_NO,KC_NO,KC_CAPSLOCK,KC_LALT,KC_LGUI,
                                       TG(BASE),KC_MUTE,
                                               KC_VOLU,
                               KC_BSPC,KC_DEL,KC_VOLD,
       // right hand
       KC_NO, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_EQL, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_NO,
       KC_PLUS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_RSFT,
                         KC_NO,KC_DOT,  KC_0,    KC_EQL,  KC_NO,
       KC_MEDIA_PLAY_PAUSE, TG(MDIA),
       KC_MFFD,
       KC_MRWD, KC_ENT, KC_SPC
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  esc   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |  up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | control|      |MsLeft|MsDown|MsRght|      |------|           |------|      | left | down | right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |caps  | opti | cmd  |                                       | lclk | Rclk |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ~L0 | mute |       | pause|  ~L1 |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |back  | del  | volup|       | next |enter | space|
 *                                 |space |      |------|       |------|      |      |
 *                                 |      |      |voldwn|       | prev |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO,
       KC_LCTRL, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_CAPSLOCK, KC_LALT, KC_LGUI,
                                           TG(BASE), KC_MUTE,
                                                    KC_VOLU,
                                  KC_BSPC, KC_DEL, KC_VOLD,
    // right hand
       KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,  KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO,
               KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
       KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_BTN1, KC_BTN2, KC_NO, KC_NO, KC_NO,
       KC_MEDIA_PLAY_PAUSE, TG(SYMB),
       KC_MFFD,
       KC_MRWD, KC_ENT, KC_SPC
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
          rgblight_init();
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
