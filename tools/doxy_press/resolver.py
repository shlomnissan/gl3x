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
        self._class_url = dict

    def class_url(self, refid: str) -> Optional[str]:
       return self._class_url.get(refid)

    def class_display(self, refid: str) -> Optional[str]:
        c = self.inv.classes.get(refid)
        return c.display if c else None

    def class_link_md(self, refid: str) -> Optional[str]:
        display = self.class_display(refid)
        url = self.class_url(refid)
        return f"[{display}]({url})" if display and url else None