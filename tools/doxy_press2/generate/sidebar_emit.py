from __future__ import annotations
from ..model import Inventory
from ..parse.xml_utilities import write_if_changed
from pathlib import Path
from typing import Dict, List

import json

FILENAME = "auto-reference-sidebar.ts"

def _build_sections(inventory: Inventory):
    group_to_classes: Dict[str, List[str]] = {}
    for group in inventory.groups.values():
        valid_ids = [cid for cid in group.class_ids if cid in inventory.classes]
        if not valid_ids: continue

        group_to_classes[group.id] = sorted(
            valid_ids, key=lambda cid: inventory.classes[cid].name.lower()
        )

    group_order = sorted(group_to_classes.keys(), key=lambda gid: inventory.groups[gid].name)
    sections: List[dict] = []

    for gid in group_order:
        group_name = inventory.groups[gid].name
        group_slug = inventory.groups[gid].slug
        items = [
            {
                "text": inventory.classes[cid].display,
                "link": f"/reference/{group_slug}/{inventory.classes[cid].slug}"
            }
            for cid in group_to_classes[gid]
        ]
        if not items: continue

        sections.append({
            "text": group_name,
            "collapsed": True,
            "items": items,
        })
    return sections

def emit_sidebar(inventory: Inventory, root_dir: Path):
    output_dir = root_dir / ".vitepress"
    output_dir.mkdir(parents = True, exist_ok = True)
    output_path = output_dir / FILENAME

    sections = _build_sections(inventory)

    json_text = json.dumps(sections, ensure_ascii=False, indent=2)
    content = (
        "// AUTO-GENERATED — do not edit.\n"
        "import type { DefaultTheme } from 'vitepress';\n\n"
        f"const referenceSidebar: DefaultTheme.SidebarItem[] = {json_text};\n\n"
        "export default referenceSidebar;\n"
    )

    write_if_changed(output_path, content)

    return output_path