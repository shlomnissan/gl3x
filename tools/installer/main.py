from __future__ import annotations

import platform
import shutil
import subprocess
import sys

from pathlib import Path

MIN_CMAKE_VERSION = "3.20.0"

def make_error(title: str, message: str | None = None):
    print(f"→ [ERROR] {title}", file=sys.stderr)
    if message: print(f"  {message}", file=sys.stderr)
    print("\n")
    sys.exit(1)

def get_os():
    system = platform.system()
    if system == "Darwin": return "macOS"
    if system == "Windows": return "Windows"
    if system == "Linux": return "Linux"
    return system or "Unknown"

def get_cmake_version():
    cmake_path = shutil.which("cmake")
    if not cmake_path:
        make_error(
            "CMake was not found on your PATH.",
            "Please install CMake 3.20 or newer and try again."
        )

    output = subprocess.run(
        [cmake_path, "--version"],
        capture_output = True,
        text = True,
        check = True,
    )

    line = output.stdout.splitlines()[0] if output.stdout else ""
    tokens = line.strip().split()
    return tokens[-1] if tokens else ""

def split_version(s: str) -> tuple[int, ...]:
    return tuple(int(part) for part in s.split('.'))

def main():
    print("\nVGLX Installer")
    print("--------------\n")

    root_dir = Path(__file__).resolve().parents[2]
    if not (root_dir / "CMakeLists.txt").exists():
        make_error(
            f"Could not find CMakeLists.txt in {root_dir}.",
            "Please run this installer from within the VGLX repository."
        )

    print("1. Checking Operating System...")
    os_name = get_os()
    if os_name == "Unknown":
        make_error(
            "Unkown operating system.",
            "VGLX currently supports Windows, macOS and Linux."
        )

    print("2. Checking CMake...")
    cmake_version = get_cmake_version()
    if split_version(cmake_version) < split_version(MIN_CMAKE_VERSION):
       make_error(
            f"CMake {MIN_CMAKE_VERSION} or newer is required.",
            f"Found version {cmake_version}"
        )

    print("\n")

if __name__ == "__main__":
    main()