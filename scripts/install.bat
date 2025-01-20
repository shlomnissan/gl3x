@echo off

:: Set default triplet value
set "triplet=x64-windows-static-md"

:: Check if a triplet is provided as an argument
if not "%~1"=="" set "triplet=%~1"

:: Determine the script's location
set "script_dir=%~dp0"

:: Move to the root directory (parent of the "scripts" folder)
cd /d "%script_dir%.."

:: Check if the "release" folder exists, and remove it if it does
if exist release (
    echo Removing existing "release" folder
    rmdir /s /q release
    if errorlevel 1 goto :error
)

:: Create the "release" folder
echo Creating "release" folder
mkdir release
cd release
if errorlevel 1 goto :error

:: Configure
echo Running CMake configuration with triplet: %triplet%
cmake .. --preset "release" -DVCPKG_TARGET_TRIPLET=%triplet%
if errorlevel 1 goto :error

:: Build
echo Building the project
cmake --build . --config Release
if errorlevel 1 goto :error

:: Install
echo Installing the project
cmake --install .
if errorlevel 1 goto :error

:: Completion message
echo Installation complete
goto :end

:: Error message
:error
echo An error occurred during the installation process

:end