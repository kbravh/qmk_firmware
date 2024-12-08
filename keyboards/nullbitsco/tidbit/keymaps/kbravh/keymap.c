/* Copyright 2021 Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Inspired by https://github.com/propmok/qmk_firmware/

// To compile, run `qmk compile -kb nullbitsco/tidbit -km kbravh -e CONVERT_TO=bit_c_pro`
// See: https://github.com/nullbitsco/docs/blob/main/bit-c-pro/user_guide_en.md#flashing_firmware

#include QMK_KEYBOARD_H

enum layers {
    _NUM = 0,
    _BLEN = 1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUM] = LAYOUT(
  KC_F12, LSFT(KC_TILDE), KC_PSLS,
  KC_P7, KC_P8,   KC_P9,   KC_PAST,
  KC_P4, KC_P5,   KC_P6,   KC_PMNS,
  KC_P1, KC_P2,   KC_P3,   KC_PPLS,
  TO(1), KC_P0,   KC_PDOT, KC_PENT
  ),

    [_BLEN] = LAYOUT(
    KC_F12, LSFT(KC_TILDE), KC_P,
    KC_P7, KC_R, KC_X, LALT(KC_D),
    KC_P4, KC_G, KC_Y, LCTL(KC_PMNS),
    KC_P1, KC_S, KC_Z, LCTL(KC_PPLS),
    TO(0), KC_P0, KC_TAB, KC_SPC
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
    [1] = { ENCODER_CCW_CW(LCTL(MS_WHLD), LCTL(MS_WHLU)), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
};
#endif

// RGB LIGHTING LAYERS
void eeconfig_init_user(void) {  // EEPROM is getting reset!
  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(HSV_CORAL);  // Set it to coral by default
  rgblight_mode(RGBLIGHT_MODE_BREATHING + 2);  // Set it to static gradient
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_config_t rgblight_config;
  switch(biton32(state)) {
    default:
        // Numpad Layer 0
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_CORAL);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;
    case _BLEN:
        // Blender Layer 1
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_ORANGE);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;
    }
return state;
}
