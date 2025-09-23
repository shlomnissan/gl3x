from __future__ import annotations

from pathlib import Path
from typing import List
from .model import Inventory, slugify

import pdb

HEADER = "<!-- AUTO-GENERATED — do not edit. -->\n"

def _class_markdown(title: str) -> str:
    return (
        f"# {title}"
    )

def _write_if_changed(path: Path, content: str) -> bool:
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists() and path.read_text(encoding="utf-8") == content:
        return False
    path.write_text(content, encoding="utf-8")
    return True

def emit_class_pages(inv: Inventory, docs_root: Path) -> List[Path]:
    written: List[Path] = []
    out_root = docs_root / "pages" / "reference"

    group_slug = {
        gid: (g.slug or slugify(g.name))
        for gid, g in inv.groups.items()
    }

    classes = sorted(
        (c for c in inv.classes.values() if c.group_id),
        key=lambda c: (group_slug[c.group_id], c.display.lower(), c.name.lower())
    )

    for c in classes:
        gslug = group_slug[c.group_id]
        cslug = c.slug
        dest = out_root / gslug / f"{cslug}.md"

        content = (
            HEADER
            + _class_markdown(c.display)
        )

        _write_if_changed(dest, content)
        written.append(dest)

    return written