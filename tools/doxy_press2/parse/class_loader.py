from __future__ import annotations
from ..model import Inventory, ClassDoc
from ..parse.description_parser import get_description
from ..resolver import Resolver
from pathlib import Path

import xml.etree.ElementTree as ET

def load_class(inventory: Inventory, id: str, xml_dir: Path, resolver: Resolver):
    root = ET.parse(xml_dir / f"{id}.xml").getroot()
    el = root.find("compounddef")
    if el is None:
        raise FileNotFoundError(f"compounddef not found in {id}.xml")

    # multiple inheritance unsupported
    base_class_id = None
    for base in el.findall("basecompoundref"):
        base_class_id = base.get("refid")
        if base_class_id: break

    [brief, details] = get_description(el, resolver)

    class_doc = ClassDoc(
        id = id,
        name = inventory.classes[id].name,
        display = inventory.classes[id].display,
        base_class_id = base_class_id,
        brief = brief,
        details = details
    )

    return class_doc