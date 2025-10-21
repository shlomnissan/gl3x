from __future__ import annotations
from dataclasses import dataclass, field
from typing import Dict, Optional, List, Tuple

@dataclass
class Class:
    id: str
    name: str
    display: str
    slug: str
    group_id: str

@dataclass
class Group:
    id: str
    name: str
    slug: str
    class_ids: List[str] = field(default_factory=list)

@dataclass
class Inventory:
    groups: Dict[str, Group] = field(default_factory=dict)
    classes: Dict[str, Class] = field(default_factory=dict)
    class_to_group: Dict[str, str] = field(default_factory=dict)