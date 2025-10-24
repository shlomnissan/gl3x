from __future__ import annotations
from ..model import VarDoc, Type
from ..resolver import Resolver
from html import escape

def _t_resolved(t: Type, resolver: Resolver):
    output = ""
    for p in t.parts:
        output += resolver.id_to_url_with_label(p.id, p.text) if p.id else p.text
    return output

def _t_str(t: Type):
    return "".join(p.text.strip() for p in t.parts)

def render_variable(v: VarDoc, resolver: Resolver):
    return (
        f"<div class=\"docblock\">"
        f"<div class=\"definition\">\n\n"
        f"### <span class=\"name\">{escape(v.name)}</span> "
        f"<span class=\"type\">{_t_resolved(v.type, resolver)}</span>"
        f"{resolver.member_id_to_anchor(v.id)}\n"
        f"</div>"
        f"<div class=\"description\">\n\n"
        f"{v.brief} {v.details}\n"
        f"```cpp\n{_t_str(v.type)} {v.name} {{{v.init_value}}}\n```\n"
        f"</div>"
        f"</div>"
    )