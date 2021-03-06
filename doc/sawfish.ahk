; IMPORTANT INFO ABOUT GETTING STARTED: Lines that start with a
; semicolon, such as this one, are comments.  They are not executed.

; This script has a special filename and path because it is automatically
; launched when you run the program directly.  Also, any text file whose
; name ends in .ahk is associated with the program, which means that it
; can be launched simply by double-clicking it.  You can have as many .ahk
; files as you want, located in any folder.  You can also run more than
; one .ahk file simultaneously and each will get its own tray icon.

; SAMPLE HOTKEYS: Below are two sample hotkeys.  The first is Win+Z and it
; launches a web site in the default browser.  The second is Control+Alt+N
; and it launches a new Notepad window (or activates an existing one).  To
; try out these hotkeys, run AutoHotkey again, which will load this file.

;      /* start code-generator "^;"
;      perl -e '
;           %key_win_progs = (
;                                n => ["Mozilla Firefox", "firefox"],
;                                m => ["emacs\@", "bash -c emacs"],
;                                t => [q(ahk_class mintty), "bash -c ~/bin/windows/start-putty.sh"],
;                                r => ["RunBhjRun", "runbhjrun"],
;                            );
;           foreach (keys %key_win_progs) {
;              ($key, $win, $prog) = ($_, @{$key_win_progs{$_}});
;               print <<EOF;
;#$key\::
;If A_PriorHotkey = #h
;{
;SetTitleMatchMode,2
;IfWinExist, $win
;    WinActivate
;else
;    Run $prog
;}
;else
;{
;  SendInput ^{$key}
;}
;return
;
;EOF
;           }
;'
;        end code-generator */
      ;; start generated code
#t::
  If A_PriorHotkey = #h
  {
    SetTitleMatchMode,2
    IfWinExist, ahk_class mintty
      WinActivate
    else
      Run bash -c ~/bin/windows/start-putty.sh
  }
  else
  {
    SendInput ^{t}
  }
  return

#n::
  If A_PriorHotkey = #h
  {
    SetTitleMatchMode,2
    IfWinExist, Mozilla Firefox
      WinActivate
    else
      Run firefox
  }
  else
  {
    SendInput ^{n}
  }
  return

#m::
  If A_PriorHotkey = #h
  {
    SetTitleMatchMode,2
    IfWinExist, emacs@
      WinActivate
    else
      Run bash -c emacs
  }
  else
  {
    SendInput ^{m}
  }
  return

#r::
  If A_PriorHotkey = #h
  {
    SetTitleMatchMode,2
    IfWinExist, RunBhjRun
      WinActivate
    else
      Run runbhjrun
  }
  else
  {
    SendInput ^{r}
  }
  return


      ;; end generated code
#h::
  Return

#d::
If A_PriorHotkey = #h
    Run ToggleDesktop
return

#s::
If A_PriorHotkey = #h
  Run ifind.exe
else
{
  SendInput ^{s}
}
return

#F1::
WinGet, MinMax, MinMax, A
if MinMax = 1
    WinRestore, A
else
    WinMaximize, A
return

#q::
SendInput !{F4}
return

;/* start code-generator "^;"
;   for x in "w" "c" "v" "l" "\\"; do
;       echo "#$x::"
;       echo "    SendInput ^{$x}"
;       echo "return"
;       echo
;   done
;   end code-generator */
; /* start generated code */
#w::
  SendInput ^{w}
  return

#c::
  SendInput ^{c}
  return

#v::
  SendInput ^{v}
  return

#l::
  SendInput ^{l}
  return

#\::
  SendInput ^{\}
  return


; /* end generated code */

WheelUp::
  Send {WheelDown}
  Return

WheelDown::
  Send {WheelUp}
  Return

<#Tab::AltTab
>#Tab::AltTab
