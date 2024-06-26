// Common Macros used by my mechanical keyboards
// Keyboard keymaps can use these macros by including this .h file

#include QMK_KEYBOARD_H
#include "version.h"
#include "secrets.h"

#define DOX_BASE 0  
#define DOX_LYR1 1 
#define DOX_LYR2 2

#define KC_BRTU KC_BRMU
#define KC_BRTD KC_BRMD
#define KC_CAPS KC_CAPS_LOCK

#define HYPER KC_CAPS

extern keymap_config_t keymap_config;

enum custom_keycodes {
  /***********/
  /* ERGODOX */
  /***********/
  EPRM,
  VRSN,
  RGB_SLD,

  /**********/
  /* NUMPAD */
  /**********/
  NP_COL,

  /*************/
  /* PASSWORDS */
  /*************/
  P_CMP,
  P_1PASS,
  P_OKTA,
  P_CP,
  P_LP,
};


// This function enters passwords
// The strings are defined in a file NOT in VCS, called "secrets.h"
bool process_password_keys(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case P_CMP:
      if (record->event.pressed) {
        send_string(computer_password);
        send_string(SS_TAP(X_ENTER));
      }
      break;
    case P_1PASS:
      if (record->event.pressed) {
        send_string(one_pass_password);
        send_string(SS_TAP(X_ENTER));
      }
      break;
    case P_OKTA:
      if (record->event.pressed) {
        send_string(okta_password);
        send_string(SS_TAP(X_ENTER));
      }
      break;
    case P_CP:
      if (record->event.pressed) {
        send_string(coachportal_password);
        send_string(SS_TAP(X_ENTER));
      }
      break;
    case P_LP:
      if (record->event.pressed) {
        send_string(last_pass_password);
        send_string(SS_TAP(X_ENTER));
      }
      break;
  }
  return true;
}

// This processes all other custom macros; they're keys defined above
bool process_custom_macro_keys(uint16_t keycode, keyrecord_t *record) {
  // bool still_need_to_process = process_password_keys(keycode, record);
  // if (still_need_to_process == false) {
  //   return false;
  // }

  switch (keycode) {
    case NP_COL:
      if (record->event.pressed) {
        send_string(":");
      }
      break;
  }
  return true;
}
