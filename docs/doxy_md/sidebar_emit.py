from __future__ import annotations

from pathlib import Path
from typing import Dict, List
from .model import Inventory, slugify

import json

def _build_sections(inv: Inventory) -> List[dict]:
    by_group: Dict[str, List[str]] = {}
    for g in inv.groups.values():
        valid_ids = [cid for cid in g.class_ids if cid in inv.classes]
        if not valid_ids:
            continue
        by_group[g.id] = sorted(
            valid_ids, key=lambda cid: inv.classes[cid].display.lower()
        )

    def group_label(gid: str) -> str:
        return inv.groups[gid].name

    def group_slug(gid: str) -> str:
        g = inv.groups[gid]
        return g.slug or slugify(g.name)

    group_order = sorted(by_group.keys(), key=lambda gid: group_label(gid).lower())

    sections: List[dict] = []
    for gid in group_order:
        gslug = group_slug(gid)
        items = [
            {
                "text": inv.classes[cid].display,
                "link": f"/reference/{gslug}/{inv.classes[cid].slug}",
            }
            for cid in by_group[gid]
        ]
        if not items:
            continue  # skip empty groups just in case
        sections.append({
            "text": group_label(gid),
            "collapsed": False,
            "items": items,
        })
    return sections


def emit_reference_sidebar_ts(
    inv: Inventory,
    docs_root: str | Path,
    filename: str = "auto-reference-sidebar.ts",
) -> Path:
    docs_root = Path(docs_root)
    vp_dir = docs_root / ".vitepress"
    vp_dir.mkdir(parents=True, exist_ok=True)
    out_path = vp_dir / filename

    sections = _build_sections(inv)

    json_text = json.dumps(sections, ensure_ascii=False, indent=2)
    ts = (
        "// AUTO-GENERATED — do not edit.\n"
        "import type { DefaultTheme } from 'vitepress';\n\n"
        f"const referenceSidebar: DefaultTheme.SidebarItem[] = {json_text};\n\n"
        "export default referenceSidebar;\n"
    )

    out_path.write_text(ts, encoding="utf-8")
    return out_path
