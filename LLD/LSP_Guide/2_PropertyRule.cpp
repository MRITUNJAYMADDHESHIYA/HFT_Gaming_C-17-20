//////////1.class invariant
//class invariant of a parent class should not be violated by a child class
#include <iostream>
#include <stdexcept>

//invariant: balance should never be negative
class BankAccount{
    protected:
        double balance;
    public:
        BankAccount(double b){
            if(b < 0){
                throw std::invalid_argument("Initial balance cannot be negative");
            }
            balance = b;
        }

        virtual void withdraw(double amount){
            if(balance - amount < 0){
                throw std::runtime_error("Insufficient funds");
            }
            balance -= amount;
            std::cout<< "Amount withdrawn. Remaining balance: " << balance <<std::endl;
        }
};

//Breakes invariant : should not be allowed(but here it's break)
class CheatAccount : public BankAccount{
    public:
        CheatAccount(double b): BankAccount(b) {}

        void withdraw(double amount) override {
            //Cheat by allowing overdraft
            balance -= amount;
            std::cout<< "Cheat Withdrawn amount: " << amount << ". New balance: " << balance <<std::endl;
        }
};

int main(){
    BankAccount* account = new BankAccount(100);
    account->withdraw(50); //valid

    return 0;
}

////////2.History constraint rule
//methods in child class should not break history constraints of parent class

class BankAccountHistory{
    protected:
        double balance;
    public:
        BankAccountHistory(double b){
            if(b < 0){
                throw std::invalid_argument("Initial balance cannot be negative");
            }
            balance = b;
        }

        //History constraint: withdraw should be allowed
        virtual void withdraw(double amount){
            if(balance - amount < 0){
                throw std::runtime_error("Insufficient funds");
            }
            balance -= amount;
            std::cout<< "Amount withdrawn. Remaining balance: " << balance <<std::endl;
        }
};

class FixedDepositAccountHistory : public BankAccountHistory{
    public:
        FixedDepositAccountHistory(double b): BankAccountHistory(b) {}

        //LSP violation: breaks history constraint
        //parent class behavior is changed : now withdraw is not allow
        void withdraw(double amount) override {
            throw std::runtime_error("Withdrawals not allowed on Fixed Deposit Account");
        }
};

int main(){
    BankAccountHistory* bankaccount = new BankAccountHistory(100);
    bankaccount->withdraw(46);

    return 0;
}

//immutable class:- we can't inheritance this class
//immutable methods:- we can't override 