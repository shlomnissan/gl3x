from __future__ import annotations

from pathlib import Path
from .parse_xml import load_inventory
from .sidebar_emit import emit_reference_sidebar_ts
from .pages_emit import emit_class_pages

import argparse

def main() -> int:
    parser = argparse.ArgumentParser(
        prog="python -m docs.doxymd.main",
        description="Generate VitePress markdown from Doxygen XML",
    )
    parser.add_argument("xml_dir", help="Path to Doxygen XML root (e.g., build/docs/xml)")
    parser.add_argument("docs_root", help="Path to docs root (directory containing .vitepress/)")

    args = parser.parse_args()
    xml_dir = Path(args.xml_dir)
    docs_root = Path(args.docs_root)

    if not (xml_dir / "index.xml").exists():
        parser.error(f"{xml_dir}/index.xml not found")

    inv = load_inventory(xml_dir)

    sidebar = emit_reference_sidebar_ts(inv, docs_root)
    print(f"✅ wrote sidebar: {sidebar}")

    written = emit_class_pages(inv, docs_root, xml_dir)
    print(f"✅ wrote {len(written)} class pages")

    return 0

if __name__ == "__main__":
    raise SystemExit(main())