from __future__ import annotations
from ..model import (
    EnumDoc,
    FunctionDoc,
    ParamDoc,
    Type,
    TypePart,
    TypedefDoc,
    VarDoc,
)
from ..parse.xml_utilities import element_text, read_pieces, bool_attr
from ..strings import remove_first_qualification
from ..resolver import Resolver
from typing import Dict

import re, xml.etree.ElementTree as ET

def _parse_type(el: ET.Element):
    output = Type()
    if el is None: return output

    if el.text:
        output.parts.append(TypePart(text = element_text(el)))

    for child in el:
        if child.tag == "ref":
            text = element_text(child)
            cid = child.get("refid")
            output.parts.append(TypePart(text = text, id = cid))
        if child.tail:
            output.parts.append(TypePart(text = child.tail.strip()))

    # noise filter: drop specifiers
    output.parts = [p for p in output.parts if p.text not in ("override", "=0")]

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

def _function_param_brief_map(el: ET.Element, resolver: Resolver):
    output: Dict[str, str] = {}

    details = el.find("detaileddescription")
    if details is None:
        return output

    for param in details.findall(".//parameterlist[@kind='param']/parameteritem"):
        name = element_text(param.find("./parameternamelist/parametername"))
        brief = read_pieces(param.find("parameterdescription"), resolver)
        output[name] = brief

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

def parse_function(el: ET.Element, resolver: Resolver):
    [brief, details] = parse_description(el, resolver)
    name = element_text(el.find("name"))
    ret_type = el.find(".//simplesect[@kind='return']/para") or el.find("type")
    if bool_attr(el, "static"):
        name = remove_first_qualification(element_text(el.find("qualifiedname")))

    params = []
    param_to_brief = _function_param_brief_map(el, resolver)
    for param in el.findall("param"):
        pname = element_text(param.find("declname"))
        params.append(
            ParamDoc(
                name = pname,
                type = _parse_type(param.find("type")),
                brief = param_to_brief.get(pname) or "",
                init_value = element_text(param.find("defval"))
            )
        )

    return FunctionDoc(
        id = el.get("id"),
        name = name,
        definition = el.find("definition").text + element_text(el.find("argsstring")),
        type = _parse_type(ret_type),
        virtual = el.get("virt"),
        brief = brief,
        details = details,
        params = params
    )

def parse_enum(el: ET.Element, resolver: Resolver):
    [brief, details] = parse_description(el, resolver)

    values: Dict[str, str] = {}
    for v in el.findall("enumvalue"):
        name = element_text(v.find("name"))
        vbrief = read_pieces(v.find("briefdescription"), resolver)
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