from __future__ import annotations
from ..model import Inventory, Group, Class, Member
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
            group_id = inventory.class_to_group.get(cid),
            slug = slugify(remove_qualifications(name))
        )

        _load_class_members(inventory, el)

        inventory.classes[cls.id] = cls

def _load_class_members(inventory: Inventory, el: ET.Element):
    cid = el.get("refid")

    for inner_class in el.findall("innerclass"):
        mid = inner_class.get("refid")
        if mid is None: continue

        inventory.members[mid] = Member(
            id = mid,
            parent_id = cid,
            name = element_text(inner_class),
            kind = "struct",
            args = None
        )

    for member in el.findall(".//memberdef"):
        mid = member.get("id")
        if mid is None: continue

        args = member.findtext("argsstring")
        inventory.members[mid] = Member(
            id = mid,
            parent_id = cid,
            name = member.findtext("name").strip(),
            kind = member.get("kind"),
            args = args.strip() if args else None
        )

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