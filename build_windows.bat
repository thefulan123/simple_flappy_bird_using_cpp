@echo off
setlocal enabledelayedexpansion

REM ============================================
REM  Flappy Bird - Windows Build Script
REM  This script builds flappy_bird.exe
REM  with statically linked SDL2.
REM ============================================

set TOOLS_DIR=%~dp0tools
set MINGW_DIR=%TOOLS_DIR%\mingw64
set SDL2_DIR=%TOOLS_DIR%\sdl2-mingw\x86_64-w64-mingw32

echo.
echo ============================================
echo   Flappy Bird - Windows Build
echo ============================================

REM ---------- Check / Download MinGW-w64 ----------
if not exist "%MINGW_DIR%\bin\g++.exe" (
    echo [1/3] Downloading MinGW-w64 toolchain...
    if not exist "%TOOLS_DIR%" mkdir "%TOOLS_DIR%"
    curl -sL "https://github.com/brechtsanders/winlibs_mingw/releases/download/16.1.0posix-14.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-16.1.0-mingw-w64ucrt-14.0.0-r2.zip" -o "%TOOLS_DIR%\mingw64.zip"
    echo [1/3] Extracting MinGW-w64 (this may take a while)...
    powershell -command "Expand-Archive -Path '%TOOLS_DIR%\mingw64.zip' -DestinationPath '%TOOLS_DIR%' -Force"
    move "%TOOLS_DIR%\mingw64" "%TOOLS_DIR%\mingw64_extracted" 2>nul
    for /d %%d in ("%TOOLS_DIR%\mingw64*") do move "%%d" "%MINGW_DIR%" 2>nul
    if not exist "%MINGW_DIR%" (
        echo ERROR: Could not find MinGW directory after extraction.
        pause
        exit /b 1
    )
    echo [1/3] MinGW-w64 ready!
) else (
    echo [1/3] MinGW-w64 found.
)

REM ---------- Check / Download SDL2 for MinGW ----------
if not exist "%SDL2_DIR%\include\SDL2\SDL.h" (
    echo [2/3] Downloading SDL2 development libraries for MinGW...
    if not exist "%TOOLS_DIR%" mkdir "%TOOLS_DIR%"
    curl -sL "https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-devel-2.32.10-mingw.zip" -o "%TOOLS_DIR%\sdl2-mingw.zip"
    echo [2/3] Extracting SDL2...
    powershell -command "Expand-Archive -Path '%TOOLS_DIR%\sdl2-mingw.zip' -DestinationPath '%TOOLS_DIR%\sdl2-mingw' -Force"
    echo [2/3] SDL2 ready!
) else (
    echo [2/3] SDL2 found.
)

REM ---------- Build ----------
echo [3/3] Compiling Flappy Bird...

set PATH=%MINGW_DIR%\bin;%MINGW_DIR%\libexec\gcc\x86_64-w64-mingw32\16.1.0;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem

"%MINGW_DIR%\bin\g++.exe" -static ^
  -I"%SDL2_DIR%\include" ^
  -I"%SDL2_DIR%\include\SDL2" ^
  -L"%SDL2_DIR%\lib" ^
  -o "%~dp0flappy_bird.exe" ^
  "%~dp0src\main.cpp" "%~dp0src\game.cpp" "%~dp0src\bird.cpp" "%~dp0src\pipe.cpp" ^
  -lmingw32 -lSDL2main -lSDL2 -mwindows ^
  -lsetupapi -lole32 -loleaut32 -limm32 -lwinmm -lversion ^
  -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lshell32 -luuid

if !ERRORLEVEL! EQU 0 (
    echo.
    echo ============================================
    echo   SUCCESS: flappy_bird.exe created!
    echo   Location: %~dp0flappy_bird.exe
    echo   Size: 
    for %%f in ("%~dp0flappy_bird.exe") do echo   %%~zf bytes
    echo ============================================
    echo.
    echo   Just double-click flappy_bird.exe to play!
    echo.
) else (
    echo.
    echo ============================================
    echo   FAILED (error code: !ERRORLEVEL!)
    echo ============================================
    echo.
    echo   Check that:
    echo     - MinGW is at: %MINGW_DIR%
    echo     - SDL2 is at:  %SDL2_DIR%
    echo     - Source files exist in: %~dp0src\
    echo.
    pause
    exit /b !ERRORLEVEL!
)

pause
