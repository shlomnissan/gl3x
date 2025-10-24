from __future__ import annotations
from ..model import ClassDoc
from ..render.render_pieces import (
    render_variable
)
from ..resolver import Resolver
from typing import List

def _render_base_class(c: ClassDoc, resolver: Resolver):
    if not c.base_class_id: return ""
    t = resolver.class_id_to_url(c.base_class_id)
    return f"::: info\nDerives from {t} and inherits all public properties and methods.\n:::"

def _render_class_header(c: ClassDoc, resolver: Resolver):
    return (
        f"# {c.display}\n"
        f"<div class=\"docblock docblock-class\">"
        f"<div class=\"description\">"
        f"{c.brief}\n\n"
        f"{c.details}\n"
        f"{_render_base_class(c, resolver)}\n"
        f"</div>"
        f"</div>\n"
    )

def render_class(c: ClassDoc, resolver: Resolver):
    lines: List[str] = []

    lines += [_render_class_header(c, resolver)]

    if c.variables:
        lines += ["## Properties\n"]
        for var_doc in c.variables:
            lines += [render_variable(var_doc, resolver)]

    return "\n".join(lines)
