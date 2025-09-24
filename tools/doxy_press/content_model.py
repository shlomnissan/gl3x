from __future__ import annotations

from dataclasses import dataclass, field
from typing import List

@dataclass(slots=True)
class DocParagraph:
    md: str

@dataclass(slots=True)
class ClassDoc:
    id: str
    name: str
    display: str
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)