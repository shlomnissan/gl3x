from __future__ import annotations

from typing import List
from .content_model import ClassDoc, DocParagraph

def _join_paragraphs(paras: List[DocParagraph]) -> str:
    # blank line between paragraphs;
    return ("\n\n".join(p.md.strip() for p in paras if p.md.strip())).strip()

def render_class(doc: ClassDoc) -> str:
    lines: List[str] = []

    lines.append(f"# {doc.display}\n\n")

    if doc.brief:
        lines.append(_join_paragraphs(doc.brief))

    if doc.details:
        lines.append(_join_paragraphs(doc.details))

    out = "\n".join(lines).rstrip() + "\n"

    return out