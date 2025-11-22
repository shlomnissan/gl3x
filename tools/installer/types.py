from __future__ import annotations

from dataclasses import dataclass

@dataclass
class ConfigurationOptions:
    os_name: str
    build_shared: bool
    build_asset_builder: bool
    build_imgui: bool