#include QMK_KEYBOARD_H
#include "./general_redox_keymap.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Before normal operation, see if keycode is for a custom macro
  // If it is, break early
  return process_custom_macro_keys(keycode, record);
};
