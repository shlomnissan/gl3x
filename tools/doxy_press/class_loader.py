from __future__ import annotations

from pathlib import Path
from .content_model import (ClassDoc)
from .doxygen_markdown import element_text, render_description

import xml.etree.ElementTree as ET

def build_class_doc(refid: str, xml_dir: str | Path) -> ClassDoc:
    root = ET.parse(xml_dir / f"{refid}.xml").getroot()
    cdef = root.find("compounddef")
    if cdef is None:
        raise FileNotFoundError(f"compounddef not found in {refid}.xml")

    name = element_text(cdef.find("compoundname")).strip()
    display = name.split("::")[-1] if "::" in name else name

    doc = ClassDoc(
        id=refid,
        name=name,
        display=display,
        brief=render_description(cdef.find("briefdescription")),
        details=render_description(cdef.find("detaileddescription")),
    )

    return doc