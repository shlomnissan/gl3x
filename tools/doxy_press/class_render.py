from __future__ import annotations

from typing import List
from .content_model import ClassDoc, DocParagraph

def _para(s: str) -> str: return s.strip()

def _first(paras): return _para(paras[0].md) if paras else ""

def _join_paragraphs(paras: List[DocParagraph]) -> str:
    return ("\n\n".join(p.md.strip() for p in paras if p.md.strip())).strip()

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
            lines += [f"- `{v.type.as_text()} {v.name}`"]
            fb = _first(v.brief)
            if v.initializer: lines += [f"   - Default value: `{v.initializer}`"]
            if fb: lines += [f"  - {fb}"]
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