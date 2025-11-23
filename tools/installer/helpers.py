from __future__ import annotations

import platform
import subprocess
import sys

from pathlib import Path

def make_info(message: str):
    print(f"→ [INFO] {message}")

def make_warning(message: str):
    print(f"→ [WARNING] {message}")

def make_error(title: str, message: str | None = None):
    print(f"→ [ERROR] {title}", file=sys.stderr)
    if message: print(f"  {message}", file=sys.stderr)
    print("\n")
    sys.exit(1)

def run_command(args: list[str], cwd: Path | None = None):
    try:
        result = subprocess.run(
            args,
            cwd=str(cwd) if cwd is not None else None,
        )
    except FileNotFoundError as exc:
        make_error("Failed to run command.", str(exc))
    return result.returncode

def default_install_prefix(os_name: str) -> Path:
    if os_name == "Windows":
        return Path(r"C:\Program Files\VGLX")
    return Path("/usr/local")

def get_os():
    system = platform.system()
    if system == "Darwin": return "macOS"
    if system == "Windows": return "Windows"
    if system == "Linux": return "Linux"
    return system or "Unknown"

def split_version(s: str) -> tuple[int, ...]:
    return tuple(int(part) for part in s.split('.'))