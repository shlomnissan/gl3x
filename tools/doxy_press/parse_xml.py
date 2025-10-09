from __future__ import annotations

from pathlib import Path
from typing import List, Optional, Dict
from .model import Inventory, Group, Class, snake_slug

import hashlib, xml.etree.ElementTree as ET

def _text(elem: Optional[ET.Element], default: str = "") -> str:
    return elem.text if elem is not None and elem.text is not None else default

def _anchor(kind: str, name: str, args: str | None) -> str:
    if kind == "function":
        sig = f"{name}{args or ''}"
        h = hashlib.sha1(sig.encode("utf-8")).hexdigest()[:8]
        return f"{kind}_{snake_slug(name)}_{h}"
    return f'{kind}_{snake_slug(name)}'

def load_inventory(xml_root: str | Path):
    xml_root = Path(xml_root)
    index = ET.parse(xml_root / "index.xml").getroot()

    inv = Inventory()
    group_refids: List[str] = []
    class_refids: List[str] = []

    # collect compund ids
    for comp in index.findall("compound"):
        kind = comp.get("kind", "")
        refid = comp.get("refid", "")
        if kind == "group":
            group_refids.append(refid)
        elif kind in ("class", "struct"):
            class_refids.append(refid)

    # load groups
    for gid in group_refids:
        g_root = ET.parse(xml_root / f"{gid}.xml").getroot()
        compounddef = g_root.find("compounddef")
        if compounddef is None:
            continue
        g_name = _text(compounddef.find("title")) or _text(compounddef.find("compoundname")) or "Group"
        group = Group(
            id=gid,
            name=g_name.strip(),
            slug=snake_slug(g_name.strip()),
            class_ids=[],
        )
        for inner in compounddef.findall("innerclass"):
            ref = inner.get("refid", "")
            if ref:
                group.class_ids.append(ref)
        inv.groups[group.id] = group

    # load classes
    for cid in class_refids:
        c_root = ET.parse(xml_root / f"{cid}.xml").getroot()
        compounddef = c_root.find("compounddef")
        if compounddef is None:
            continue
        fqname = _text(compounddef.find("compoundname")).strip()  # e.g., vglx::Camera
        display = fqname.split("::")[-1] if "::" in fqname else fqname
        cls = Class(
            id=cid,
            name=fqname,
            display=display,
            group_id=None,  # set below
        )
        inv.classes[cls.id] = cls
        for m in compounddef.findall(".//memberdef"):
            mid = m.get("id");
            kind = m.get("kind", "")
            if not mid: continue
            name = (m.findtext("name") or "").strip()
            args = (m.findtext("argsstring") or "").strip() or None
            inv.members[mid] = (cid, _anchor(kind, name, args))

    # map classes to groups using groups innerclass lists
    refid_to_group: Dict[str, str] = {}
    for g in inv.groups.values():
        for ref in g.class_ids:
            refid_to_group[ref] = g.id

    for c in inv.classes.values():
        if c.id in refid_to_group:
            c.group_id = refid_to_group[c.id]

    # ensure all classes referenced by groups actually exist
    for g in inv.groups.values():
        g.class_ids = [cid for cid in g.class_ids if cid in inv.classes]

    inv.assign_class_slugs()

    return inv