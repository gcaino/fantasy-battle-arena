@echo off

set (PROJECT_DIR)=%~1
set (TARGET_OUTPUT_DIR)=%~2
set (CONFIGURATION)=%~3

IF "%(CONFIGURATION)%"=="DEBUG" (
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-graphics-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-window-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-system-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-audio-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 

Xcopy "%(PROJECT_DIR)%ext\VLD\bin\Win64\vld_x64.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\VLD\bin\Win64\dbghelp.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\VLD\bin\Win64\Microsoft.DTfW.DHL.manifest" "%(TARGET_OUTPUT_DIR)%" /E /D 
)

IF "%(CONFIGURATION)%"=="RELEASE" (
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-graphics-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-window-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-system-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\sfml-audio-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
)

Xcopy /E /I /Y /D "%(PROJECT_DIR)%assets" "%(TARGET_OUTPUT_DIR)%assets"
Xcopy "%(PROJECT_DIR)%ext\SFML-2.5.1-windows-vc15-64-bit\bin\openal32.dll" "%(TARGET_OUTPUT_DIR)%" /E /D