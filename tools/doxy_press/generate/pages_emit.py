from __future__ import annotations
from ..model import Inventory
from ..parse.class_loader import load_class
from ..parse.xml_utilities import write_if_changed
from ..render.class_page import render_class
from ..resolver import Resolver
from pathlib import Path
from typing import List

def emit_class_pages(inventory: Inventory, xml_dir: Path, root_dir: Path):
    written: List[Path] = []
    output_dir = root_dir / "pages" / "reference"
    resolver = Resolver(inventory)

    for cls in inventory.classes.values():
        group = inventory.groups.get(cls.group_id)
        if group is None: continue

        group_slug = group.slug
        class_slug = cls.slug
        output_path = output_dir / group_slug / f"{class_slug}.md"
        class_doc = load_class(inventory, cls.id, xml_dir, resolver)
        content = render_class(class_doc, resolver)

        write_if_changed(output_path, content)
        written.append(output_path)

    return written