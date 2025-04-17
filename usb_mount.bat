@echo off
:: 判斷是否已是系統管理員
net session >nul 2>&1
if %errorLevel% == 0 (
    goto :admin
) else (
    :: 重新以系統管理員執行
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit
)

:admin
echo 現在是系統管理員模式
usbipd list
usbipd attach --busid 5-1 --wsl Ubuntu-22.04
pause