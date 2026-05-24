;============================================
; Flappy Bird C++ — Windows Installer
; NSIS (Nullsoft Scriptable Install System)
;============================================

Unicode True
RequestExecutionLevel admin

!define APP_NAME "Flappy Bird C++"
!define APP_VERSION "1.0.0"
!define APP_PUBLISHER "thefulan123"
!define APP_URL "https://github.com/thefulan123/simple_flappy_bird_using_cpp"

;----------------------------------------
; Include Modern UI
;----------------------------------------
!include "MUI2.nsh"

;----------------------------------------
; General
;----------------------------------------
Name "${APP_NAME}"
OutFile "FlappyBird_Installer.exe"
InstallDir "$PROGRAMFILES64\${APP_NAME}"
InstallDirRegKey HKLM "Software\${APP_NAME}" ""

;----------------------------------------
; Interface Settings
;----------------------------------------
!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_RUN "$INSTDIR\flappy_bird.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Mainkan Flappy Bird sekarang"

;----------------------------------------
; Pages
;----------------------------------------
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;----------------------------------------
; Languages
;----------------------------------------
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Indonesian"

;----------------------------------------
; Installer Sections
;----------------------------------------
Section ""
    SetOutPath "$INSTDIR"

    File "flappy_bird.exe"

    CreateDirectory "$SMPROGRAMS\${APP_NAME}"
    CreateShortCut "$SMPROGRAMS\${APP_NAME}\Flappy Bird C++.lnk" "$INSTDIR\flappy_bird.exe"
    CreateShortCut "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

    CreateShortCut "$DESKTOP\Flappy Bird C++.lnk" "$INSTDIR\flappy_bird.exe"

    WriteUninstaller "$INSTDIR\Uninstall.exe"

    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "DisplayName" "${APP_NAME}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "DisplayVersion" "${APP_VERSION}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "Publisher" "${APP_PUBLISHER}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "URLInfoAbout" "${APP_URL}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "DisplayIcon" "$INSTDIR\flappy_bird.exe,0"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "UninstallString" "$INSTDIR\Uninstall.exe"
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" \
        "NoRepair" 1
SectionEnd

;----------------------------------------
; Uninstaller Section
;----------------------------------------
Section "Uninstall"
    Delete "$INSTDIR\flappy_bird.exe"
    Delete "$INSTDIR\Uninstall.exe"
    RMDir "$INSTDIR"

    Delete "$SMPROGRAMS\${APP_NAME}\Flappy Bird C++.lnk"
    Delete "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk"
    RMDir "$SMPROGRAMS\${APP_NAME}"
    Delete "$DESKTOP\Flappy Bird C++.lnk"

    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
    DeleteRegKey HKLM "Software\${APP_NAME}"
SectionEnd
