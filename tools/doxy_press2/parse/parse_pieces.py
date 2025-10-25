from __future__ import annotations
from ..model import (
    EnumDoc,
    Type,
    TypePart,
    TypedefDoc,
    VarDoc,
)
from ..parse.xml_utilities import element_text, read_pieces, bool_attr
from ..resolver import Resolver
from typing import Dict

import re, xml.etree.ElementTree as ET

def _parse_type(el: ET.Element):
    output = Type()
    if el is None: return output

    if el.text:
        output.parts.append(TypePart(text = el.text.strip()))

    for child in el:
        if child.tag == "ref":
            text = element_text(child)
            cid = child.get("refid")
            output.parts.append(TypePart(text = text, id = cid))
        if child.tail:
            output.parts.append(TypePart(text = child.tail))

    return output

def _initializer(el: ET.Element):
    if el is None: return

    output = read_pieces(el, None)
    match = re.match(r'^\{\s*(.*)\s*\}$', output)
    if match:
        output = match.group(1).strip() or ""

    output = re.sub(r'^\s*=\s*', '', output)
    if output == "" or output == "{}":
        return None

    return output

def parse_description(el: ET.Element, resolver: Resolver):
    brief = read_pieces(el.find("briefdescription"), resolver)
    details = read_pieces(el.find("detaileddescription"), resolver)
    return [brief, details]

def parse_variable(el: ET.Element, resolver: Resolver):
    [brief, details] = parse_description(el, resolver)
    location = el.find("location")
    return VarDoc (
        id = el.get("id"),
        name = element_text(el.find("name")),
        type = _parse_type(el.find("type")),
        init_value = _initializer(el.find("initializer")),
        brief = brief,
        details = details,
        line = location.get("line")
    )

def parse_enum(el: ET.Element, resolver: Resolver):
    [brief, details] = parse_description(el, resolver)

    values: Dict[str, str] = {}
    for v in el.findall("enumvalue"):
        name = element_text(v.find("name"))
        vbrief = read_pieces(el.find("briefdescription"), resolver)
        values[name] = vbrief

    return EnumDoc(
        id = el.get("id"),
        name = element_text(el.find("name")),
        scoped = bool_attr(el, "scoped"),
        brief = brief,
        details = details,
        values = values
    )

def parse_typedef(el: ET.Element, resolver: Resolver):
    [brief, details] = parse_description(el, resolver)
    return TypedefDoc(
        id = el.get("id"),
        name = element_text(el.find("name")),
        definition = element_text(el.find("definition")),
        type = _parse_type(el.find("type")),
        brief = brief,
        details = details
    )