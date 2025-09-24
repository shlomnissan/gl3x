from __future__ import annotations

from dataclasses import dataclass, field
from typing import List, Optional

@dataclass(slots=True)
class DocParagraph:
    md: str

@dataclass(slots=True)
class TypePart:
    text: str
    refid: Optional[str] = None # present when Doxygen <ref> appears inside <type>

@dataclass(slots=True)
class TypeRef:
    parts: List[TypePart] = field(default_factory=list)

    def as_text(self) -> str:
        return "".join(p.text for p in self.parts).strip()

@dataclass(slots=True)
class VarDoc:
    id: str
    name: str
    prot: str
    static: bool
    type: TypeRef
    initializer: Optional[str] = None
    brief: List[DocParagraph] = field(default_factory=list)

@dataclass(slots=True)
class ClassDoc:
    id: str
    name: str
    display: str
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)
    variables: List[VarDoc] = field(default_factory=list)