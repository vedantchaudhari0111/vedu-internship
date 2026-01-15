#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
                            //el dorado
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// --- UTILITY FUNCTIONS ---

// Professional "Typing" effect for futuristic feel
void typeWrite(string text, int speed = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

// Secure Password Masking (Shows '*' instead of letters)
string getMaskedPassword() {
    string password = "";
    char ch;
#ifdef _WIN32
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
#else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    cout << "[SECURE INPUT]: ";
    cin >> password;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    cout << endl;
    return password;
}

// Simple XOR Cipher for "Encrypted" storage
string encryptDecrypt(string toEncrypt) {
    char key = 'K'; // Secret key for the matrix
    string output = toEncrypt;
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;
    return output;
}

// --- CORE SYSTEM ---

class UserAuthSystem {
public:
    void displayHeader() {
        system("clear"); // Use system("cls") for Windows
        cout << "==========================================" << endl;
        cout << "    NEURAL-LINK CORE INTERFACE v2.0       " << endl;
        cout << "==========================================" << endl;
    }

    void bootSequence() {
        typeWrite(">> INITIALIZING QUANTUM ENCRYPTION...\n");
        typeWrite(">> LOADING DATABASE MODULES...\n");
        cout << "[";
        for(int i=0; i<20; i++) {
            cout << "■" << flush;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        cout << "] 100%\n\n";
    }

    void registerUser() {
        string username, password;
        displayHeader();
        cout << "[NEW REGISTRATION PROTOCOL]" << endl;
        cout << "Enter Username: "; cin >> username;

        if (fileExists(username + ".dat")) {
            typeWrite("!! ERROR: Identity already exists in the archive.\n");
            return;
        }

        cout << "Enter Password: ";
        password = getMaskedPassword();

        ofstream file(username + ".dat");
        if (file.is_open()) {
            file << encryptDecrypt(password);
            file.close();
            typeWrite(">> SUCCESS: Identity stored in the Neural Core.\n");
        }
    }

    bool loginUser() {
        string username, password, storedPass;
        displayHeader();
        cout << "[AUTHENTICATION REQUIRED]" << endl;
        cout << "Username: "; cin >> username;
        cout << "Password: ";
        password = getMaskedPassword();

        ifstream file(username + ".dat");
        if (file.is_open()) {
            getline(file, storedPass);
            file.close();

            if (encryptDecrypt(storedPass) == password) {
                typeWrite(">> ACCESS GRANTED. Welcome, " + username + ".\n");
                return true;
            }
        }
        typeWrite("!! ACCESS DENIED: Invalid Credentials.\n");
        return false;
    }

private:
    bool fileExists(string filename) {
        ifstream f(filename.c_str());
        return f.good();
    }
};

// --- MAIN EXECUTION ---

int main() {
    UserAuthSystem system;
    system.bootSequence();
    
    int choice;
    while (true) {
        system.displayHeader();
        cout << "1. REGISTER NEW IDENTITY\n";
        cout << "2. AUTHENTICATE LOGIN\n";
        cout << "3. DISCONNECT SYSTEM\n";
        cout << "\nSelection: ";
        cin >> choice;

        switch (choice) {
            case 1: system.registerUser(); break;
            case 2: system.loginUser(); break;
            case 3: typeWrite(">> SYSTEM SHUTDOWN COMPLETE.\n"); return 0;
            default: typeWrite("!! INVALID INPUT.\n");
        }
        cout << "\nPress Enter to continue...";
        cin.ignore(); cin.get();
    }
    return 0;
}