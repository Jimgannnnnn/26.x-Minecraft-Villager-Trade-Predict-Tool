@echo off
chcp 65001 >nul

echo ========================================
echo  村民交易预测工具 - C版本构建
echo ========================================
echo.

set "SRC_DIR=%~dp0"
set "OUT_DIR=%SRC_DIR%dist"
set "EXE_NAME=村民交易预测工具.exe"

if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

REM 尝试检测编译器
where gcc >nul 2>&1
if %errorlevel% equ 0 goto BUILD_GCC

where cl >nul 2>&1
if %errorlevel% equ 0 goto BUILD_MSVC

echo [错误] 未找到 gcc 或 MSVC cl.exe！
echo.
echo 请安装以下任一编译器：
echo   1. MinGW-w64: https://winlibs.com/ (下载解压后加入 PATH)
echo   2. MinGW-w64 (winget): winget install -e --id GnuWin32.Make
echo   3. MSVC Build Tools: https://visualstudio.microsoft.com/downloads/
echo.
pause
exit /b 1

:BUILD_GCC
echo [检测] 编译器: GCC
echo.
echo [编译] 源文件 -> %EXE_NAME%
gcc -std=c99 -O2 -s ^
    -o "%OUT_DIR%\%EXE_NAME%" ^
    "%SRC_DIR%main_gui.c" ^
    "%SRC_DIR%villager_trade.c" ^
    "%SRC_DIR%xoroshiro128pp.c" ^
    "%SRC_DIR%md5.c" ^
    -lcomctl32 -lcomdlg32 -lgdi32 -luser32 -lshell32 ^
    -mwindows ^
    -DUNICODE -D_UNICODE

if %errorlevel% equ 0 goto BUILD_OK
echo.
echo [错误] 编译失败！
pause
exit /b 1

:BUILD_MSVC
echo [检测] 编译器: MSVC
echo.
echo [编译] 源文件 -> %EXE_NAME%
cl /nologo /O2 /Fe:"%OUT_DIR%\%EXE_NAME%" ^
    "%SRC_DIR%main_gui.c" ^
    "%SRC_DIR%villager_trade.c" ^
    "%SRC_DIR%xoroshiro128pp.c" ^
    "%SRC_DIR%md5.c" ^
    comctl32.lib comdlg32.lib gdi32.lib user32.lib shell32.lib ^
    /link /SUBSYSTEM:WINDOWS /MACHINE:X64

if %errorlevel% equ 0 goto BUILD_OK
echo.
echo [错误] 编译失败！
pause
exit /b 1

:BUILD_OK
echo.
exit /b 0