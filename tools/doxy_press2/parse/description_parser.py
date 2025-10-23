from __future__ import annotations
from ..resolver import Resolver
from .xml_utilities import element_text
from typing import Optional, List

import xml.etree.ElementTree as ET

def _read_pieces(el: ET.Element, resolver: Optional[Resolver], strip: bool = True):
    output: List[str] = []

    def walk(node: ET.Element):
        if el is None: return
        if node.text: output.append(node.text)

        for child in node:
            tag = child.tag
            if tag == "ref":
                label = _read_pieces(child, resolver) or element_text(child)
                if resolver:
                    child_id = child.get("refid")
                    label = resolver.id_to_url_with_label(child_id, label)
                output.append(label)
            elif tag == "linebreak":
                output.append("  \n")
            elif tag == "sp":
                output.append(" ")
            elif tag == "programlisting":
                output.append(_read_program_listing(child))
            elif tag == "simplesect":
                continue
            else:
                output.append(_read_pieces(child, resolver, strip))

            if child.tail:
                output.append(child.tail)

    walk(el)
    return "".join(output).strip() if strip else "".join(output)

def _read_program_listing(listing: ET.Element, lang: str = "cpp"):
    lines: List[str] = []
    for line in listing.findall("codeline"):
        lines.append(_read_pieces(line, None, False))
    return f"\n```{lang}\n{("\n".join(lines).rstrip("\n"))}\n```\n"

def get_description(el: ET.Element, resolver: Resolver):
    brief = _read_pieces(el.find("briefdescription"), resolver)
    details = _read_pieces(el.find("detaileddescription"), resolver)

    return [brief, details]