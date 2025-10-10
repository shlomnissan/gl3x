from __future__ import annotations

from typing import Optional, Dict
from .model import Inventory, slugify

class Resolver:
    def __init__(self, inv: Inventory, base: str = "/reference/"):
        self.inv = inv
        self.base = base.rstrip("/") + "/"

        dict: Dict[str, str] = {}
        for group in inv.groups.values():
            group_slug = group.slug or slugify(group.name)
            for class_id in group.class_ids:
                c = inv.classes.get(class_id)
                if c: dict[c.id] = f"{self.base}{group_slug}/{c.slug}"

        for member in inv.members:
            member_idx = inv.members.get(member)
            base_url = dict.get(member_idx[0])
            if base_url:
                dict[member] = f'{base_url}#{member_idx[1]}'

        self._refid_to_url = dict

    def refid_url(self, refid: str) -> Optional[str]:
       return self._refid_to_url.get(refid)

    def refid_link_with_class_name(self, refid: str) -> Optional[str]:
        c = self.inv.classes.get(refid)
        return self.refid_link_with_label(refid, c.display)

    def refid_link_with_label(self, refid: str, label: str) -> Optional[str]:
        url = self.refid_url(refid)
        return f"[{label}]({url})" if label and url else label

    def member_anchor(self, refid: str) -> Optional[str]:
        idx = self.inv.members[refid]
        return f'{{#{idx[1]}}}' if idx and len(idx) > 1 else ""