from __future__ import annotations
from ..model import Type, VarDoc
from ..parse.xml_utilities import element_text, read_pieces
from ..resolver import Resolver

import xml.etree.ElementTree as ET

def _parse_type(el: ET.Element):
    if el is None: return

    # TODO: implement parse type

    return Type("", "")

def _initializer(el: ET.Element):
    if el is None: return

    # TODO: implement initializer

    return ""

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