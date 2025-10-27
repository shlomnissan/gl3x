import re

_camel_re1 = re.compile(r"(.)([A-Z][a-z]+)")
_camel_re2 = re.compile(r"([a-z])([A-Z])")

def slugify(s: str):
    s = s.replace("::", "_")
    s = _camel_re1.sub(r"\1_\2", s)
    s = _camel_re2.sub(r"\1_\2", s)
    s = re.sub(r"[\s\-]+", "_", s)
    s = re.sub(r"\W+", "_", s, flags=re.ASCII)
    s = re.sub(r"_+", "_", s).strip("_")
    return (s or "x").lower()

def remove_first_qualification(s):
    parts = s.split("::", 1)
    return parts[1] if len(parts) == 2 else s

def remove_qualifications(s):
    return s.split("::")[-1] if "::" in s else s

def tighten_template_spaces(s: str):
    def clean(match: re.Match):
        inner = match.group(1)
        inner = inner.strip()
        inner = re.sub(r'\s*,\s*', ', ', inner)
        return f"<{inner}>"

    return re.sub(r'<\s*(.*?)\s*>', clean, s)