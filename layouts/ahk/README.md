# Auto Hot Key Scripts

## Guide
- Install as a symlinks in Windows, through wsl
  ```
  ` New-Item -ItemType SymbolicLink -Path "C:\Users\TomCraig\OneDrive - ayahealthcare.com\Documents\AutoHotkey\ahk_hotkeys.ahk" -Target "\\wsl$\Ubuntu\home\tom\dotfiles\ahk\hotkeys.ahk"

  New-Item -ItemType SymbolicLink -Path "C:\Users\TomCraig\OneDrive - ayahealthcare.com\Documents\AutoHotkey\WinGetPosEx.ahk" -Target "\\wsl$\Ubuntu\home\tom\dotfiles\ahk\WinGetPosEx.ahk"

  ```