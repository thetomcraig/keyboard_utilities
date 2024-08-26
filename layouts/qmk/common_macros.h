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


enum custom_keycodes {
  /***********/
  /* ERGODOX */
  /***********/
  EPRM,
  VRSN,
  RGB_SLD,

  /***********/
  /* TMUX */
  /***********/
  // TX_NXT,
  // TX_PRV,
  // TX_NEW,
  // TX_MV_L,
  // TX_MV_R,
  // TX_CYC,
  // TX_TGL,
  // TX_SRCH,
  // TX_CMD,
  // TUX_CMD,

  /******************/
  /* LINE MOVEMENTS */
  /******************/
  WD_NXT,
  WD_PRV,
  LIN_SRT,
  LIN_END,

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


