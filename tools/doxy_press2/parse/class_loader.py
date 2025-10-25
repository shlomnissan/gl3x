from __future__ import annotations
from ..model import Inventory, ClassDoc
from ..parse.parse_pieces import (
    parse_description,
    parse_enum,
    parse_typedef,
    parse_variable,
)
from ..resolver import Resolver
from pathlib import Path

import xml.etree.ElementTree as ET

def load_class(inventory: Inventory, id: str, xml_dir: Path, resolver: Resolver, sort_variables = False):
    root = ET.parse(xml_dir / f"{id}.xml").getroot()
    el = root.find("compounddef")
    if el is None:
        raise FileNotFoundError(f"compounddef not found in {id}.xml")

    # multiple inheritance unsupported
    base_class_id = None
    for base in el.findall("basecompoundref"):
        base_class_id = base.get("refid")
        if base_class_id: break

    [brief, details] = parse_description(el, resolver)

    class_doc = ClassDoc(
        id = id,
        name = inventory.classes[id].name,
        display = inventory.classes[id].display,
        base_class_id = base_class_id,
        brief = brief,
        details = details
    )

    for inner_class in el.findall("innerclass"):
        inner_class_id = inner_class.get("refid")
        if inner_class_id:
            class_doc.inner_classes.append(
                load_class(
                    inventory,
                    inner_class_id,
                    xml_dir,
                    resolver,
                    True
                )
            )

    for section in el.findall("sectiondef"):
        for member in section.findall("memberdef"):
            # skip non-public members
            if member.get("prot") != "public":
                continue

            kind = member.get("kind")
            if kind == "variable":
                class_doc.variables.append(parse_variable(member, resolver))
            if kind == "enum":
                class_doc.enums.append(parse_enum(member, resolver))
            if kind == "typedef":
                class_doc.typedefs.append(parse_typedef(member, resolver))

    if sort_variables:
        class_doc.variables.sort(key=lambda v: v.line)

    return class_doc