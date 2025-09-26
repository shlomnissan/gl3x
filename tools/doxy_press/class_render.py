from __future__ import annotations

from html import escape
from typing import List
from .content_model import ClassDoc, VarDoc, FunctionDoc, DocParagraph, TypeRef

def _para(s: str) -> str: return s.strip()

def _first(paras): return _para(paras[0].md) if paras else ""

def _join_paragraphs(paras: List[DocParagraph]) -> str:
    return ("\n\n".join(p.md.strip() for p in paras if p.md.strip())).strip()

def _inline_md_to_html(text: str) -> str:
    # minimal: convert `code` to <code>, escape the rest
    from html import escape as _esc
    import re
    parts = re.split(r"(`[^`]*`)", text)
    html = []
    for p in parts:
        if p.startswith("`") and p.endswith("`"):
            html.append(f"<code>{_esc(p[1:-1], quote=False)}</code>")
        else:
            html.append(_esc(p, quote=False))
    return "".join(html)

def _render_property(prop: VarDoc):
    name_str = prop.name
    name_html = escape(name_str, quote=False)
    type_str = prop.type.as_text()
    type_html = escape(type_str, quote=False)
    default_val = f'{{ {prop.initializer} }}' if prop.initializer else ""
    desc = _inline_md_to_html(_join_paragraphs(prop.brief)) if prop.brief else ""

    code_block = (
        f'  ```cpp\n'
        f'  {type_str} {name_str} {default_val}\n'
        f'  ```\n'
    )

    return (
        f'<div class="property">\n'
        f'  <div class="definition">\n\n'
        f'  ### <span class="name">{name_html}</span> <span class="type">{type_html}</span>\n'
        f'{code_block}'
        f'  </div>\n'
        f'  <div class="description">\n'
        f'    {desc}\n'
        f'  </div>\n'
        '</div>'
    )

def _render_function(func: FunctionDoc):

    return

def render_class(doc: ClassDoc) -> str:
    lines: List[str] = []

    lines.append(f"# {doc.display}\n\n")

    if doc.brief:
        lines.append(_join_paragraphs(doc.brief))

    if doc.details:
        lines.append(_join_paragraphs(doc.details))

    if doc.constructors:
        lines += ["## Constructors", ""]
        for c in doc.constructors:
            lines += [f"### `{c.name}()`"]
            lines.append(_join_paragraphs(c.brief))
            lines.append("")


    if doc.variables:
        lines += ["## Properties", ""]
        for v in doc.variables:
            lines.append(_render_property(v))
            lines.append("")

    if doc.functions:
        lines += ["## Functions", ""]
        for f in doc.functions:
            lines += [f"### `{f.name}()`"]
            fb = _first(f.brief)
            if fb: lines += [f"  - {fb}"]
        lines.append("")

    out = "\n".join(lines).rstrip() + "\n"

    return out