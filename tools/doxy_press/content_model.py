from __future__ import annotations

from dataclasses import dataclass, field
from typing import List, Optional
from .resolver import Resolver
from .model import remove_all_qualifications

import re

@dataclass(slots=True)
class DocParagraph:
    md: str

@dataclass(slots=True)
class TypePart:
    text: str
    refid: Optional[str] = None # present when Doxygen <ref> appears inside <type>

@dataclass(slots=True)
class ParamDoc:
    name: str
    type: TypeRef
    desc: Optional[str] = None
    default: Optional[str] = None

@dataclass(slots=True)
class TypeRef:
    parts: List[TypePart] = field(default_factory=list)

    def _clean_text(self, s: str) -> str:
        s = re.sub(r'\boverride\b', '', s)
        s = re.sub(r'\s*=\s*0\b', '', s)
        return re.sub(r'\s+', ' ', s).strip()

    def as_text(self) -> str:
        s = "".join(p.text.strip() for p in self.parts if p.text and p.text.strip())
        return self._clean_text(s)

    def as_resolved_text(self, resolver: Resolver) -> str:
        s = ""
        for part in self.parts:
            label = self._clean_text(part.text)
            if not label: continue
            if (part.refid):
                label = remove_all_qualifications(label)
                s += resolver.refid_link_with_label(part.refid, label)
            else:
                s += label
        return s

@dataclass(slots=True)
class VarDoc:
    id: str
    name: str
    prot: str
    static: bool
    type: TypeRef
    initializer: Optional[str] = None
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)
    line: Optional[int] = 0

@dataclass(slots=True)
class TypeDefDoc:
    id: str
    name: str
    display: str
    definition: str
    type: TypeRef
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)

@dataclass(slots=True)
class FunctionDoc:
    id: str
    name: str
    prot: str
    static: bool
    virt: Optional[str]
    return_type: TypeRef
    signature: str
    params: List[ParamDoc] = field(default_factory=list)
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)

@dataclass(slots=True)
class EnumValueDoc:
    name: str
    brief: List[DocParagraph] = field(default_factory=list)

@dataclass(slots=True)
class EnumDoc:
    id: str
    name: str
    display: str
    scoped: bool
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)
    values: List[EnumValueDoc] = field(default_factory=list)

@dataclass(slots=True)
class ClassDoc:
    id: str
    name: str
    display: str
    base_ids: List[Optional[str]] = field(default_factory=list)
    brief: List[DocParagraph] = field(default_factory=list)
    details: List[DocParagraph] = field(default_factory=list)
    variables: List[VarDoc] = field(default_factory=list)
    functions: List[FunctionDoc] = field(default_factory=list)
    constructors: List[FunctionDoc] = field(default_factory=list)
    factories: List[FunctionDoc] = field(default_factory=list)
    enums: List[EnumDoc] = field(default_factory=list)
    inner_classes: List[ClassDoc] = field(default_factory=list)
    typedefs: List[TypeDefDoc] = field(default_factory=list)