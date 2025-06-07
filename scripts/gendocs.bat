@echo off
setlocal enabledelayedexpansion

REM Exit on error

set "BUILD_DIR=%~1"
if "%BUILD_DIR%"=="" set "BUILD_DIR=build"
set "DOCS_DIR=%BUILD_DIR%\docs\html"

echo Generating Doxygen documentation

REM Ensure build directory exists and CMake is configured
if not exist "%BUILD_DIR%\Makefile" (
    if not exist "%BUILD_DIR%\build.ninja" (
        echo Configuring CMake
        cmake -S . -B "%BUILD_DIR%"
        if errorlevel 1 exit /b 1
    )
)

REM Build the Doxygen target
cmake --build "%BUILD_DIR%" --target doxygen
if errorlevel 1 exit /b 1

REM Verify output
if exist "%DOCS_DIR%\index.html" (
    echo [SUCCESS] Documentation generated at: %DOCS_DIR%\index.html
) else (
    echo [ERROR] Documentation generation failed: %DOCS_DIR%\index.html not found.
    exit /b 1
)

endlocal