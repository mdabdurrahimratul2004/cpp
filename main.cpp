#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class Customer {
public:
    string name;
    string serialNumber;
    int age;
    string phoneNumber;
    string email;
    double balance;

    Customer() {}

    Customer(string n, string s, int a, string p, string e, double b) {
        name = n;
        serialNumber = s;
        age = a;
        phoneNumber = p;
        email = e;
        balance = b;
    }

    void saveToFile() {
        ofstream outFile("customers.txt", ios::app);
        if (!outFile) {
            cout << "Error opening file!\n";
            return;
        }
        outFile << serialNumber << " " << name << " " << age << " "
                << phoneNumber << " " << email << " " << balance << endl;
        outFile.close();
    }
};

class Bank {
protected:
    string serials[1000];
    int totalSerials = 0;

    void loadExistingSerials() {
        ifstream inFile("customers.txt");

        string serial, temp;
        if (inFile.is_open()) {
            while (!inFile.eof()) {
                inFile >> serial;
                if (!serial.empty()) {
                    serials[totalSerials++] = serial;
                    getline(inFile, temp);
                }
            }
            inFile.close();
        } else {
            cout << "File not found. Starting fresh!\n";
        }
    }

    void returnMenu() {
        int option;
        cout << "\n1. Main Menu\n2. Exit\nChoose: ";
        cin >> option;
        if (option == 2) {
            cout << "Thanks for banking with us!\n";
            exit(0);
        }
    }

public:
    Bank() {
        loadExistingSerials();
    }

    bool isSerialUnique(string serial) {
        for (int i = 0; i < totalSerials; i++) {
            if (serials[i] == serial) {
                return false;
            }
        }
        return true;
    }

    void createAccount() {
        cout << "1. One account\n2. Multiple accounts\n3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            cout << "Going back to main menu...\n";
            return;
        }

        int total;
        if (choice == 1) {
            total = 1;
        } else if (choice == 2) {
            cout << "How many accounts do you want to create? => ";
            cin >> total;
        } else {
            cout << "Invalid option! Returning to main menu...\n";
            return;
        }

