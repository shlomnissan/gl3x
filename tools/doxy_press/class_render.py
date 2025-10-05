from __future__ import annotations

from html import escape
from typing import List
from .model import Inventory, slugify
from .content_model import (
    ClassDoc,
    EnumDoc,
    VarDoc,
    FunctionDoc,
    DocParagraph,
)

def _escape_md(name: str) -> str:
    return (
        name.replace("[", r"\[")
            .replace("]", r"\]")
            .replace("(", r"\(")
            .replace(")", r"\)")
    )

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
        f'<div class="docblock">\n'
        f'  <div class="definition">\n\n'
        f'  ### <span class="name">{name_html}</span> <span class="type">{type_html}</span>\n'
        f'{code_block}'
        f'  </div>\n'
        f'  <div class="description">\n'
        f'    {desc}\n'
        f'  </div>\n'
        f'</div>'
    )

def _render_enum(enum: EnumDoc):
    if len(enum.values) == 0: return

    enum_values = f'|Value|Description|\n'
    enum_values += f'|---|---|\n'
    for value in enum.values:
        brief = _inline_md_to_html(_join_paragraphs(value.brief)) if value.brief else ""
        enum_values += f'| <span class="type">{value.name}</span> | {brief}\n'

    brief = _inline_md_to_html(_join_paragraphs(enum.brief)) if enum.brief else ""
    scoped = '<Badge type="info" text="scoped" />' if enum.scoped else ""

    return (
        f'<div class="docblock">\n'
        f'  <div class="definition">\n\n'
        f'### <span class="name">{enum.display}</span> {scoped}\n'
        f'  </div>\n'
        f'  <div class="description">\n'
        f'    {brief}\n\n'
        f'{enum_values}\n'
        f'  </div>\n'
        f'</div>\n\n'
    )


def _render_function(func: FunctionDoc):
    name_str = _escape_md(func.name)
    brief = _inline_md_to_html(_join_paragraphs(func.brief)) if func.brief else ""
    description = _inline_md_to_html(_join_paragraphs(func.details)) if func.details else ""
    ret = escape(func.return_type.as_text(), quote=False)

    params_list = ""
    if func.params:
        params_list += f'<ul class="params">\n'
        for param in func.params:
            pname = param.name
            pdesc = param.desc
            params_list += f'<li><span class="name">{pname}</span> {pdesc}</li>\n'
        params_list += f'</ul>\n'

    return (
        f'<div class="docblock">\n'
        f'  <div class="definition">\n\n'
        f'### <span class="name">{name_str}()</span> <span class="type">{ret}</span>\n\n'
        f'  </div>\n\n'
        f'```cpp\n'
        f'{func.signature}\n'
        f'```\n'
        f'  {params_list}\n'
        f'  <div class="description">\n'
        f'    {brief} {description}\n'
        f'  </div>\n'
        f'</div>\n\n'
    )

def render_class(inv: Inventory, doc: ClassDoc) -> str:
    lines: List[str] = []

    lines.append(f"# {doc.display}\n\n")

    if doc.brief:
        lines.append(_join_paragraphs(doc.brief))

    if doc.details:
        lines.append("")
        lines.append(_join_paragraphs(doc.details))

    if len(doc.base_ids) > 0:
        base = inv.classes[doc.base_ids[0]]
        if base:
            group = inv.groups[base.group_id]
            lines.append("")
            lines += [f'Derives from [{base.display}](/reference/{group.slug}/{base.slug}); ']
            lines += [f'inherits all unlisted properties and methods.']

    if doc.constructors:
        lines += ["## Constructors", ""]
        for c in doc.constructors:
            lines.append(_render_function(c))
        lines.append("")

    if doc.enums:
        lines += ["## Enumerations"]
        for e in doc.enums:
            lines.append(_render_enum(e))
        lines.append("")

    if doc.variables:
        lines += ["## Properties", ""]
        for v in doc.variables:
            lines.append(_render_property(v))
        lines.append("")

    if doc.functions:
        lines += ["## Functions", ""]
        for f in doc.functions:
            lines.append(_render_function(f))
        lines.append("")

    out = "\n".join(lines).rstrip() + "\n"

    return out