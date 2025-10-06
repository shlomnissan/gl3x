from __future__ import annotations

from typing import List, Optional
from .content_model import DocParagraph
from .resolver import Resolver

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

def collect_inlines(node: ET.Element, resolver: Optional[Resolver] = None) -> str:
    out: List[str] = []

    def walk(n: ET.Element):
        if n.text:
            out.append(n.text)

        for child in list(n):
            tag = child.tag

            if tag == "emphasis":
                inner = collect_inlines(child, resolver)
                out.append(f"*{inner}*")
            elif tag == "bold":
                inner = collect_inlines(child, resolver)
                out.append(f"**{inner}**")
            elif tag == "computeroutput":
                inner = collect_inlines(child, resolver).replace("\n", " ")
                out.append(f"`{inner}`")
            elif tag == "ref":
                label = resolver.class_link_md(child.get("refid")) if resolver else None
                if not label:
                    label = collect_inlines(child, resolver) or element_text(child)
                out.append(label)
            elif tag == "linebreak":
                out.append("  \n")
            elif tag == "programlisting":
                out.append(programlisting_to_md(child))
            elif tag == "simplesect":
                pass
            else:
                out.append(collect_inlines(child, resolver))

            if child.tail:
                out.append(child.tail)

    walk(node)

    return "".join(out).strip()

def _iter_nonparam_paras(root: ET.Element):
    result: List[ET.Element] = []

    def walk(n: ET.Element, in_param: bool = False):
        tag = n.tag

        if tag in ("parameterlist", "parameterdescription"):
            in_param = True

        if tag == "para":
            # Skip <para> that *wraps* a parameterlist, or lives under one
            if not in_param and n.find(".//parameterlist") is None:
                result.append(n)
            return  # don't descend further from this <para>

        for child in n:
            walk(child, in_param)

    if root is not None:
        walk(root, False)

    return result

def render_description(
        desc: Optional[ET.Element],
        include_params: bool = False,
        resolver: Optional[Resolver] = None
) -> List[DocParagraph]:
    if desc is None:
        return []

    paras: List[DocParagraph] = []

    if include_params:
        for para in desc.findall(".//para"):
            md = collect_inlines(para, resolver)
            if md: paras.append(DocParagraph(md=md))
    else:
        for para in _iter_nonparam_paras(desc):
            md = collect_inlines(para, resolver)
            if md: paras.append(DocParagraph(md=md))

    return paras