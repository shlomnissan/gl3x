from __future__ import annotations
from ..model import Type, VarDoc
from ..parse.xml_utilities import element_text
from ..parse.description_parser import get_description
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

def parse_variable(el: ET.Element, resolver: Resolver):
    [brief, details] = get_description(el, resolver)
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