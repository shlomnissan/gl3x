from __future__ import annotations

from pathlib import Path
from typing import Dict
from .doxygen_markdown import element_text, render_description, collect_inlines
from .resolver import Resolver
from .content_model import (
    ClassDoc,
    EnumDoc,
    EnumValueDoc,
    VarDoc,
    FunctionDoc,
    TypeRef,
    TypePart,
    ParamDoc
)

import re
import xml.etree.ElementTree as ET

def _bool_attr(e: ET.Element, name: str) -> bool:
    return (e.get(name) or "").lower() in ("yes", "true", "1")

def _parse_type(t: ET.Element | None) -> TypeRef:
    tr = TypeRef()
    if t is None: return tr
    if t.text: tr.parts.append(TypePart(text=t.text))
    for ch in list(t):
        if ch.tag == "ref":
            tr.parts.append(TypePart(text=(ch.text or "").strip(), refid=ch.get("refid")))
        else:
            tr.parts.append(TypePart(text="".join(ch.itertext())))
        if ch.tail:
            tr.parts.append(TypePart(text=ch.tail))

    # normalize whitespace within each part
    for p in tr.parts:
        p.text = " ".join(p.text.split())

    # noise filter: drop specifiers that sometimes leak into <type>
    tr.parts = [p for p in tr.parts if p.text not in ("override", "=0")]

    return tr

def _initializer_display(init: ET.Element | None) -> str | None:
    if init is None: return None

    s = collect_inlines(init).strip()
    s = re.sub(r'^\s*=\s*', '', s)

    while True:
        m = re.match(r'^\{\s*(.*)\s*\}$', s)
        if not m:
            break
        s = m.group(1).strip()

    s = re.sub(r'\(\s*\)', '()', s)
    s = s.rstrip(';')
    s = re.sub(r'\s+', ' ', s).strip()
    return s or None

def _parse_variable(m: ET.Element) -> VarDoc:
    return VarDoc(
        id=m.get("id",""),
        name=element_text(m.find("name")).strip(),
        prot=m.get("prot", "public"),
        static=_bool_attr(m, "static"),
        type=_parse_type(m.find("type")),
        initializer=_initializer_display(m.find("initializer")),
        brief=render_description(m.find("briefdescription")),
    )

def _parse_enum_value(m: ET.Element) -> EnumValueDoc:
    return EnumValueDoc(
        name=element_text(m.find("name")).strip(),
        brief=render_description(m.find("briefdescription")),
    )

def _parse_enum(m: ET.Element) -> EnumDoc:
    name = element_text(m.find("name")).strip()
    display = name.split("::")[-1] if "::" in name else name

    values = []
    for v in m.findall("enumvalue"):
        values.append(_parse_enum_value(v))

    return EnumDoc(
        id=m.get("id",""),
        name=name,
        display=display,
        scoped=_bool_attr(m, "scoped") or _bool_attr(m, "strong"),
        brief=render_description(m.find("briefdescription")),
        details=render_description(m.find("detaileddescription")),
        values=values,
    )

def _is_ctor(m: ET.Element, cname: str) -> bool:
    func_name = element_text(m.find("name")).strip()
    return_str = _parse_type(m.find("type")).as_text()
    return func_name == cname or return_str == ""

def _is_user_ctor(m: ET.Element, cname: str) -> bool:
    if not _is_ctor(m, cname):
        return False

    name = m.findtext("name", "")
    if name.startswith("~"):
        return False

    definition = m.findtext("definition", "") or ""
    if "=default" in definition or "=delete" in definition:
        return False

    argsstring = m.findtext("argsstring", "") or ""
    if "=default" in argsstring or "=delete" in argsstring:
        return False

    return True

def _is_user_func(m: ET.Element) -> bool:
    definition = m.findtext("definition", "") or ""
    if "=default" in definition or "=delete" in definition:
        return False

    argsstring = m.findtext("argsstring", "") or ""
    if "=default" in argsstring or "=delete" in argsstring:
        return False

    return True

def _param_briefs_map(m: ET.Element) -> Dict[str, str]:
    out: Dict[str, str] = {}

    detailed = m.find("detaileddescription")
    if detailed is None:
        return out

    for item in detailed.findall(".//parameterlist[@kind='param']/parameteritem"):
        names = [
            (n.text or "").strip()
            for n in item.findall("./parameternamelist/parametername")
        ]

        pdesc_el = item.find("parameterdescription")
        pdesc = render_description(pdesc_el, True) if pdesc_el is not None else []
        brief = pdesc[0].md.strip() if pdesc else ""

        for name in names:
            if name:
                out[name] = brief[0].lower() + brief[1:]

    return out

def _parse_function(m: ET.Element) -> FunctionDoc:
    definition = element_text(m.find("definition"))
    args = element_text(m.find("argsstring"))

    params = []
    for p in m.findall("param"):
        params.append(
            ParamDoc(
                name=element_text(p.find("declname")).strip()
                   or element_text(p.find("defname")).strip(),
                type=_parse_type(p.find("type")),
                default=(element_text(p.find("defval")).strip() or None),
            )
        )

    param_briefs = _param_briefs_map(m)
    for p in params:
        if p.name and p.name in param_briefs:
            p.desc = param_briefs[p.name]

    return FunctionDoc(
        id=m.get("id", ""),
        name=element_text(m.find("name")).strip(),
        prot=m.get("prot","public"),
        static=_bool_attr(m, "static"),
        virt=m.get("virt"),
        return_type=_parse_type(m.find("type")),
        signature=(definition + args).strip(),
        params=params,
        brief=render_description(m.find("briefdescription")),
        details=render_description(m.find("detaileddescription")),
    )

def build_class_doc(refid: str, xml_dir: str | Path, resolver: Resolver) -> ClassDoc:
    root = ET.parse(xml_dir / f"{refid}.xml").getroot()
    cdef = root.find("compounddef")
    if cdef is None:
        raise FileNotFoundError(f"compounddef not found in {refid}.xml")

    name = element_text(cdef.find("compoundname")).strip()
    display = name.split("::")[-1] if "::" in name else name

    base_ids = []
    for base in cdef.findall("basecompoundref"):
        if base.get("refid"): base_ids.append(base.get("refid"))

    doc = ClassDoc(
        id=refid,
        name=name,
        display=display,
        base_ids=base_ids,
        brief=render_description(cdef.find("briefdescription"), None, resolver),
        details=render_description(cdef.find("detaileddescription"), None, resolver),
    )

    for sec in cdef.findall("sectiondef"):
        for m in sec.findall("memberdef"):
            if m.get("prot") != "public":
                continue
            kind = m.get("kind")

            if kind == "variable":
                doc.variables.append(_parse_variable(m))

            if kind == "function":
                if _is_ctor(m, name):
                    if _is_user_ctor(m, name):
                        doc.constructors.append(_parse_function(m))
                else:
                    if _is_user_func(m):
                        doc.functions.append(_parse_function(m))

            if kind == "enum":
                doc.enums.append(_parse_enum(m))

    return doc