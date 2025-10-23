from __future__ import annotations
from ..model import ClassDoc
from ..resolver import Resolver
from typing import List

def _render_class_header(cls: ClassDoc, resolver: Resolver):
    lines: List[str] = []
    lines.append(f"# {cls.display}\n\n")
    lines.append("<div class=\"docblock docblock-class\"><div class=\"description\">\n")

    lines.append(cls.brief)
    lines.append("\n\n")
    lines.append(cls.details)
    lines.append("\n\n")

    if cls.base_class_id:
        label = resolver.class_id_to_url(cls.base_class_id)
        lines += ["::: info\n"]
        lines += [f"Derives from {label} and inherits all public properties and methods.\n"]
        lines += [":::\n"]

    lines.append("</div></div>")
    return "".join(lines)

def render_class(cls: ClassDoc, resolver: Resolver):
    output = _render_class_header(cls, resolver)

    return output
