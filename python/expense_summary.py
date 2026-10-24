#!/usr/bin/env python3
"""Summarize expenses from a CSV file using only the Python standard library."""

import csv
import sys
from collections import defaultdict
from decimal import Decimal, InvalidOperation
from pathlib import Path


def load_expenses(csv_path: Path) -> tuple[Decimal, dict[str, Decimal], int]:
    totals: dict[str, Decimal] = defaultdict(Decimal)
    count = 0

    with csv_path.open("r", newline="", encoding="utf-8-sig") as file:
        reader = csv.DictReader(file)
        required = {"date", "category", "description", "amount"}
        columns = set(reader.fieldnames or [])
        missing = required - columns
        if missing:
            raise ValueError(
                "CSV is missing required column(s): " + ", ".join(sorted(missing))
            )

        for line_number, row in enumerate(reader, start=2):
            category = (row.get("category") or "").strip() or "Uncategorized"
            raw_amount = (row.get("amount") or "").strip()
            try:
                amount = Decimal(raw_amount)
            except InvalidOperation as exc:
                raise ValueError(
                    f"Invalid amount on CSV line {line_number}: {raw_amount!r}"
                ) from exc

            if not amount.is_finite() or amount < 0:
                raise ValueError(
                    f"Amount on CSV line {line_number} must be a finite, non-negative number."
                )

            totals[category] += amount
            count += 1

    return sum(totals.values(), Decimal("0")), dict(totals), count


def main() -> int:
    if len(sys.argv) != 2:
        print("Usage: python expense_summary.py <expenses.csv>")
        return 2

    csv_path = Path(sys.argv[1])
    if not csv_path.is_file():
        print(f"Error: file not found: {csv_path}", file=sys.stderr)
        return 2

    try:
        total, categories, count = load_expenses(csv_path)
    except (OSError, csv.Error, ValueError) as exc:
        print(f"Error: {exc}", file=sys.stderr)
        return 1

    print("\nEXPENSE SUMMARY")
    print("=" * 34)
    print(f"Transactions: {count}")
    print(f"Total spent:  {total:.2f}")
    print("\nSpending by category:")
    if not categories:
        print("  No expenses found.")
    else:
        for category, amount in sorted(
            categories.items(), key=lambda item: (-item[1], item[0].casefold())
        ):
            print(f"  {category}: {amount:.2f}")

        highest_category, highest_amount = max(
            categories.items(), key=lambda item: item[1]
        )
        print(f"\nHighest category: {highest_category} ({highest_amount:.2f})")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
