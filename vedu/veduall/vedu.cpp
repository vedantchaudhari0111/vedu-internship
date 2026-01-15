#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

// --- UTILITIES ---
void typeWrite(string text) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void pause() {
    cout << "\n[Press Enter to Return]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ==========================================
// MODULE 1: TASK 2 (SECURE LOGIN)
// ==========================================
class SecuritySystem {
public:
    string encrypt(string s) {
        for(int i=0; i<s.size(); i++) s[i] += 3;
        return s;
    }
    string decrypt(string s) {
        for(int i=0; i<s.size(); i++) s[i] -= 3;
        return s;
    }

    void registerUser() {
        string u, p;
        cout << "\n[REGISTER NEW ID]\nUsername: "; cin >> u;
        cout << "Password: "; cin >> p;
        ofstream file(u + ".dat");
        file << encrypt(p);
        file.close();
        typeWrite(">> ID CREATED. PLEASE LOGIN.\n");
    }

    bool login() {
        string u, p, stored;
        cout << "\n[SYSTEM LOGIN]\nUsername: "; cin >> u;
        cout << "Password: "; cin >> p;
        
        ifstream file(u + ".dat");
        if(file.is_open()) {
            getline(file, stored);
            if(decrypt(stored) == p) {
                typeWrite(">> ACCESS GRANTED. Welcome " + u + ".\n");
                return true;
            }
        }
        typeWrite("!! ACCESS DENIED.\n");
        return false;
    }
};

// ==========================================
// MODULE 2: TASK 1 (CGPA CALCULATOR)
// ==========================================
class AcademicSystem {
    struct Course {
        string name;
        int marks, credits, gp;
    };
public:
    void run() {
        int n;
        vector<Course> subs;
        float totalPts = 0; 
        int totalCreds = 0;

        cout << "\n=== ACADEMIC PORTAL (CGPA) ===" << endl;
        cout << "Enter number of subjects: "; cin >> n;

        for(int i=0; i<n; i++) {
            Course c;
            cout << "Subject " << i+1 << " Name: "; cin >> c.name;
            cout << "Marks (0-100): "; cin >> c.marks;
            cout << "Credits: "; cin >> c.credits;

            // Grading Logic
            if(c.marks >= 90) c.gp = 10;
            else if(c.marks >= 80) c.gp = 9;
            else if(c.marks >= 70) c.gp = 8;
            else if(c.marks >= 60) c.gp = 7;
            else if(c.marks >= 50) c.gp = 6;
            else if(c.marks >= 40) c.gp = 4;
            else c.gp = 0;

            subs.push_back(c);
            totalPts += (c.gp * c.credits);
            totalCreds += c.credits;
        }

        cout << "\n--- TRANSCRIPT ---" << endl;
        cout << left << setw(15) << "SUBJECT" << setw(10) << "GRADE PT" << endl;
        for(auto c : subs) {
            cout << left << setw(15) << c.name << setw(10) << c.gp << endl;
        }
        
        float cgpa = (totalCreds > 0) ? totalPts/totalCreds : 0;
        cout << "------------------" << endl;
        cout << "FINAL CGPA: " << fixed << setprecision(2) << cgpa << " / 10.0" << endl;
        pause();
    }
};

// ==========================================
// MODULE 3: TASK 4 (BANKING SYSTEM)
// ==========================================
class BankSystem {
    struct Transaction { string type; double amt; };
    double balance = 0;
    vector<Transaction> history;
public:
    void run() {
        int choice;
        while(true) {
            cout << "\n=== FINANCIAL PORTAL (NEURAL BANK) ===" << endl;
            cout << "1. Deposit\n2. Withdraw\n3. History\n4. Balance\n5. Back to Main Menu\nSelect: ";
            cin >> choice;

            if(cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); continue; }

            if(choice == 1) {
                double amt; cout << "Amount: $"; cin >> amt;
                balance += amt;
                history.push_back({"DEPOSIT", amt});
                cout << ">> SUCCESS." << endl;
            }
            else if(choice == 2) {
                double amt; cout << "Amount: $"; cin >> amt;
                if(amt > balance) cout << "!! LOW FUNDS." << endl;
                else {
                    balance -= amt;
                    history.push_back({"WITHDRAW", amt});
                    cout << ">> DISPENSED." << endl;
                }
            }
            else if(choice == 3) {
                cout << "\n--- STATEMENT ---" << endl;
                for(auto t : history) cout << t.type << ": $" << t.amt << endl;
            }
            else if(choice == 4) {
                cout << ">> BALANCE: $" << balance << endl;
            }
            else if(choice == 5) break;
        }
    }
};

// ==========================================
// MAIN SUPER-APP CONTROLLER
// ==========================================
int main() {
    SecuritySystem security;
    AcademicSystem academics;
    BankSystem bank;
    
    int choice;
    bool loggedIn = false;

    while(true) {
        if(!loggedIn) {
            cout << "\n===============================" << endl;
            cout << "    NEURAL-OS MAIN GATEWAY     " << endl;
            cout << "===============================" << endl;
            cout << "1. Login\n2. Register\n3. Shutdown\nSelect: ";
            cin >> choice;

            if(choice == 1) {
                if(security.login()) loggedIn = true;
            }
            else if(choice == 2) security.registerUser();
            else if(choice == 3) return 0;
        } 
        else {
            // MAIN APP DASHBOARD
            cout << "\n===============================" << endl;
            cout << "       NEURAL-OS DASHBOARD     " << endl;
            cout << "===============================" << endl;
            cout << "1. Academic Portal (CGPA)\n2. Financial Portal (Bank)\n3. Logout\nSelect App: ";
            cin >> choice;

            if(cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); continue; }

            if(choice == 1) academics.run();
            else if(choice == 2) bank.run();
            else if(choice == 3) {
                loggedIn = false;
                typeWrite(">> LOGGING OUT...\n");
            }
        }
    }
    return 0;
}
