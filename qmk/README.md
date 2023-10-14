# QMK


- Setup qmk with `brew`, which will clone to the home dir
- Copy these files to that repo (infinity)
  ```
  QMK_REPO_DIR=${HOME}/qmk_firmware
  KEYMAP_DIR=${QMK_REPO_DIR}/keyboards/input_club/ergodox_infinity/keymaps/thetomcraig
  mkdir -p $KEYMAP_DIR
  cp ergodox_infinity/* $KEYMAP_DIR
  cp secrets.h $KEYMAP_DIR
  cp common_macros.h $KEYMAP_DIR
  cp general_ergodox_keymap.h $KEYMAP_DIR

  cp flash_infinity_ergodox.sh $QMK_REPO_DIR
  ```
- Go flash with QMK
  - `cd $QMK_REPO_DIR`
  - (Run the flashing file)

