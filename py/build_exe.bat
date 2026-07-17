@echo off
chcp 65001 >nul
set "SCRIPT_DIR=%~dp0src"
cd /d "%SCRIPT_DIR%" 2>nul
if errorlevel 1 (
    echo [错误] 无法进入目录: %SCRIPT_DIR%
    pause
    exit /b 1
)

echo ========================================
echo  村民交易预测工具 - 构建 EXE
echo ========================================
echo.

pyinstaller --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [错误] 未找到 pyinstaller，请先运行:
    echo   pip install pyinstaller
    echo.
    pause
    exit /b 1
)

echo [1/2] 清理旧的构建文件...
if exist build rmdir /s /q build
if exist dist rmdir /s /q dist

echo [2/2] 构建 EXE...
pyinstaller --onefile --windowed --name "村民交易导出工具" trade_export_gui.py

if errorlevel 1 (
    echo.
    echo [错误] 构建失败!
    pause
    exit /b 1
)

echo.
echo ========================================
echo  构建完成!
echo  输出: %CD%\dist\村民交易预测工具.exe
echo ========================================
pause