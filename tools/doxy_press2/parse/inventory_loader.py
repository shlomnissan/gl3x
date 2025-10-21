from __future__ import annotations
from ..model import Inventory, Group, Class
from ..strings import slugify, remove_qualifications
from .xml_utilities import element_text
from pathlib import Path
from typing import  List

import xml.etree.ElementTree as ET

def _load_groups(inventory: Inventory, group_ids: List[str], xml_root: Path):
    for gid in group_ids:
        root = ET.parse(xml_root / f"{gid}.xml").getroot()
        el = root.find("compounddef")
        if el is None: return

        name = element_text(el.find("title"))
        group = Group(
            id = gid,
            name = name,
            slug = slugify(name),
            class_ids = []
        )

        for inner_class in el.findall("innerclass"):
            ref = inner_class.get("refid")
            if ref is None: continue
            group.class_ids.append(ref)
            inventory.class_to_group[ref] = group.id

        inventory.groups[group.id] = group

def _load_classes(inventory: Inventory, class_ids: List[str], xml_root: Path):
    for cid in class_ids:
        root = ET.parse(xml_root / f"{cid}.xml").getroot()
        el = root.find("compounddef")
        if el is None: return

        name = element_text(el.find("compoundname"))
        cls = Class(
            id = cid,
            name = name,
            display = remove_qualifications(name),
            group_id = inventory.class_to_group.get(cid, "__ungrouped__"),
            slug = slugify(remove_qualifications(name))
        )

        inventory.classes[cls.id] = cls

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

    _load_groups(inventory, group_ids, xml_root)
    _load_classes(inventory, class_ids, xml_root)

    return inventory