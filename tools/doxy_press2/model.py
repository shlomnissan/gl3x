from __future__ import annotations
from dataclasses import dataclass, field
from typing import Dict, Optional, List

@dataclass
class Class:
    id: str
    name: str
    display: str
    slug: str
    group_id: Optional[str]

@dataclass
class Group:
    id: str
    name: str
    slug: str
    class_ids: List[str] = field(default_factory=list)

@dataclass
class Member:
    id: str
    parent_id: str
    name: str
    kind: str
    slug: str

@dataclass
class Inventory:
    groups: Dict[str, Group] = field(default_factory=dict)
    classes: Dict[str, Class] = field(default_factory=dict)
    members: Dict[str, Member] = field(default_factory=dict)
    class_to_group: Dict[str, str] = field(default_factory=dict)

@dataclass
class Description:
    brief: str
    details: str

@dataclass
class ClassDoc:
    id: str
    name: str
    display: str
    base_class_id: Optional[str]
    brief: str
    details: str