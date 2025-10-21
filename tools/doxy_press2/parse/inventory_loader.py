from __future__ import annotations
from ..model import Inventory
from pathlib import Path
from typing import  List

import xml.etree.ElementTree as ET

def _load_groups(inventory: Inventory, group_ids: List[str]):
    # load groups
    return

def _load_classes(inventory: Inventory, class_ids: List[str]):
    # load classes
    return

def _load_class_members(inventory: Inventory, class_el: ET.Element):
    # load class members
    return

def load_inventory(xml_root: Path):
    inventory = Inventory()
    index = ET.parse(xml_root / "index.xml").getroot()

    group_ids: List[str] = []
    class_ids: List[str] = []
    for el in index.findall("compound"):
        kind = el.get("kind", "")
        refid = el.get("refid", "")
        if kind == "group":
            group_ids.append(refid)
        elif kind in ("class", "struct"):
            class_ids.append(refid)

    _load_groups(inventory, group_ids)
    _load_classes(inventory, class_ids)

    return inventory