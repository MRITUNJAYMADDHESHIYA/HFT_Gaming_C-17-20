#include<iostream>
#include<vector>
using namespace std;

//store account details
enum AccountType {SAVINGS, CHECKING, BUSINESS};

class BankAccount{
    private:
        string accountHolder;
        int    accountNumber;
        double balance;
        AccountType type;
    public:
        //constructor
        BankAccount(string name, int accNum, double initialBalance, AccountType accType){
            accountHolder = name;
            accountNumber = accNum;
            balance       = initialBalance;
            type          = accType;
        }

        //Deposit Money
        void deposit(double amount){
            if(amount > 0){
                balance += amount;
                cout<<"Deposited: $"<<amount<<endl;
            }else{
                cout<<"Invalid deposit amount!"<<endl;
            }
        }

        //withdraw money
        void withdraw(double amount){
            if(amount > 0 && amount <= balance){
                balance -= amount;
                cout<<"Withdrew: $"<<amount<<endl;
            }else{
                cout<<"Invalid withdrawal amount or insufficient funds!"<<endl;
            }
        }

        //Display account details
        void display(){
            cout<<"\nAccount Holder: "<<accountHolder<<endl;
            cout<<"Account Number: "<<accountNumber<<endl;
            cout<<"Balance: $"<<balance<<endl;
            cout<<"Account Type: ";
            switch(type){
                case SAVINGS: cout<<"SAVINGS"<<endl; break;
                case CHECKING: cout<<"CHECKING"<<endl; break;
                case BUSINESS: cout<<"BUSINESS"<<endl; break;
            }
        }

        //Get account number
        int getAccountNumber(){
            return accountNumber;
        }

        //account modification
        void AccountModification(string name, AccountType accType){
            accountHolder = name;
            type = accType;
        }
};

int main(){
    vector<BankAccount> accounts;

    while(true){
        
        cout<<"Bank Account Management System"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"1. Create Account"<<endl;
        cout<<"2. Deposit Money"<<endl;
        cout<<"3. Withdraw Money"<<endl;
        cout<<"4. Check Balance"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"6. Modify Account Details"<<endl;

        int choice;
        cout<<"Enter your choice: ";
        cin>>choice;   

        if(choice == 1){
            string name;
            int accNum;
            double initialBalance;
            cout<<"Enter Account Holder Name: ";    
            cin.ignore();
            getline(cin, name);
            cout<<"Enter Account Number: ";
            cin>>accNum;
            cout<<"Enter Initial Balance: $";
            cin>>initialBalance;
            cout<<"Enter Account Type (0: SAVINGS, 1: CHECKING, 2: BUSINESS): ";
            int typeInput; 
            cin>>typeInput;
            if(typeInput < 0 || typeInput > 2){
                cout<<"Invalid account type! Setting to SAVINGS by default."<<endl;
                typeInput = 0;
            }
            accounts.push_back(BankAccount(name, accNum, initialBalance, static_cast<AccountType>(typeInput)));
            cout<<"Account created successfully!\n"<<endl;
        }else if(choice == 2){
            int accNum;
            double amount;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;

            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    cout<<"Enter Deposit Amount: $";
                    cin>>amount;
                    acc.deposit(amount);
                    found = true;
                    break;
                }
            }if(!found){
                cout<<"Account not found!"<<endl;
            }
        }else if(choice == 3){
            int accNum;
            double amount;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;

            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    cout<<"Enter Withdrawal Amount: $";
                    cin>>amount;
                    acc.withdraw(amount);
                    found = true;
                    break;
                }
            }if(!found){
                cout<<"Account not found!"<<endl;
            }
        }else if(choice == 4){
            int accNum;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;
            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    acc.display();
                    found = true;
                    break;
                }
            }if(!found){
                cout<<"Account not found!"<<endl;
            }
        }else if(choice == 5){
            cout<<"Exiting the system. Goodbye!"<<endl;
            break;
        }else if(choice == 6){
            int accNum;
            string name;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;
            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    cout<<"Enter new Account Holder Name: ";    
                    cin.ignore();
                    getline(cin, name);
                    cout<<"Enter new Account Type (0: SAVINGS, 1: CHECKING, 2: BUSINESS): ";
                    int typeInput;
                    cin>>typeInput;
                    if(typeInput >= 0 && typeInput <= 2){
                        acc.AccountModification(name, static_cast<AccountType>(typeInput));
                    }else{
                        cout<<"Invalid account type! No changes made to account type."<<endl;
                    }
                    cout<<"Account details updated successfully!"<<endl;
                    found = true;
                    break;
                }
            }if(!found){
                cout<<"Account not found!"<<endl;
            }
        }
        
        
        else{
            cout<<"Invalid choice! Please try again."<<endl;
        }
        cout<<endl; //for better readability
    }
    return 0;
}   