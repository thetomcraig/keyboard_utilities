; #Include WinGetPosEx.ahk
#EscapeChar \

IsAppActive(App) {
    Winget,AppName,ProcessName,A
    return AppName == App
}

; Middle mouse button to win+tab
MButton::#Tab

; Modifiers
; Map Windows to Control
; LWin::LCtrl
; RWin::RCtrl
; Map F9 to Windows key
; F9::LWin



; For word-wise movement,
; alt+arrows is for macOS,
; but ctrl+arrows is Windows
; !Left::^Left
; !Right::^Right

; Alt+Space: clipboard history
!Space::
Send, ^+!q ; Ctrl+Shift+Alt+Q
Return


;Browser Tabs
^+]::Send, ^{tab}
^+[::Send, +^{tab}

;Browser History
^]::Send, !{Right}
^[::Send, !{Left}


; Readline-esque controls
Home::
if IsAppActive("WindowsTerminal.exe") {
    Send, ^a
    ; MsgBox, "terminal active"
} else {
    ; MsgBox, "terminal NOT active"
    Send, {Home}
}
Return
End::
if IsAppActive("WindowsTerminal.exe") {
    Send, ^e
} else {
    Send, {End}
}
Return
+^!p::
if IsAppActive("WindowsTerminal.exe") {
    Send, ^k
} else {
    Send, +{End}
    Send, {Del}
}
Return
+^!u::
if IsAppActive("WindowsTerminal.exe") {
    Send, ^w
} else {
    Send, ^{Backspace}
}
Return



;;;;;;;;;;;;;;;;;;;
; Window Controls ;
;;;;;;;;;;;;;;;;;;;

; Windows has no concept of "hiding" an application
; So this will just minimize thea active window
^h::WinMinimize, A
Return
^m::WinMinimize, A
Return

; "Quit" (close the front window)
^q::
Send !{f4}
Return

; Halves and quarters
^!+w::send, #{Up}
+^!s::Send, #{Down}
+^!r::Send, +#{Down}
+^!f::WinMaximize, A

+^!a::
WinMaximize, A
Send, #{Left}
Sleep, 100
Send, {Esc}
Return

+^!d::
WinMaximize, A
Send, #{Right}
Sleep, 100
Send, {Esc}
Return

; Move window to NEXT display
+^!x::Send, +#{Right}


;;;;;;;;;;
; Ctrl+` ;
;;;;;;;;;;
; This emulates Cmd+backtick on MacOS, 
; to cycle between the windows of the current application
^`:: ;
; WinGetClass, CurrentActive, A
WinGet, CurrentActive, ProcessName, A
; MsgBox, The active window's class is "%CurrentActive%".
; WinGet, OutputVar, ProcessName, A
; MsgBox, The active window's class is "%OutputVar%".
WinGet, Instances, Count, ahk_exe %CurrentActive%
If Instances > 1
    WinSet, Bottom,, A
WinActivate, ahk_exe %CurrentActive%
return

; Emulate the macOS hotkeys for screenshots
^+4::
^+5::
Run, "SnippingTool.exe" ,, min
WinWait, Snipping Tool
Return
ControlSend,, ^{n}, ahk_class Microsoft-Windows-SnipperToolbar


^+m::
^+c::
    IfWinExist, ahk_exe C:\Program Files\Microsoft Office\root\Office16\OUTLOOK.EXE
    {
        WinActivate
    }
    else
    {
        Run, C:\Program Files\Microsoft Office\root\Office16\OUTLOOK.EXE
        WinActivate
    }
return
^+f::
    IfWinExist, ahk_exe C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe
    {
        WinActivate
    }
    else
    {
        Run, C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe
        WinActivate
    }
return





; ALT TAB - CHROME TOO
; DARK READER
; Ctrl+, for settings everywhere
; ctrl+k to ctrl+f in teams


; Debugging
+^!b::
Winget,AppName,ProcessName,A
MsgBox, %AppName%
Return

