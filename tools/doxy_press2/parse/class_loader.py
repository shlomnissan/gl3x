from __future__ import annotations
from pathlib import Path

import xml.etree.ElementTree as ET

def load_class(id: str, xml_dir: Path):
    root = ET.parse(xml_dir / f"{id}.xml").getroot()
    el = root.find("compounddef")
    if el is None:
        raise FileNotFoundError(f"compounddef not found in {id}.xml")

    # TODO: implement