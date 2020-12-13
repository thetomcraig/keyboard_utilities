# Minibook Hackintosh Karabiner Keymaps
## Keyboard Enable/Disable Toggle
- The `karabiner.json` file has functionality to toggle the keyboard on ad off.
- In the "Default" profile, keys are normal.  In "Disable Keys" keys are disabled.
- Toggle between the two with `Command` + `Option` + `Control` + `d`
- NOTE: When in the "disable" mode, all keys _except_ the four above are disabled. This makes it easy to quickly re-enable the keys.
### Install
- Install by replacing your `karabiner.json` with the file `profile_switch.json`
    - `cp profile_switch.json ${HOME}/.config/karabiner/karabiner.json`

