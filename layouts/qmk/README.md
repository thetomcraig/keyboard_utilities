# QMK


- Setup qmk with `brew`, which will clone to the home dir
- Define variable for the keyboard to compile, e.g.
```
KEYBOARD_PATH=input_club/ergodox_infinity
KEYBOARD_PATH=redox
```
- Copy keyboard files to that repo
```
QMK_REPO_DIR=${HOME}/qmk_firmware && \
KEYMAP_DIR=${QMK_REPO_DIR}/keyboards/$KEYBOARD_PATH/keymaps/thetomcraig && \
mkdir -p $KEYMAP_DIR && \
cp $KEYBOARD_PATH/* $KEYMAP_DIR && \
cp secrets.h $KEYMAP_DIR && \
cp common_macros.h $KEYMAP_DIR
```
- For ergodox infinity:
```
cp ergodox_infinity_config.h ${QMK_REPO_DIR}/keyboards/$KEYBOARD_PATH/config.h
```
- Go flash with QMK
```
cd $QMK_REPO_DIR && \
cp $KEYMAP_DIR/flash_keyboard.sh . && \
./flash_keyboard.sh
```

