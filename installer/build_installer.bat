@echo off
setlocal enabledelayedexpansion

REM ============================================
REM  Flappy Bird - Build Installer Script
REM  This script builds FlappyBird_Installer.exe
REM  using NSIS (Nullsoft Scriptable Install System).
REM ============================================

set TOOLS_DIR=%~dp0..\tools
set NSIS_DIR=%TOOLS_DIR%\nsis
set INSTALLER_DIR=%~dp0
set PROJECT_DIR=%~dp0..
set SRC_DIR=%~dp0..\src

echo.
echo ============================================
echo   Flappy Bird - Membuat Installer
echo ============================================
echo.

REM ---------- Step 1: Build .exe jika belum ada ----------
if not exist "%PROJECT_DIR%\flappy_bird.exe" (
    echo [1/3] Build game .exe dulu...
    call "%~dp0..\build_windows.bat"
    if not exist "%PROJECT_DIR%\flappy_bird.exe" (
        echo ERROR: Gagal build .exe
        pause
        exit /b 1
    )
) else (
    echo [1/3] Game .exe ditemukan.
)

REM Copy .exe ke folder installer
copy /Y "%PROJECT_DIR%\flappy_bird.exe" "%INSTALLER_DIR%flappy_bird.exe" >nul
echo [1/3] Game .exe disalin ke folder installer.

REM ---------- Step 2: Download NSIS jika belum ada ----------
if not exist "%NSIS_DIR%\makensis.exe" (
    echo [2/3] Mendownload NSIS...
    if not exist "%TOOLS_DIR%" mkdir "%TOOLS_DIR%"
    curl -sL "https://sourceforge.net/projects/nsis/files/NSIS%203/3.12/nsis-3.12.zip/download" -o "%TOOLS_DIR%\nsis.zip"
    echo [2/3] Ekstrak NSIS...
    powershell -command "Expand-Archive -Path '%TOOLS_DIR%\nsis.zip' -DestinationPath '%TOOLS_DIR%' -Force"
    for /d %%d in ("%TOOLS_DIR%\nsis-*") do move "%%d" "%NSIS_DIR%" 2>nul
    if not exist "%NSIS_DIR%" set "NSIS_DIR=%TOOLS_DIR%\nsis-3.12"
    echo [2/3] NSIS siap!
) else (
    echo [2/3] NSIS ditemukan.
)

REM ---------- Step 3: Compile installer ----------
echo [3/3] Membuat installer...

set PATH=%NSIS_DIR%;%PATH%
makensis.exe /V2 "%INSTALLER_DIR%installer.nsi"

if !ERRORLEVEL! EQU 0 (
    echo.
    echo ============================================
    echo   SUCCESS: Installer berhasil dibuat!
    echo   File: %INSTALLER_DIR%FlappyBird_Installer.exe
    echo ============================================
    echo.
    echo   Cara pakai:
    echo     1. Buka folder installer/
    echo     2. Double-click FlappyBird_Installer.exe
    echo     3. Ikuti petunjuk instalasi
    echo.
) else (
    echo.
    echo ============================================
    echo   FAILED (error code: !ERRORLEVEL!)
    echo ============================================
    pause
    exit /b !ERRORLEVEL!
)

pause
