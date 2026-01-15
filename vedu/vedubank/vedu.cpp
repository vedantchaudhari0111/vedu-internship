  // this is my El dorado
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <limits> // Required for fixing input errors

using namespace std;

// --- FUTURISTIC VISUALS ---
void typeWrite(string text) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void showLoading(string task) {
    cout << "\n>> " << task << "... [";
    for(int i=0; i<15; i++) {
        cout << "#" << flush;
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    cout << "] DONE.\n";
}

// --- CLASS DEFINITIONS ---
class Transaction {
public:
    string type;
    double amount;
    Transaction(string t, double a) {
        type = t; 
        amount = a; 
    }
};

class Account {
private:
    double balance;
    vector<Transaction> history;

public:
    Account() { balance = 0.0; }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("DEPOSIT", amount));
        typeWrite(">> FUNDS SECURED. Balance Updated.\n");
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            typeWrite("!! ERROR: Insufficient Credits.\n");
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("WITHDRAW", amount));
        typeWrite(">> CASH DISPENSED.\n");
        return true;
    }

    void addLog(string type, double amount) {
        history.push_back(Transaction(type, amount));
    }

    double getBalance() { return balance; }

    void showHistory() {
        cout << "\n   --- TRANSACTION LEDGER ---" << endl;
        cout << left << setw(20) << "TYPE" << setw(10) << "AMOUNT" << endl; 
        cout << "------------------------------" << endl;
        if(history.empty()) {
            cout << "(No transactions yet)" << endl;
        } else {
            for (auto t : history) {
                cout << left << setw(20) << t.type << "$" << t.amount << endl;
            }
        }
        cout << "------------------------------" << endl;
    }
};

class Customer {
public:
    string name;
    int accountID;
    Account account;

    Customer(string n, int id) {
        name = n;
        accountID = id;
    }
};

// --- SYSTEM MANAGER ---
vector<Customer> bankDatabase;

Customer* findCustomer(int id) {
    for (int i = 0; i < bankDatabase.size(); i++) {
        if (bankDatabase[i].accountID == id) {
            return &bankDatabase[i];
        }
    }
    return nullptr;
}

void createAccount() {
    string name;
    int id;
    
    // FIX: Clear buffer so names with spaces work
    cout << "\n[NEW CLIENT ONBOARDING]" << endl;
    cout << "Enter Full Name: "; 
    cin.ignore(); 
    getline(cin, name); // Allows "Vedant Chaudhari"

    cout << "Assign Account ID (Number): "; 
    cin >> id;
    
    bankDatabase.push_back(Customer(name, id));
    showLoading("CREATING SECURE VAULT");
    cout << ">> ACCOUNT CREATED FOR: " << name << " (ID: " << id << ")\n";
}

void performTransaction() {
    int id;
    cout << "Enter Account ID: "; 
    if (!(cin >> id)) { // Error check
        cout << "!! INVALID INPUT." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    Customer* cust = findCustomer(id);
    if (cust == nullptr) {
        cout << "!! USER NOT FOUND." << endl;
        return;
    }

    int choice;
    double amount;
    cout << "\nWelcome, " << cust->name << "." << endl;
    cout << "1. Deposit\n2. Withdraw\n3. View History\n4. Check Balance\nSelection: ";
    cin >> choice;

    switch(choice) {
        case 1: 
            cout << "Amount to Deposit: $"; cin >> amount;
            cust->account.deposit(amount);
            break;
        case 2:
            cout << "Amount to Withdraw: $"; cin >> amount;
            cust->account.withdraw(amount);
            break;
        case 3:
            cust->account.showHistory();
            break;
        case 4:
            cout << ">> CURRENT BALANCE: $" << cust->account.getBalance() << endl;
            break;
        default:
            cout << "Invalid Option." << endl;
    }
}

// --- MAIN LOOP ---
int main() {
    int choice;
    while (true) {
        cout << "\n===================================" << endl;
        cout << "    NEURAL-BANK CORP v4.1 (FIXED)" << endl;
        cout << "===================================" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Access My Account" << endl;
        cout << "3. Exit" << endl;
        cout << "Selection: ";
        cin >> choice;

        // FIX: Prevent infinite loop if user types a letter
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) createAccount();
        else if (choice == 2) performTransaction();
        else if (choice == 3) break;
    }
    return 0;
}