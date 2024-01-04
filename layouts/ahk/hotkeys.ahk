; #Include WinGetPosEx.ahk
#EscapeChar \


IsAppActive(App) {
    Winget,AppName,ProcessName,A
    return AppName == App
}


; Middle mouse button to win+tab
MButton::#Tab

; Map Win+Tab to Alt+Tab
; LWin & Tab::AltTab
; RWin & Tab::AltTab

; Modifiers
; Map Windows to Control
LWin::LCtrl
RWin::RCtrl
; Map F9 to Windows key
F9::LWin

; For word-wise movement,
; alt+arrows is for macOS,
; but ctrl+arrows is Windows
!Left::^Left
!Right::^Right

; Alt+Space: clipboard history
!Space::
Send #{v}
Return

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
} else {
    Send, {Home}
}
Return
End:
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


; TODO: refactor
; and figure out centering logic
; Window Controls
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
; DEV TOOLS
; DARK READER
; Ctrl+, for settings everywhere
; ctrl+k to ctrl+f in teams


; Debugging
+^!b::
Winget,AppName,ProcessName,A
MsgBox, %AppName%
Return

