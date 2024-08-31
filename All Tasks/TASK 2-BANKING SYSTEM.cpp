#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(const string &t, double a) : type(t), amount(a) {}

    void printTransaction() const {
        cout << "| " << type << " | $" << amount << " |\n";
    }
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum, double bal) : accountNumber(accNum), balance(bal) {}

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "\n+-----------------------------------------+\n";
        cout << "|        Deposit successful!              |\n";
        cout << "|        New balance: $" << balance << "              |\n";
        cout << "+-----------------------------------------+\n";
    }

    void withdraw(double amount) {
        cout << "+-----------------------------------------+\n";
        if (balance >= amount) {
            balance -= amount;
            transactions.emplace_back("Withdrawal", amount);
            cout << "|     Withdrawal successful!              |\n";
            cout << "|     New balance: $" << balance << "                |\n";
        } else {
            cout << "|   Insufficient funds for withdrawal.    |\n";
        }
        cout << "+-----------------------------------------+\n";
    }

    void transfer(Account &toAccount, double amount) {
        if (balance >= amount) {
            withdraw(amount);
            toAccount.deposit(amount);
            cout << "|      Transfer successful!               |\n";
            cout << "+-----------------------------------------+\n";
        } else {
            cout << "|      Transfer failed.                   |\n";
            cout << "|      Insufficient funds.                |\n";
            cout << "+-----------------------------------------+\n";
        }
    }

    void printAccountDetails() const {
        cout << "+-----------------------------------------+\n";
        cout << "| Account Number: " << accountNumber << "                   |\n";
        cout << "| Balance: $" << balance << "                           |\n";
        cout << "| Recent Transactions:                          |\n";
        cout << "+-----------------------------------------+\n";
        for (const auto &transaction : transactions) {
            transaction.printTransaction();
        }
        cout << "+-----------------------------------------+\n";
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(const string &n, int id) : name(n), customerID(id) {}

    void openAccount(int accountNumber, double initialBalance) {
        accounts.emplace_back(accountNumber, initialBalance);
    }

    Account* getAccount(int accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void printCustomerDetails() const {
        cout << "+-----------------------------------------+\n";
        cout << "| Customer ID: " << customerID << "                       |\n";
        cout << "| Name: " << name << "                          |\n";
        cout << "| Accounts:                               |\n";
        cout << "+-----------------------------------------+\n";
        for (const auto &account : accounts) {
            account.printAccountDetails();
        }
    }

    int getCustomerID() const {
        return customerID;
    }
};

class Bank {
private:
    vector<Customer> customers;

public:
    void addCustomer(const string &name, int customerID) {
        customers.emplace_back(name, customerID);
    }

    Customer* findCustomer(int customerID) {
        for (auto &customer : customers) {
            if (customer.getCustomerID() == customerID) {
                return &customer;
            }
        }
        return nullptr;
    }

    void transfer(int fromCustomerID, int fromAccountNumber, int toCustomerID, int toAccountNumber, double amount) {
        Customer* fromCustomer = findCustomer(fromCustomerID);
        Customer* toCustomer = findCustomer(toCustomerID);

        if (fromCustomer && toCustomer) {
            Account* fromAccount = fromCustomer->getAccount(fromAccountNumber);
            Account* toAccount = toCustomer->getAccount(toAccountNumber);

            if (fromAccount && toAccount) {
                fromAccount->transfer(*toAccount, amount);
            } else {
                cout << "+-----------------------------------------+\n";
                cout << "| Transfer failed. Invalid account number.|\n";
                cout << "+-----------------------------------------+\n";
            }
        } else {
            cout << "+-----------------------------------------+\n";
            cout << "| Transfer failed. Invalid customer ID.   |\n";
            cout << "+-----------------------------------------+\n";
        }
    }
};

int main() {
    Bank bank;

    string customer1Name, customer2Name;
    int customer1ID, customer2ID;
    int customer1AccountNumber, customer2AccountNumber;
    double customer1InitialBalance, customer2InitialBalance;

    cout << "Enter first customer's name: ";
    getline(cin, customer1Name);
    cout << "Enter first customer's ID: ";
    cin >> customer1ID;
    cout << "Enter first customer's account number: ";
    cin >> customer1AccountNumber;
    cout << "Enter first customer's initial balance: $";
    cin >> customer1InitialBalance;

    cout << "\nEnter second customer's name: ";
    cin.ignore();
    getline(cin, customer2Name);
    cout << "Enter second customer's ID: ";
    cin >> customer2ID;
    cout << "Enter second customer's account number: ";
    cin >> customer2AccountNumber;
    cout << "Enter second customer's initial balance: $";
    cin >> customer2InitialBalance;

    bank.addCustomer(customer1Name, customer1ID);
    bank.addCustomer(customer2Name, customer2ID);


    Customer* customer1 = bank.findCustomer(customer1ID);
    Customer* customer2 = bank.findCustomer(customer2ID);

    if (customer1) {
        customer1->openAccount(customer1AccountNumber, customer1InitialBalance);
    }
    if (customer2) {
        customer2->openAccount(customer2AccountNumber, customer2InitialBalance);
    }


    double depositAmount, withdrawalAmount, transferAmount;

    cout << "\nEnter amount to deposit into " << customer1Name << "'s account: $";
    cin >> depositAmount;
    if (customer1) {
        Account* account1 = customer1->getAccount(customer1AccountNumber);
        if (account1) {
            account1->deposit(depositAmount);
        }
    }

    cout << "\nEnter amount to withdraw from " << customer1Name << "'s account: $";
    cin >> withdrawalAmount;
    if (customer1) {
        Account* account1 = customer1->getAccount(customer1AccountNumber);
        if (account1) {
            account1->withdraw(withdrawalAmount);
        }
    }

    cout << "\nEnter amount to transfer from " << customer1Name << "'s account to " << customer2Name << "'s account: $";
    cin >> transferAmount;
    if (customer1 && customer2) {
        bank.transfer(customer1ID, customer1AccountNumber, customer2ID, customer2AccountNumber, transferAmount);
    }

    if (customer1) {
        cout << "\n" << customer1Name << "'s Details:\n";
        customer1->printCustomerDetails();
    }
    if (customer2) {
        cout << "\n" << customer2Name << "'s Details:\n";
        customer2->printCustomerDetails();
    }

    return 0;
}
