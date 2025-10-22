from __future__ import annotations
from ..model import Inventory, ClassDoc
from ..parse.xml_utilities import element_text
from ..parse.description_parser import get_description
from pathlib import Path

import xml.etree.ElementTree as ET

def load_class(inventory: Inventory, id: str, xml_dir: Path):
    root = ET.parse(xml_dir / f"{id}.xml").getroot()
    el = root.find("compounddef")
    if el is None:
        raise FileNotFoundError(f"compounddef not found in {id}.xml")

    # multiple inheritance unsupported
    base_class = el.find("basecompoundref")
    base_class_id = base_class.get("refid") if base_class else None

    [brief, details] = get_description(el)

    class_doc = ClassDoc(
        id = id,
        name = inventory.classes[id].name,
        display = inventory.classes[id].display,
        base_class_id = base_class_id,
        brief = brief,
        details = details
    )

    return class_doc