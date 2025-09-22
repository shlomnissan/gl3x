from __future__ import annotations

from dataclasses import dataclass, field
from typing import Dict, Optional, List

import hashlib
import re

_slug_safe = re.compile(r"[^a-z0-9\-]+")
_camel_re1 = re.compile(r"(.)([A-Z][a-z]+)")
_camel_re2 = re.compile(r"([a-z0-9])([A-Z])")

def _snake_slug(s: str) -> str:
    s = s.replace("::", "_")
    s = _camel_re1.sub(r"\1_\2", s)
    s = _camel_re2.sub(r"\1_\2", s)
    s = re.sub(r"[\s\-]+", "_", s)
    s = re.sub(r"\W+", "_", s, flags=re.ASCII)
    s = re.sub(r"_+", "_", s).strip("_")
    return (s or "x").lower()

def _short_hash(s: str, n: int = 6) -> str:
    return hashlib.sha1(s.encode("utf-8")).hexdigest()[:n]

def slugify(s: str) -> str:
    s = s.strip().lower()
    s = s.replace("::", "-")
    s = re.sub(r"\s+", "-", s)
    s = _slug_safe.sub("-", s)
    s = re.sub(r"-{2,}", "-", s).strip("-")
    return s or "x"

@dataclass
class Class:
    id: str
    name: str
    display: str
    group_id: Optional[str] = None
    slug: str = ""

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

    def assign_class_slugs(self) -> None:
        grouped: Dict[str, List[Class]] = {}
        for c in self.classes.values():
            gid = c.group_id or "_ungrouped"
            grouped.setdefault(gid, []).append(c)

        for gid, cls_list in grouped.items():
            used = set()
            for c in sorted(cls_list, key=lambda x: (x.display.lower(), x.name.lower())):
                base = _snake_slug(c.display)
                slug = base
                if slug in used:
                    ns_hint = ""
                    if "::" in c.name:
                        ns_hint = c.name.split("::")[-2]
                        ns_hint = slugify(ns_hint)
                        slug = f"{base}_{ns_hint}"
                if slug in used:
                    slug = f"{base}-{_short_hash(c.name)}"
                c.slug = slug
                used.add(slug)