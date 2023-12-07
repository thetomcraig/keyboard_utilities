#include QMK_KEYBOARD_H
#include "common_macros.h"
// Used by the ergodox and ergodox infinity keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* WINDOWS */
  [DOX_BASE] = LAYOUT_ergodox(
    /* left hand */
    /* top row */                   KC_ESC,      KC_1,       KC_2,        KC_3,      KC_4,      KC_5,      KC_GRV,
                                    KC_TAB,      KC_Q,       KC_W,        KC_E,      KC_R,      KC_T,
    /* index, large top key */                                                                             MO(2),
    /* home row */                  HYPER,       KC_A,       KC_S,        KC_D,      KC_F,      KC_G,
                                    KC_LSFT,     KC_Z,       KC_X,        KC_C,      KC_V,      KC_B,
    /* index, large bottom key */                                                                          MO(1),
    /* bottom row */                KC_LCTL,    TG(2),       KC_CAPS,     KC_LGUI,  KC_LALT,
    /* thumb, small top keys */                                                                                              KC_ENT,   KC_LCTL,
    /* thumb, small middle key */                                                                                                      _______,
    /* thumb, big keys */                                                                                          KC_SPC,   KC_BSPC,
    /* thumb, small bottom key */                                                                                                      KC_LCTL,


    /* right hand */
    /* top row */                                               KC_6,       KC_7,     KC_8,        KC_9,         KC_0,        KC_LBRC,     KC_RBRC,
    /* index, large top key */                                  KC_MINUS,
                                                                            KC_Y,     KC_U,        KC_I,         KC_O,        KC_P,        KC_BSLS,
    /* home row */                                                          KC_H,     KC_J,        KC_K,         KC_L,        KC_SCLN,     KC_QUOT,
    /* index, large bottom key */                               KC_EQUAL,
                                                                            KC_N,     KC_M,        KC_COMM,      KC_DOT,      KC_SLSH,     KC_RSFT,
    /* bottom row */                                                                  KC_RALT,     KC_RGUI,      KC_CAPS,      TG(2),       KC_RCTL,
    /* thumb, small top keys */     KC_RCTL,    KC_BSPC,
    /* thumb, small middle key */   _______,
    /* thumb, small bottom key */   KC_RCTL,
    /* thumb, big keys */                       KC_ENT,  KC_SPC
  ),

  /* LAYER 1: AUX */
  [DOX_LYR1] = LAYOUT_ergodox(
                                   /* left hand */
    /* top row */                  _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______,
    /* index, large top key */                                                           _______,
    /* home row */                 _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______,
    /* index, large bottom key */                                                        _______,
    /* bottom row */               P_CMP,   P_1PASS, P_OKTA,  P_CP,    P_LP,
    /* thumb, small top keys */                                                                              QK_BOOT,   QK_BOOT,
    /* thumb, small middle key */                                                                                       QK_BOOT,
    /* thumb, big keys */                                                                           _______, KC_DEL,
    /* thumb, small bottom key */                                                                                       QK_BOOT,

                                  /* right hand */
    /* top row */                                                    _______, _______, _______, _______, _______, KC_BRTD, KC_BRTU,
    /* index, large top key */                                       _______,
                                                                              _______, _______, _______, _______, _______, _______, 
    /* home row */                                                            _______, _______, _______, _______, _______, _______, 
    /* index, large bottom key */                                    _______,
                                                                              _______, _______, _______, _______, _______, _______, 
    /* bottom row */                                                                   KC_MRWD,  KC_MPLY,KC_MFFD, KC_VOLD, KC_VOLU,
    /* thumb, small top keys */             KC_DEL, KC_DEL,
    /* thumb, small middle key */           QK_BOOT,
    /* thumb, small bottom key */           QK_BOOT,
    /* thumb, big keys */                           _______, _______
  ),

  /* MACOS */
  [DOX_LYR2] = LAYOUT_ergodox(
                                    /* left hand */
    /* top row */                   KC_ESC,      KC_1,       KC_2,        KC_3,      KC_4,      KC_5,      KC_GRV,
                                    KC_TAB,      KC_Q,       KC_W,        KC_E,      KC_R,      KC_T,
    /* index, large top key */                                                                             MO(2),
    /* home row */                  HYPER,       KC_A,       KC_S,        KC_D,      KC_F,      KC_G,
                                    KC_LSFT,     KC_Z,       KC_X,        KC_C,      KC_V,      KC_B,
    /* index, large bottom key */                                                                          MO(1),
    /* bottom row */                KC_LCTL,    TG(2),      KC_CAPS,      KC_LALT,   KC_LGUI,
    /* thumb, small top keys */                                                                                              KC_ENT,   KC_LCTL,
    /* thumb, small middle key */                                                                                                      _______,
    /* thumb, big keys */                                                                                          KC_SPC,   KC_BSPC,
    /* thumb, small bottom key */                                                                                                      KC_LCTL,


    /* right hand */
    /* top row */                                               KC_6,       KC_7,     KC_8,        KC_9,         KC_0,        KC_LBRC,     KC_RBRC,
    /* index, large top key */                                  KC_MINUS,
                                                                            KC_Y,     KC_U,        KC_I,         KC_O,        KC_P,        KC_BSLS,
    /* home row */                                                          KC_H,     KC_J,        KC_K,         KC_L,        KC_SCLN,     KC_QUOT,
    /* index, large bottom key */                               KC_EQUAL,
                                                                            KC_N,     KC_M,        KC_COMM,      KC_DOT,      KC_SLSH,     KC_RSFT,
    /* bottom row */                                                                  KC_RGUI,     KC_RALT,      KC_CAPS,     TG(2),       KC_RCTL,
    /* thumb, small top keys */     KC_RCTL,   KC_BSPC,
    /* thumb, small middle key */   _______,
    /* thumb, small bottom key */   KC_RCTL,
    /* thumb, big keys */                       KC_ENT,  KC_SPC
  )

};
