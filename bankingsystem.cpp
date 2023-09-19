//i have taken help from multiple sources to learn and complete this...
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib> 

using namespace std;
class Account {
private:
    int password;
    int balance;
public:
    int accountNum; 
    string name;

    
    static int lastAssignedAccountNum;

    
    Account(string Name) {
        name = Name;
        accountNum = ++lastAssignedAccountNum;
        password = 0; 
        balance = 0; 
    }

    void setBalance(int balance1) {
        if (balance1 > 0) {
            balance += balance1;
        } else if (balance1 < 0) {
            if (-balance1 <= balance) {
                balance += balance1;
            } else {
                cout << "Transaction not possible, insufficient funds." << endl;
            }
        }
    }

    int getBalance() {
        return balance;
    }

    void setPassword(int password1) {
        if (password == 0 && password1 >= 1000 && password1 <= 9999) {
            password = password1;
        } else {
            cout << "Pin should be a 4-digit positive number." << endl;
        }
    }

    int getPassword() {
        return password;
    }

    void create() {
        fstream fout;
        fout.open("accountDetails.csv", ios::out | ios::app);

        if (!fout.is_open()) {
            cerr << "Failed to open the file." << endl;
            return;
        }

        fout << name << ", "
             << accountNum << ", "
             << password << ", "
             << balance << ", "
             << "\n";

        fout.close();
    }

    void readRecord() {
        fstream fin;
        fin.open("accountDetails.csv", ios::in);

        if (!fin.is_open()) {
            cerr << "Failed to open the file." << endl;
            return;
        }

        int accountNum2, count = 0;
        cout << "Enter the account number: ";
        cin >> accountNum2;

        vector<string> row;
        string line, word, temp;

        while (getline(fin, line)) {
            row.clear();
            stringstream s(line);

            while (getline(s, word, ',')) {
                row.push_back(word);
            }

            accountNum = stoi(row[1]);

            if (accountNum == accountNum2) {
                count = 1;
                cout << "Details of account number " << row[1] << " : " << endl;
                cout << "Name: " << row[0] << endl;
                cout << "Password: " << row[2] << endl;
                cout << "Balance: " << row[3] << endl;
                break;
            }
        }

        if (count == 0) {
            cout << "Record not found." << endl;
        }

        fin.close();
    }

    bool updateRecordTransaction(int amount) {
        fstream fin, fout;
        fin.open("accountDetails.csv", ios::in);

        if (!fin.is_open()) {
            cerr << "Failed to open the file." << endl;
            return false;
        }

        fout.open("accountDetails2.csv", ios::out);

        int accountNum4, count = 0;
        string line, word;
        vector<string> row;

        cout << "Enter your account number: ";
        cin >> accountNum4;

        while (getline(fin, line)) {
            row.clear();
            stringstream s(line);

            while (getline(s, word, ',')) {
                row.push_back(word);
            }

            accountNum = stoi(row[1]);

            if (accountNum == accountNum4) {
                count = 1;
                int currentBalance = atoi(row[3].c_str());
                int newBalance = currentBalance + amount;

                if (newBalance >= 0) {
                    stringstream convert;
                    convert << newBalance;
                    row[3] = convert.str();
                } else {
                    cout << "Transaction not possible, insufficient funds." << endl;
                    fin.close();
                    fout.close();
                    return false;
                }
            }

            for (size_t i = 0; i < row.size(); ++i) {
                fout << row[i];
                if (i < row.size() - 1) {
                    fout << ',';
                }
            }

            fout << '\n';
        }

        if (count == 0) {
            cout << "Record not found." << endl;
            fin.close();
            fout.close();
            return false;
        }

        fin.close();
        fout.close();

        remove("accountDetails.csv");
        rename("accountDetails2.csv", "accountDetails.csv");

        return true;
    }

    static bool transferFunds(int fromAccountNum, int toAccountNum, int amount) {
        Account sender("Sender"); 
        Account receiver("Receiver");

        if (!sender.updateRecordTransaction(-amount)) {
            cout << "Transaction failed: Sender does not have sufficient funds." << endl;
            return false;
        }

        if (!receiver.updateRecordTransaction(amount)) {
            
            sender.updateRecordTransaction(amount);
            cout << "Transaction failed: Receiver's account not found." << endl;
            return false;
        }

        cout << "Transaction successful: " << amount << " transferred from Account " << fromAccountNum << " to Account " << toAccountNum << endl;

        return true;
    }
};




int Account::lastAssignedAccountNum = 0;

int main() {
    char command;
    string name;
    int password, initialAmount, transactionAmount, fromAccountNum, toAccountNum;

    cout << "Welcome to IITI Bank" << endl;

    Account user("Temporary");

    do {
        cout << "Choose an option:" << endl;
        cout << "n - Open a new account" << endl;
        cout << "b - Check balance" << endl;
        cout << "d - Deposit cash" << endl;
        cout << "w - Withdraw cash" << endl;
        cout << "t - Transfer money" << endl;
        cout << "e - Exit" << endl;

        cin >> command;

        switch (command) {
            case 'n':
                cout << "Enter your name: ";
                cin >> name;
                cout << "Create a 4-digit PIN: ";
                cin >> password;
                user = Account(name); 
                user.setPassword(password);
                cout << "Enter initial amount: ";
                cin >> initialAmount;
                user.setBalance(initialAmount);
                user.create();
                cout << "Your account number is: " << user.accountNum << endl;
                break;
            case 'b':
                user.readRecord();
                break;
            case 'd':
                cout << "Enter the amount to deposit: ";
                cin >> transactionAmount;
                user.updateRecordTransaction(transactionAmount);
                cout << "Transaction successful: Deposit of " << transactionAmount << " done." << endl;
                break;
            case 'w':
                cout << "Enter the amount to withdraw: ";
                cin >> transactionAmount;
                transactionAmount = -transactionAmount; 
                if (user.updateRecordTransaction(transactionAmount)) {
                    cout << "Transaction successful: Withdrawal of " << (-transactionAmount) << " done." << endl;
                }
                break;
            case 't':
                cout << "Enter your account number: ";
                cin >> fromAccountNum;
                cout << "Enter the recipient's account number: ";
                cin >> toAccountNum;
                cout << "Enter the amount to transfer: ";
                cin >> transactionAmount;
                if (Account::transferFunds(fromAccountNum, toAccountNum, transactionAmount)) {
                    cout << "Transaction successful: Transfer of " << transactionAmount << " done." << endl;
                }
                break;
            case 'e':
                cout << "Thank you for visiting us!" << endl;
                break;
            default:
                cout << "Invalid command. Please try again." << endl;
        }
    } while (command != 'e');

    return 0;
}
