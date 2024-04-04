#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

enum custom_layers {
    _BASE,
    _NUM,
    _CODE,
    _OS,
};

enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    TX_TGL,
    LIN_SRT,
    WD_PRV,
    WD_NXT,
    LIN_END,
    TX_CYC,
    TX_CMD,
    TX_SRCH,
    TX_NXT,
    TX_PRV,
    TX_MV_L,
    TX_MV_R,
    TX_NEW,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case TX_TGL:
        if (record->event.pressed) {
            register_code(KC_F12);
        } else {
            unregister_code(KC_F12);
        }
        break;

    case LIN_SRT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("a"));
        }
        break;

    case WD_PRV:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_LEFT);
            unregister_code(KC_LALT);
        }
        break;

    case WD_NXT:
        if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_RIGHT);
        } else {
            unregister_code(KC_RIGHT);
            unregister_code(KC_LALT);
        }
        break;

    case LIN_END:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("e"));
        }
        break;

    case TX_CMD:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING(":");
        }
        break;

    case TX_SRCH:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING("f");
        }
        break;

    case TX_CYC:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING(";");
        }
        break;

    case TX_NXT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING("n");
        }
        break;

    case TX_PRV:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING("p");
        }
        break;

    case TX_MV_L:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING(",");
        }
        break;

    case TX_MV_R:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING(".");
        }
        break;

    case TX_NEW:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("b"));
            SEND_STRING("/");
        }
        break;

    }
    return true;
};


#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC , KC_F1 , KC_F2       , KC_F3       , KC_F4       , KC_F5  ,          KC_F6  , KC_F7       , KC_F8          , KC_F9       , KC_F10 , KC_F11 ,
        KC_EQL , KC_1  , KC_2        , KC_3        , KC_4        , KC_5   ,          KC_6   , KC_7        , KC_8           , KC_9        , KC_0   , KC_MINS,
        KC_TAB , KC_Q  , KC_W        , KC_E        , KC_R        , KC_T   ,          KC_Y   , KC_U        , KC_I           , KC_O        , KC_P   , KC_BSLS,
        KC_LCTL, KC_A  , LCTL_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G   ,          KC_H   , RSFT_T(KC_J), RGUI_T(KC_K)   , RCTL_T(KC_L), KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z  , KC_X        , KC_C        , LALT_T(KC_V), KC_B   ,          KC_N   , RALT_T(KC_M), KC_COMM        , KC_DOT      , KC_SLSH, KC_RSFT,
                 KC_GRV, KC_BSLS     , KC_LEFT     , KC_RGHT     ,                            KC_UP       , KC_DOWN        , KC_LBRC     , KC_RBRC,
                                                                   KC_BTN1, KC_BTN2, KC_BTN1,
                                            KC_LCTL, KC_LALT,                                 KC_RCTL     , KC_RGUI        ,
                 LT(_CODE, KC_SPC), LT(_OS, KC_TAB), KC_HOME,                                 KC_PGUP     , LT(_OS, KC_ENT), LT(_NUM, KC_BSPC),
                                                      KC_END,                                 KC_PGDN
    ),
    [_NUM] = LAYOUT(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,          KC_F6,   KC_F7  , KC_F8  , KC_F9  , KC_F1  , KC_F2  ,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______, _______, _______, _______, _______, _______,
        XXXXXXX, KC_LBRC, KC_7   , KC_8   , KC_9   , KC_RBRC,          _______, _______, _______, _______, _______, _______,
        XXXXXXX, KC_SCLN, KC_4   , KC_5   , KC_6   , KC_EQL ,          _______, _______, _______, _______, _______, _______,
        XXXXXXX, KC_GRV , KC_1   , KC_2   , KC_3   , KC_BSLS,          _______, _______, _______, _______, _______, _______,
                _______ , _______, _______, _______,                            _______, _______, _______, _______,
                                                     _______, _______, _______,
                                   _______, _______,                            _______, _______,
                             KC_0, KC_MINS, _______,                            _______, LT(_OS, KC_ENT), LT(_NUM, KC_BSPC) ,
                                            _______,                            _______
    ),
    [_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______ , _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______ , _______, _______,
        _______, _______, _______, _______, _______, _______,          TX_TGL , LIN_SRT, WD_PRV , WD_NXT  , LIN_END, _______,
        _______, TX_CMD , _______, _______, TX_SRCH, _______,          KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, TX_CYC , _______,
        _______, _______, _______, _______, _______, _______,          TX_NXT , TX_PRV , TX_MV_L, TX_MV_R , TX_NEW, _______,
                _______ , _______, _______, _______,                            _______, _______, _______ , _______,
                                                     _______, _______, _______,
                                   _______, _______,                            _______, _______,
                          _______, _______, _______,                            _______, _______, _______,
                                            _______,                            _______
    ),
    [_OS] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                _______ , _______, _______, _______,                            _______, _______, _______, _______,
                                                     _______, _______, _______,
                                   _______, _______,                            _______, _______,
                          _______, _______, _______,                            _______, _______, _______,                             
                                            _______,                            _______
    )
};
