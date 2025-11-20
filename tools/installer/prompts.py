from __future__ import annotations

def ask_choice(prompt: str, choices: list[str], default_index: int = 0):
    print(f"{prompt}")
    for i, choice in enumerate(choices, start = 1):
        default_mark = " (default)" if i - 1 == default_index else ""
        print(f"  {i}) {choice}{default_mark}")
    while True:
        answer = input(f"Select [default {default_index + 1}]: ").strip()
        if not answer:
            return choices[default_index]
        if answer.isdigit():
            idx = int(answer) - 1
            if 0 <= idx < len(choices):
                return choices[idx]
        print("  Please enter a valid number.")

def ask_yes_no(prompt: str, default_yes: bool = True):
    default_str = "Y/n" if default_yes else "y/N"
    while True:
        answer = input(f"{prompt} [{default_str}]: ").strip().lower()
        if not answer:
            return default_yes
        if answer in ("y", "yes"):
            return True
        if answer in ("n", "no"):
            return False
        print("  Please answer 'y' or 'n'.")