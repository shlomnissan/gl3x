from __future__ import annotations

import xml.etree.ElementTree as ET

def element_text(el: ET.Element, default: str = "") -> str:
    if el is None or el.text is None:
        return default
    return el.text.strip()