# C++ Personal Finance Tracker

A beginner-friendly C++ console app for recording income and expenses, viewing transactions, checking your overall balance, generating monthly reports, and filtering transactions by category. It stores records locally in a text file.

## Features

- Add income and expenses in PKR
- Record amount, category, description, and date
- View all saved transactions
- Calculate total income, total expenses, and current balance
- Generate a monthly report using `YYYY-MM`
- Filter transactions by category (case-insensitive)
- Validate menu choices, amounts, required fields, and date/month formats
- Save data in `transactions.txt` and reload it when the program starts
- Standard C++ library only; no external packages required

## Requirements

- Windows 10 or Windows 11
- A C++ compiler, such as g++ (MinGW-w64) or MSVC

## Run on Windows with g++

1. Install a C++ compiler that provides `g++`.
2. Download or clone this repository and open Command Prompt in the project folder.
3. Compile:

   ```bat
   g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o finance_tracker.exe
   ```

4. Run:

   ```bat
   finance_tracker.exe
   ```

If Windows says `g++` is not recognized, install/configure MinGW-w64, add its `bin` folder to your `PATH`, then reopen the terminal.

## Run with Visual Studio

Install Visual Studio with the **Desktop development with C++** workload, create/open a C++ console project, replace the generated source with `main.cpp`, then build and run with **Ctrl+F5**.

## Menu

1. Add income
2. Add expense
3. View all transactions
4. View financial summary
5. View monthly report
6. Filter transactions by category
7. Exit

## Example monthly report

If October 2026 includes PKR 85,000 income and PKR 1,200 expenses:

```text
Report for 2026-10
Income:       PKR 85000.00
Expenses:     PKR 1200.00
Monthly net:  PKR 83800.00
Transactions: 2
```

Choose menu option 5 and enter `2026-10` to view that month's totals. Choose option 6 and enter a category such as `Food` to show matching transactions.

## Data storage

Each line in `transactions.txt` follows this format:

```text
Type|Amount|Category|Description|Date
```

The file is created in the program's current working directory. Back it up if you want to keep your records. Do not use the `|` character in categories or descriptions because it separates fields. The date validation checks the format and basic month/day ranges, but does not verify every calendar date.

## Concepts demonstrated

- Structures, vectors, functions, loops, and `switch`
- Input validation and exception handling
- File input/output
- String processing and case-insensitive matching
- Monthly totals and formatted console output

## Possible improvements

- Edit or delete transactions
- Search by date range
- Export to CSV
- Charts or a graphical interface
- Unit tests

## Disclaimer

This is a learning project, not accounting or financial advice. Keep a backup of your local data file.
