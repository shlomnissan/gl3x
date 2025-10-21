from __future__ import annotations
from pathlib import Path

import xml.etree.ElementTree as ET

def element_text(el: ET.Element, default: str = "") -> str:
    if el is None or el.text is None:
        return default
    return el.text.strip()

def write_if_changed(path: Path, content: str) -> bool:
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists() and path.read_text(encoding="utf-8") == content:
        return False
    path.write_text(content, encoding="utf-8")
    return True