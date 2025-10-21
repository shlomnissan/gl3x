from __future__ import annotations
from .parse.inventory_loader import load_inventory
from pathlib import Path

import argparse

def main():
    parser = argparse.ArgumentParser(
        prog="python -m docs.doxy_press.main",
        description="Generate VitePress markdown from Doxygen XML",
    )
    parser.add_argument("xml_dir", help="Path to Doxygen XML root (e.g., build/docs/xml)")
    parser.add_argument("root_dir", help="Path to docs root (directory containing .vitepress/)")

    args = parser.parse_args()
    xml_dir = Path(args.xml_dir)

    if not (xml_dir / "index.xml").exists():
        parser.error(f"{xml_dir}/index.xml not found")

    _inventory = load_inventory(xml_dir)

    return 0

if __name__ == "__main__":
    raise SystemExit(main())