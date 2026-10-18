#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

struct Transaction {
    string type;
    double amount;
    string category;
    string description;
    string date;
};

const string DATA_FILE = "transactions.txt";

string trim(const string& text) {
    const string whitespace = " \t\r\n";
    size_t start = text.find_first_not_of(whitespace);
    if (start == string::npos) return "";
    size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

string lowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char ch) { return static_cast<char>(tolower(ch)); });
    return text;
}

string getNonEmptyInput(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        value = trim(value);
        if (value.empty()) {
            cout << "This field cannot be empty. Please try again.\n";
            continue;
        }
        if (value.find('|') != string::npos) {
            cout << "Please do not use the | character.\n";
            continue;
        }
        return value;
    }
}

int getMenuChoice() {
    string input;
    while (true) {
        cout << "\n========== PERSONAL FINANCE TRACKER ==========\n";
        cout << "1. Add income\n2. Add expense\n3. View all transactions\n";
        cout << "4. View financial summary\n5. View monthly report\n";
        cout << "6. Filter transactions by category\n7. Exit\n";
        cout << "Choose an option (1-7): ";
        getline(cin, input);
        input = trim(input);
        try {
            size_t used = 0;
            int choice = stoi(input, &used);
            if (used == input.size() && choice >= 1 && choice <= 7) return choice;
        } catch (...) {}
        cout << "Invalid choice. Enter a number from 1 to 7.\n";
    }
}

double getPositiveAmount() {
    string input;
    while (true) {
        cout << "Amount in PKR: ";
        getline(cin, input);
        input = trim(input);
        try {
            size_t used = 0;
            double amount = stod(input, &used);
            if (used == input.size() && isfinite(amount) && amount > 0.0) return amount;
        } catch (...) {}
        cout << "Invalid amount. Enter a number greater than 0, such as 1500 or 250.50.\n";
    }
}

string getDate() {
    while (true) {
        string date = getNonEmptyInput("Date (YYYY-MM-DD): ");
        bool valid = date.size() == 10 && date[4] == '-' && date[7] == '-';
        if (valid) {
            for (size_t i = 0; i < date.size(); ++i) {
                if (i == 4 || i == 7) continue;
                if (!isdigit(static_cast<unsigned char>(date[i]))) valid = false;
            }
            int month = stoi(date.substr(5, 2));
            int day = stoi(date.substr(8, 2));
            valid = valid && month >= 1 && month <= 12 && day >= 1 && day <= 31;
        }
        if (valid) return date;
        cout << "Invalid date format. Use YYYY-MM-DD, for example 2026-10-18.\n";
    }
}

string getMonth() {
    while (true) {
        string month = getNonEmptyInput("Enter month (YYYY-MM), for example 2026-10: ");
        bool valid = month.size() == 7 && month[4] == '-';
        if (valid) {
            for (size_t i = 0; i < month.size(); ++i) {
                if (i == 4) continue;
                if (!isdigit(static_cast<unsigned char>(month[i]))) valid = false;
            }
            int number = stoi(month.substr(5, 2));
            valid = valid && number >= 1 && number <= 12;
        }
        if (valid) return month;
        cout << "Invalid month. Use YYYY-MM, for example 2026-10.\n";
    }
}

vector<Transaction> loadTransactions() {
    vector<Transaction> transactions;
    ifstream file(DATA_FILE);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Transaction t;
        string amountText;
        if (getline(ss, t.type, '|') && getline(ss, amountText, '|') &&
            getline(ss, t.category, '|') && getline(ss, t.description, '|') &&
            getline(ss, t.date)) {
            try {
                t.amount = stod(amountText);
                if ((t.type == "Income" || t.type == "Expense") &&
                    isfinite(t.amount) && t.amount > 0.0) transactions.push_back(t);
            } catch (...) {}
        }
    }
    return transactions;
}

bool saveTransaction(const Transaction& t) {
    ofstream file(DATA_FILE, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open " << DATA_FILE << " for saving.\n";
        return false;
    }
    file << t.type << '|' << fixed << setprecision(2) << t.amount << '|'
         << t.category << '|' << t.description << '|' << t.date << '\n';
    return static_cast<bool>(file);
}

