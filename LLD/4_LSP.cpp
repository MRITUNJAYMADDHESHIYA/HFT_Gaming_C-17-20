//liskov substitution principle
//Subclasses should be substitutable for their base classes without altering the correctness of the program.

//example:- non-withdrawal account(fixed account)--> withdrawal account(savings account, current account)

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Account {
public:
    virtual void deposit(double amount) = 0;
    virtual ~Account() = default;
};

class WithdrawableAccount : public Account {
public:
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public WithdrawableAccount {
private:
    double balance;
public:
    SavingAccount() : balance(0.0) {}

    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited $" << amount << " to Saving Account. New balance: $" << balance << endl;
    }

    void withdraw(double amount) override {
        if (amount > balance)
            cout << "Insufficient funds in Saving Account." << endl;
        else {
            balance -= amount;
            cout << "Withdrew $" << amount << " from Saving Account. New balance: $" << balance << endl;
        }
    }
};

class CurrentAccount : public WithdrawableAccount {
private:
    double balance;
public:
    CurrentAccount() : balance(0.0) {}

    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited $" << amount << " to Current Account. New balance: $" << balance << endl;
    }

    void withdraw(double amount) override {
        if (amount > balance)
            cout << "Insufficient funds in Current Account." << endl;
        else {
            balance -= amount;
            cout << "Withdrew $" << amount << " from Current Account. New balance: $" << balance << endl;
        }
    }
};

class FixedDepositAccount : public Account {
private:
    double balance;
public:
    FixedDepositAccount() : balance(0.0) {}

    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited $" << amount << " to Fixed Deposit Account. New balance: $" << balance << endl;
    }
};

class BankClient {
private:
    vector<Account*> accounts;
public:
    BankClient(const vector<Account*>& accs) : accounts(accs) {}

    void processTransactions() {
        for (Account* acc : accounts) {
            acc->deposit(1000);

            // only withdraw if the account supports it
            auto* withdrawable = dynamic_cast<WithdrawableAccount*>(acc);
            if (withdrawable) {
                withdrawable->withdraw(500);
            } else {
                cout << "Withdrawal not allowed for this account type." << endl;
            }
        }
    }
};

int main() {
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedDepositAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransactions();

    for (Account* acc : accounts)
        delete acc;
    delete client;

    return 0;
}
