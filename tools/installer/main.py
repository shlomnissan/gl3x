from __future__ import annotations

import platform
import shutil
import subprocess
import sys

from pathlib import Path
from dataclasses import dataclass

from .prompts import ask_choice, ask_yes_no

INSTALLER_VERSION = "0.0.1"
MIN_CMAKE_VERSION = "3.20.0"

@dataclass
class ConfigurationOptions:
    os_name: str
    install_prefix: Path
    build_shared: bool
    build_asset_builder: bool
    build_imgui: bool

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

def default_install_prefix(os_name: str):
    if os_name == "Windows":
        return Path("C:/Program Files/vglx")
    return Path("/usr/local")

def configuration_options(os_name: str):
    default_prefix = default_install_prefix(os_name)
    install_path_choice = ask_choice(
        "\nInstallation path:",
        [f"Default path ({default_prefix})", "Custom path"]
    )
    if install_path_choice.startswith("Default"):
        install_prefix = default_prefix
    else:
        custom = input("Enter installation prefix: ").strip()
        install_prefix = Path(custom) if custom else default_prefix

    build_shared = ask_choice(
        "\nLibrary target:",
        ["Shared library (recommended)", "Static library"]
    ).startswith("Shared")

    print("\nAdditional components to install with VGLX:")
    build_asset_builder = ask_yes_no("Asset Builder CLI: generates engine-optimized assets (recommended)")
    build_imgui = ask_yes_no("ImGui: minimal UI library for tools and examples")

    components = []
    if build_asset_builder:
        components.append("asset builder")
    if build_imgui:
        components.append("imgui")
    if not components:
        components.append("none")

    print("\nSummary:")
    print(f"  OS: {os_name}")
    print(f"  Install prefix: {install_prefix}")
    print(f"  Library type: {'shared' if build_shared else 'static'}")
    print(f"  Components: {', '.join(components)}")

    if not ask_yes_no("\nProceed with installation?", default_yes=True):
        print("→ [INFO] Installation cancelled by user.\n")
        sys.exit(0)

    return ConfigurationOptions(
        os_name = os_name,
        install_prefix = install_prefix,
        build_shared = build_shared,
        build_asset_builder = build_asset_builder,
        build_imgui = build_imgui,
    )

def main():
    print()
    print(f"VGLX Installer v{INSTALLER_VERSION}")
    print("---------------------\n")

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

    print("3. Configuration Options...")
    config = configuration_options(os_name)

    print()

if __name__ == "__main__":
    main()