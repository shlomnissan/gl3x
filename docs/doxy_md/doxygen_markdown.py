from __future__ import annotations

from typing import List, Optional
from .content_model import DocParagraph

import xml.etree.ElementTree as ET

def element_text(elem: Optional[ET.Element]) -> str:
    return (elem.text or "") if elem is not None else ""

def programlisting_to_md(listing: ET.Element, fence_lang: str = "cpp") -> str:
    lines: list[str] = []

    def build_line(cl: ET.Element) -> str:
        pieces: list[str] = []

        def walk(n: ET.Element):
            if n.text:
                pieces.append(n.text)

            for child in list(n):
                tag = child.tag

                if tag == "sp":
                    pieces.append(" ")
                elif tag == "highlight":
                    walk(child)
                elif tag == "ref":
                    if child.text:
                        pieces.append(child.text)
                    for g in list(child):
                        walk(g)
                elif tag == "linebreak":
                    pieces.append("\n")
                else:
                    walk(child)

                if child.tail:
                    pieces.append(child.tail)

        walk(cl)

        return "".join(pieces)

    for codeline in listing.findall("codeline"):
        lines.append(build_line(codeline))

    code = "\n".join(lines).rstrip("\n")
    return f"\n```{fence_lang}\n{code}\n```\n"

def collect_inlines(node: ET.Element) -> str:
    out: List[str] = []

    def walk(n: ET.Element):
        if n.text:
            out.append(n.text)

        for child in list(n):
            tag = child.tag

            if tag == "emphasis":
                inner = collect_inlines(child)
                out.append(f"*{inner}*")
            elif tag == "bold":
                inner = collect_inlines(child)
                out.append(f"**{inner}**")
            elif tag == "computeroutput":
                inner = collect_inlines(child).replace("\n", " ")
                out.append(f"`{inner}`")
            elif tag == "ref":
                label = collect_inlines(child) or element_text(child)
                out.append(label)
            elif tag == "linebreak":
                out.append("  \n")
            elif tag == "programlisting":
                out.append(programlisting_to_md(child))
            elif tag == "simplesect":
                pass
            else:
                out.append(collect_inlines(child))

            if child.tail:
                out.append(child.tail)

    walk(node)

    return "".join(out).strip()

def render_description(desc: Optional[ET.Element]) -> List[DocParagraph]:
    if desc is None:
        return []

    paras: List[DocParagraph] = []

    # doxygen wraps text in <para> nodes inside brief/detailed description
    for para in desc.findall(".//para"):
        md = collect_inlines(para)
        if md:
            paras.append(DocParagraph(md=md))

    return paras