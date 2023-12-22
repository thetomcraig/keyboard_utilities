; #Include WinGetPosEx.ahk
#EscapeChar \


IsAppActive(App) {
    Winget,AppName,ProcessName,A
    return AppName == App
}


; disable for miryoku
; SetCapslockState, AlwaysOff

; Middle mouse button to win+tab
MButton::#Tab

;;;;;;;;;;;;;
; Modifiers ;
;;;;;;;;;;;;;
; Map Alt Control
; LAlt::LCtrl
; RAlt::RCtrl
; Map Win to Alt
; LWin::LAlt
; RWin::RAlt


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

;#SingleInstance, Force
; Map Ctrl+Tab to Win+Tab
; But in the browser, make it select next tab
^Tab::
if IsAppActive("brave.exe") {
    Send, ^{PgDn}
} else {
    Send #{Tab}
}
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

; vim navigation 
; +^!h:: Send {Left} 
; +^!l:: Send {Right}
; +^!k:: Send {Up}
; +^!j:: Send {Down}

; Forward Delete
; +^!Backspace::Send, {Del}

; Back and Forward One Word
; +^!i::Send, ^{Left}
; +^!o::Send, ^{Right}

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



; Tmux Commands
+^!/::
Send, ^b
Sleep, 50
Send, c
Return
+^!-::
Send, ^b
Sleep, 50
Send, -
Return
+^!\::
Send, ^b
Sleep, 50
Send, {Text}\
Return
+^!|::
Send, ^b
Sleep, 50
Send, |
Return
+^!n::
Send, ^b
Sleep, 50
Send, n
Return
+^!m::
Send, ^b
Sleep, 50
Send, m
Return
+^!t::
Send, ^b
Sleep, 50
Send, t
Return
+^!,::
Send, ^b
Sleep, 50
Send, ,
Return
+^!.::
Send, ^b
Sleep, 50
Send, .
Return
+^!\;::
Send, ^b
Sleep, 50
Send, {Text};
Return

; TODO: refactor
; and figure out centering logic
; Window Controls
^!+w::send, #{Up}
+^!s::Send, #{Down}
+^!r::Send, +#{Down}
+^!f::WinMaximize, A

; +^!a::
; WinMaximize, A
; Send, #{Left}
; Sleep, 100
; Send, {Esc}
; Return

; +^!d::
; WinMaximize, A
; Send, #{Right}
; Sleep, 100
; Send, {Esc}
; Return

; Move window to NEXT display
+^!x::Send, +#{Right}

; Emulate the macOS hotkeys for screenshots
^+4::
^+5::
Run, "SnippingTool.exe" ,, min
WinWait, Snipping Tool
Return
ControlSend,, ^{n}, ahk_class Microsoft-Windows-SnipperToolbar

; Debugging
+^!b::
Winget,AppName,ProcessName,A
MsgBox, %AppName%
Return


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

; Initialize a variable to track the state of the backtick key
BacktickState := 0
; Custom hotkey for the backtick key
; `::CheckDoubleTap()

; Function to check for a double-tap of the backtick key
CheckDoubleTap() {
    ; Get the state of the backtick key
    BacktickState := !BacktickState

    ; Wait for a short time to detect a double-tap
    Sleep, 100

    ; If the key is pressed again within the time interval, send Escape
    if (BacktickState && GetKeyState("`", "P"))
    {
        Send, {Esc}
    } else {
        Send, {Text}`
    }

    ; Reset the key state
    BacktickState := 0
    MsgBox, "done"
}





; ALT TAB - CHROME TOO
; DEV TOOLS
; DARK READER
; Ctrl+, for settings everywhere
; ctrl+k to ctrl+f in teams