        for (int i = 0; i < total; i++) {
            string name, serialNumber, phoneNumber, email;
            int age;
            double balance;

            cout << "Enter your name: ";
            cin >> name;

            do {
                cout << "Enter your unique 4-digit serial number: ";
                cin >> serialNumber;
                if (!isSerialUnique(serialNumber)) {
                    cout << "Serial already exists! Type a new 4-digit serial.\n";
                }
                else if(serialNumber.length() != 4) {
                    cout << "Serial number must be 4 digits long!\n";
                }
                else {
                    break;
                }
            } while (serialNumber.length() != 4 || !isSerialUnique(serialNumber));

            cout << "Enter your age: ";
            cin >> age;
            if (age < 18) {
                cout << "\nYou must be at least 18 years old to create an account.\n";
                continue;
            }

            cout << "Enter your phone number: ";
            cin >> phoneNumber;
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your initial balance: ";
            cin >> balance;

            Customer newCustomer(name, serialNumber, age, phoneNumber, email, balance);
            newCustomer.saveToFile();

            serials[totalSerials++] = serialNumber;

            cout << "\nAccount created successfully!\n";
            cout << "Assigned Serial (Shown): " << 7638000000 + stoi(serialNumber) << endl;
        }
        returnMenu();
    }

    void searchAccount() {
        string searchSerial;
        cout << "Enter the 4-digit serial number to search: ";
        cin >> searchSerial;

        ifstream inFile("customers.txt");
        bool found = false;
        string serial, name, phone, email;
        int age;
        double balance;

        while (inFile >> serial >> name >> age >> phone >> email >> balance) {
            if (serial == searchSerial) {
                cout << "\n--- Account Found ---\n";
                cout << "Name: " << name << endl;
                cout << "Age: " << age << endl;
                cout << "Phone: " << phone << endl;
                cout << "Email: " << email << endl;
                cout << "Balance: $" << balance << endl;
                cout << "Assigned Serial (Shown): " << 7638000000 + stoi(serial) << endl;
                found = true;
                break;
            }
        }
        inFile.close();

        if (!found) {
            cout << "\nAccount not found with serial number: " << searchSerial << endl;
        }
        returnMenu();
    }

    void balanceQuery() {
        string searchSerial;
        cout << "Enter the 4-digit serial number to check balance: ";
        cin >> searchSerial;

        ifstream inFile("customers.txt");
        bool found = false;
        string serial, name, phone, email;
        int age;
        double balance;

        while (inFile >> serial >> name >> age >> phone >> email >> balance) {
            if (serial == searchSerial) {
                cout << "\n--- Balance Information ---\n";
                cout << "Account Holder : " << name << endl;
                cout << "Assigned Serial : " << 7638000000 + stoi(serial) << endl;
                cout << "Available Balance : $" << balance << endl;
                found = true;
                break;
            }
        }
        inFile.close();

        if (!found) {
            cout << "\nAccount not found.\n";
        }
        returnMenu();
    }

    void depositMoney() {
        string searchSerial;
        cout << "Enter the 4-digit serial number to deposit: ";
        cin >> searchSerial;

        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        bool found = false;
        string serial, name, phone, email;
        int age;
        double balance, depositAmount;

        while (inFile >> serial >> name >> age >> phone >> email >> balance) {
            if (serial == searchSerial) {
                cout << "Enter amount to deposit: ";
                cin >> depositAmount;
                balance += depositAmount;
                cout << "\nDeposit successful! New Balance: $" << balance << endl;
                found = true;
            }
            tempFile << serial << " " << name << " " << age << " "
                     << phone << " " << email << " " << balance << endl;
        }

        inFile.close();
        tempFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");

        if (!found) {
            cout << "\nAccount not found.\n";
        }
        returnMenu();
    }

    void withdrawMoney() {
        string searchSerial;
        cout << "Enter the 4-digit serial number to withdraw: ";
        cin >> searchSerial;

        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        bool found = false;
        string serial, name, phone, email;
        int age;
        double balance, withdrawAmount;

        while (inFile >> serial >> name >> age >> phone >> email >> balance) {
            if (serial == searchSerial) {
                cout << "Enter amount to withdraw: ";
                cin >> withdrawAmount;
                if (withdrawAmount <= balance) {
                    balance -= withdrawAmount;
                    cout << "\nWithdrawal successful! New Balance: $" << balance << endl;
                } else {
                    cout << "\nInsufficient balance!\n";
                }
                found = true;
            }
            tempFile << serial << " " << name << " " << age << " "
                     << phone << " " << email << " " << balance << endl;
        }

        inFile.close();
        tempFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");

        if (!found) {
            cout << "\nAccount not found.\n";
        }
        returnMenu();
    }

    void takeLoan() {
        string searchSerial;
        cout << "Enter the 4-digit serial number to apply for a loan: ";
        cin >> searchSerial;

        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        bool found = false;
        string serial, name, phone, email;
        int age;
        double balance, loanAmount;

        while (inFile >> serial >> name >> age >> phone >> email >> balance) {
            if (serial == searchSerial) {
                cout << "Enter loan amount you want: ";
                cin >> loanAmount;
                balance += loanAmount;
                cout << "\nLoan approved! New Balance: $" << balance << endl;
                found = true;
            }
            tempFile << serial << " " << name << " " << age << " "
                     << phone << " " << email << " " << balance << endl;
        }

        inFile.close();
        tempFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");

        if (!found) {
            cout << "\nAccount not found.\n";
        }
        returnMenu();
    }

    void deleteAccount() {
        string deleteSerial;
        cout << "Enter the 4-digit serial number to delete: ";
        cin >> deleteSerial;

        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        bool found = false;
        string serial, name, phone, email;
        int age;
        double balance;

        while (inFile >> serial >> name >> age >> phone >> email >> balance) {
            if (serial != deleteSerial) {
                tempFile << serial << " " << name << " " << age << " "
                         << phone << " " << email << " " << balance << endl;
            } else {
                found = true;
            }
        }

        inFile.close();
        tempFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");

        if (found) {
            cout << "\nAccount deleted successfully!\n";
        } else {
            cout << "\nAccount not found.\n";
        }
        returnMenu();
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n\t\t\033[1;34mBangladesh Bank\033[0m\n" << endl;
        cout << "1. Create Account\n";
        cout << "2. Search Account\n";
        cout << "3. Balance Query\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Take Loan\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.searchAccount(); break;
            case 3: bank.balanceQuery(); break;
            case 4: bank.depositMoney(); break;
            case 5: bank.withdrawMoney(); break;
            case 6: bank.takeLoan(); break;
            case 7: bank.deleteAccount(); break;
            case 8: cout << "Thanks for banking with us!\n"; exit(0);
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (true);

    return 0;
}
