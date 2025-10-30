@echo off

:: Determine the script's location
set "script_dir=%~dp0"
cd /d "%script_dir%.."

:: Remove old install directories
echo Cleaning previous install builds...
rmdir /s /q out\install-release 2>nul
rmdir /s /q out\install-debug 2>nul

:: Install release build
echo Building Release (install-release)

cmake --preset install-release
if errorlevel 1 goto :error

cmake --build out\install-release --config Release
if errorlevel 1 goto :error

cmake --install out\install-release --config Release
if errorlevel 1 goto :error

:: Install debug build
echo Building Debug (install-debug)

cmake --preset install-debug
if errorlevel 1 goto :error

cmake --build out\install-debug --config Debug
if errorlevel 1 goto :error

cmake --install out\install-debug --config Debug
if errorlevel 1 goto :error

:: Done
echo Installation complete
goto :end

:error
echo An error occurred during the installation process

:end