void addTransaction(const string& type, vector<Transaction>& transactions) {
    cout << "\n--- Add " << type << " ---\n";
    Transaction t;
    t.type = type;
    t.amount = getPositiveAmount();
    t.category = getNonEmptyInput("Category (e.g. Salary, Food, Transport): ");
    t.description = getNonEmptyInput("Description: ");
    t.date = getDate();
    if (saveTransaction(t)) {
        transactions.push_back(t);
        cout << type << " saved successfully.\n";
    } else {
        cout << "The transaction could not be saved.\n";
    }
}

void printHeader() {
    cout << left << setw(5) << "No." << setw(10) << "Type"
         << setw(13) << "Amount(PKR)" << setw(16) << "Category"
         << setw(24) << "Description" << "Date\n";
    cout << string(82, '-') << '\n';
}

void printTransaction(const Transaction& t, size_t number) {
    cout << left << setw(5) << number << setw(10) << t.type
         << setw(13) << fixed << setprecision(2) << t.amount
         << setw(16) << t.category.substr(0, 15)
         << setw(24) << t.description.substr(0, 23) << t.date << '\n';
}

void viewTransactions(const vector<Transaction>& transactions) {
    cout << "\n================ ALL TRANSACTIONS ================\n";
    if (transactions.empty()) {
        cout << "No transactions yet. Add income or expenses first.\n";
        return;
    }
    printHeader();
    for (size_t i = 0; i < transactions.size(); ++i) printTransaction(transactions[i], i + 1);
}

void showSummary(const vector<Transaction>& transactions) {
    double income = 0.0, expenses = 0.0;
    for (const Transaction& t : transactions) {
        if (t.type == "Income") income += t.amount;
        else expenses += t.amount;
    }
    cout << "\n============== FINANCIAL SUMMARY ==============\n" << fixed << setprecision(2);
    cout << "Total income:   PKR " << income << '\n';
    cout << "Total expenses: PKR " << expenses << '\n';
    cout << "Balance:        PKR " << income - expenses << '\n';
    cout << "Transactions:   " << transactions.size() << '\n';
}

void showMonthlyReport(const vector<Transaction>& transactions) {
    cout << "\n================ MONTHLY REPORT ================\n";
    string month = getMonth();
    double income = 0.0, expenses = 0.0;
    size_t count = 0;
    for (const Transaction& t : transactions) {
        if (t.date.size() >= 7 && t.date.substr(0, 7) == month) {
            ++count;
            if (t.type == "Income") income += t.amount;
            else expenses += t.amount;
        }
    }
    cout << "\nReport for " << month << '\n' << fixed << setprecision(2);
    cout << "Income:       PKR " << income << '\n';
    cout << "Expenses:     PKR " << expenses << '\n';
    cout << "Monthly net:  PKR " << income - expenses << '\n';
    cout << "Transactions: " << count << '\n';
    if (count == 0) cout << "No transactions were found for this month.\n";
}

void filterByCategory(const vector<Transaction>& transactions) {
    cout << "\n============= FILTER BY CATEGORY =============\n";
    string category = getNonEmptyInput("Enter category to search for: ");
    string target = lowerCase(category);
    size_t matches = 0;
    double income = 0.0, expenses = 0.0;
    for (const Transaction& t : transactions) {
        if (lowerCase(t.category) == target) {
            if (matches == 0) printHeader();
            printTransaction(t, matches + 1);
            ++matches;
            if (t.type == "Income") income += t.amount;
            else expenses += t.amount;
        }
    }
    if (matches == 0) {
        cout << "No transactions found for category \"" << category << "\".\n";
    } else {
        cout << fixed << setprecision(2);
        cout << "\nMatching transactions: " << matches << '\n';
        cout << "Income in this category:   PKR " << income << '\n';
        cout << "Expenses in this category: PKR " << expenses << '\n';
    }
}

int main() {
    vector<Transaction> transactions = loadTransactions();
    cout << "Welcome to Personal Finance Tracker!\n";
    cout << "Loaded " << transactions.size() << " saved transaction(s).\n";
    bool running = true;
    while (running) {
        switch (getMenuChoice()) {
            case 1: addTransaction("Income", transactions); break;
            case 2: addTransaction("Expense", transactions); break;
            case 3: viewTransactions(transactions); break;
            case 4: showSummary(transactions); break;
            case 5: showMonthlyReport(transactions); break;
            case 6: filterByCategory(transactions); break;
            case 7:
                cout << "Your transactions are saved in " << DATA_FILE << ".\nGoodbye!\n";
                running = false;
                break;
        }
    }
    return 0;
}
