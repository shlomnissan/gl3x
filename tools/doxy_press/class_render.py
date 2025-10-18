from __future__ import annotations

from html import escape
from typing import List
from .resolver import Resolver
from .content_model import (
    ClassDoc,
    DocParagraph,
    EnumDoc,
    FunctionDoc,
    TypeDefDoc,
    VarDoc,
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

def _render_property(prop: VarDoc, resolver: Resolver):
    name_str = prop.name
    name_html = escape(name_str, quote=False)
    anchor = resolver.member_anchor(prop.id)
    type_raw = prop.type.as_text()
    type_resolved = escape(prop.type.as_resolved_text(resolver), quote=False)
    default_val = f'{{ {prop.initializer} }}' if prop.initializer else ""
    desc = _inline_md_to_html(_join_paragraphs(prop.brief)) if prop.brief else ""

    code_block = (
        f'  ```cpp\n'
        f'  {type_raw} {name_str} {default_val}\n'
        f'  ```\n'
    )

    return (
        f'<div class="docblock">\n'
        f'  <div class="definition">\n\n'
        f'  ### <span class="name">{name_html}</span> <span class="type">{type_resolved}</span> {anchor}\n'
        f'{code_block}'
        f'  </div>\n'
        f'  <div class="description">\n\n'
        f'{desc}\n'
        f'  </div>\n'
        f'</div>'
    )

def _render_enum(enum: EnumDoc, resolver: Resolver):
    if len(enum.values) == 0: return

    enum_values = '|Value|Description|\n'
    enum_values += '|---|---|\n'
    for value in enum.values:
        brief = _inline_md_to_html(_join_paragraphs(value.brief)) if value.brief else ""
        enum_values += f'| <span class="type">{value.name}</span> | {brief}\n'

    anchor = resolver.member_anchor(enum.id)
    brief = _inline_md_to_html(_join_paragraphs(enum.brief)) if enum.brief else ""
    tag = "scoped enum" if enum.scoped else "enum"
    badge = f'<Badge type="info" text="{tag}" />'

    return (
        f'<div class="docblock">\n'
        f'  <div class="definition">\n\n'
        f'### <span class="name">{enum.name}</span> {badge} {anchor}\n'
        f'  </div>\n'
        f'  <div class="description">\n\n'
        f'{brief}\n\n'
        f'{enum_values}\n'
        f'  </div>\n'
        f'</div>\n\n'
    )

def _render_typedef(typedef: TypeDefDoc, resolver: Resolver):
    anchor = resolver.member_anchor(typedef.id)
    badge = '<Badge type="info" text="typedef" />'
    brief = _inline_md_to_html(_join_paragraphs(typedef.brief))
    description = _inline_md_to_html(_join_paragraphs(typedef.details))

    return (
        f'<div class="docblock inner-class">\n'
        f'<div class="definition">\n\n'
        f'### <span class="name">{typedef.display}</span> {badge} {anchor}\n'
        f'</div>\n\n'
        f'```cpp\n{typedef.definition}\n```\n'
        f'<div class="description">\n\n'
        f'{brief}\n\n'
        f'{description}\n\n'
        f'</div>\n'
        f'</div>\n\n'
    )

def _render_inner_class(inner_class: ClassDoc, resolver: Resolver):
    member_values = '|Member|Description|\n'
    member_values += '|---|---|\n'
    for var in inner_class.variables:
        brief = _inline_md_to_html(_join_paragraphs(var.brief)) if var.brief else ""
        vtype = escape(var.type.as_resolved_text(resolver), quote=False)
        member_values += f'| <span class="type">{var.name}</span>'
        member_values += f' <span class="inner-type">{vtype}</span>'
        member_values += f'| {brief}\n'

    brief = _inline_md_to_html(_join_paragraphs(inner_class.brief)) if inner_class.brief else ""
    badge = '<Badge type="info" text="struct" />'
    anchor = resolver.member_anchor(inner_class.id)

    return (
        f'<div class="docblock inner-class">\n'
        f'  <div class="definition">\n\n'
        f'### <span class="name">{inner_class.name}</span> {badge} {anchor}\n'
        f'  </div>\n'
        f'  <div class="description">\n\n'
        f'{brief}\n\n'
        f'{member_values}\n'
        f'  </div>\n'
        f'</div>\n\n'
    )

def _render_function(func: FunctionDoc, resolver: Resolver):
    name_str = _escape_md(func.name)
    anchor = resolver.member_anchor(func.id)
    brief = _inline_md_to_html(_join_paragraphs(func.brief)) if func.brief else ""
    description = _inline_md_to_html(_join_paragraphs(func.details)) if func.details else ""
    type_resolved = escape(func.return_type.as_resolved_text(resolver), quote=False)

    params_list = ""
    if func.params:
        params_list += f'|Parameter|Description|\n|---|---|\n'
        for param in func.params:
            pname = param.name
            pdesc = param.desc
            params_list += f'|<span class="type">{pname}</span>|{pdesc}|\n'

    badge = ""
    if func.virt in ("virtual", "pure-virtual"):
        label = "pure virtual" if func.virt == "pure-virtual" else "virtual"
        badge = f'<Badge type="info" text="{label}" />'

    return (
        f'<div class="docblock">\n'
        f'  <div class="definition">\n\n'
        f'### <span class="name">{name_str}()</span> <span class="type">{type_resolved}</span> {badge} {anchor}\n\n'
        f'  </div>\n\n'
        f'```cpp\n'
        f'{func.signature}\n'
        f'```\n'
        f'  <div class="description">\n\n'
        f'{params_list}\n'
        f'{brief} {description}\n'
        f'  </div>\n'
        f'</div>\n\n'
    )

def render_class(doc: ClassDoc, resolver: Resolver) -> str:
    lines: List[str] = []

    lines.append(f"# {doc.display}\n\n")
    lines.append(f'<div class="docblock docblock-class"><div class="description">')
    if doc.brief:
        lines.append(_join_paragraphs(doc.brief))

    if doc.details:
        lines.append("")
        lines.append(_join_paragraphs(doc.details))

    if len(doc.base_ids) > 0:
        link = resolver.refid_link_with_class_name(doc.base_ids[0])
        if link:
            lines.append("")
            lines += ["::: info"]
            lines += [f'Derives from {link} and inherits all public properties and methods.']
            lines += [":::\n"]

    lines.append("</div></div>\n\n")

    if doc.constructors or doc.factories:
        lines += ["## Construction", ""]
        if doc.constructors:
            lines += ["### Constructors", "<br/>"]
            for c in doc.constructors:
                lines.append(_render_function(c, resolver))
        if doc.factories:
            lines += ["### Factories <Badge type='info' text='preferred' />", "<br/>"]
            for f in doc.factories:
                lines.append(_render_function(f, resolver))

        lines.append("")

    if doc.enums or doc.inner_classes or doc.typedefs:
        lines += ["## Types"]
        if doc.enums:
            for e in doc.enums:
                lines.append(_render_enum(e, resolver))
        if doc.inner_classes:
            for c in doc.inner_classes:
                lines.append(_render_inner_class(c, resolver))
        if doc.typedefs:
            for t in doc.typedefs:
                lines.append(_render_typedef(t, resolver))
        lines.append("")

    if doc.variables:
        lines += ["## Properties", ""]
        for v in doc.variables:
            lines.append(_render_property(v, resolver))
        lines.append("")

    if doc.functions:
        lines += ["## Functions", ""]
        for f in doc.functions:
            lines.append(_render_function(f, resolver))
        lines.append("")

    out = "\n".join(lines).rstrip() + "\n"

    return out