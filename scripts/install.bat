@echo off

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

:: Configure the project
echo Running CMake configuration
cmake .. --preset "release"
if errorlevel 1 goto :error

:: Build the project
echo Building the project
cmake --build . --config Release
if errorlevel 1 goto :error

:: Install the project
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