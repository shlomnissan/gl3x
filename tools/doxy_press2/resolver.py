from __future__ import annotations
from .model import Inventory
from typing import Dict

class Resolver:
    def __init__(self, inventory: Inventory, base: str = "/reference/"):
        self.inventory = inventory
        self.base = base.rstrip("/") + "/"

        id_to_url: Dict[str, str] = {}

        for group in self.inventory.groups.values():
            group_slug = group.slug
            for class_id in group.class_ids:
                cls = inventory.classes.get(class_id)
                id_to_url[cls.id] = f"{self.base}{group_slug}/{cls.slug}"

        for member in self.inventory.members.values():
            parent_class = inventory.classes.get(member.parent_id)
            if parent_class is not None:
                class_url = id_to_url.get(parent_class.id)
                id_to_url[member.id] = f"{class_url}#{member.slug}"

        self._id_to_url = id_to_url

    def id_to_url(self, id: str):
       return self._id_to_url.get(id)

    def id_to_url_with_label(self, id: str, label: str):
        url = self._id_to_url.get(id)
        return f"[{label}]({url})" if label and url else label

    def class_id_to_url(self, id: str):
        cls = self.inventory.classes.get(id)
        return self.id_to_url_with_label(id, cls.display) if cls else None