# Programming Practice & Python Utilities

A collection of small programming exercises and practical tools I'm building while learning software development.

## Projects

### 🐍 Python Expense Summary

A command-line utility that reads a CSV file and reports:
- Total spending
- Number of transactions
- Spending grouped by category
- The highest-spending category

**Requirements:** Python 3.9+; no third-party packages.

**Run the sample:**

```bash
python python/expense_summary.py sample_expenses.csv
```

Use the included [sample_expenses.csv](sample_expenses.csv) to try it. The amounts are example data only.

**Expected output (summary):**

```text
EXPENSE SUMMARY
==================================
Transactions: 6
Total spent:  2670.00

Spending by category:
  Food: 1300.00
  Entertainment: 700.00
  Transport: 370.00
  Education: 300.00

Highest category: Food (1300.00)
```

The program validates the CSV columns and amount values, and displays a helpful error if the file is missing or the data is invalid.

### 💰 C++ Personal Finance Tracker

A C++17 console application for recording income and expenses, reviewing summaries, filtering transactions, and generating monthly reports.

[View the C++ project and build instructions](https://github.com/Abdul-Suboor-idk/cpp-personal-finance-tracker.)

## Skills I'm practicing

- C++ and Python
- Functions, loops, conditionals, and data structures
- File input/output and CSV processing
- Input validation and error handling
- Git and GitHub documentation

## Learning goals

- Add tests and improve project structure
- Build more Python automation tools
- Develop a small web project
- Explore AI APIs when I have a suitable project and setup

This is a learning repository. Feedback and suggestions are welcome.
