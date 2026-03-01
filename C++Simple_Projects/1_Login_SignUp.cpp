#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Information {
    string Username, Email, Password;
    string SearchName, SearchEmail, SearchPassword;
    fstream file;

public:
    void SignUp();
    void Login();
    void ForgotPassword();
};

void Information::SignUp() {
    cout << "\nEnter Your User Name: ";
    getline(cin, Username);
    cout << "Enter Your Email: ";
    getline(cin, Email);
    cout << "Enter Your Password: ";
    getline(cin, Password);

    file.open("loginData.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << Username << "\n" << Email << "\n" << Password << "\n";
        file.close();
        cout << "\nAccount Created Successfully!\n";
    } else {
        cout << "\nUnable to open file for writing.\n";
    }
}

void Information::Login() {
    cout << "\n------------ Login ------------\n";
    cout << "Enter Your User Name: ";
    getline(cin, SearchName);
    cout << "Enter Your Password: ";
    getline(cin, SearchPassword);

    bool found = false;
    file.open("loginData.txt", ios::in);
    if (file.is_open()) {
        while (getline(file, Username) && getline(file, Email) && getline(file, Password)) {
            if (Username == SearchName) {
                if (Password == SearchPassword) {
                    cout << "\nLogin Successful!\n";
                    cout << "Username: " << Username << "\nEmail: " << Email << "\n";
                } else {
                    cout << "\nIncorrect Password!\n";
                }
                found = true;
                break;
            }
        }
        file.close();

        if (!found)
            cout << "\nUser Not Found!\n";
    } else {
        cout << "\nUnable to open file for reading.\n";
    }
}

void Information::ForgotPassword() {
    cout << "\n------------ Forgot Password ------------\n";
    cout << "Enter Your Username: ";
    getline(cin, SearchName);
    cout << "Enter Your Email: ";
    getline(cin, SearchEmail);

    bool found = false;
    file.open("loginData.txt", ios::in);
    if (file.is_open()) {
        while (getline(file, Username) && getline(file, Email) && getline(file, Password)) {
            if (Username == SearchName) {
                if (Email == SearchEmail) {
                    cout << "\nAccount Found...\n";
                    cout << "Your Password is: " << Password << "\n";
                } else {
                    cout << "\nEmail Does Not Match!\n";
                }
                found = true;
                break;
            }
        }
        file.close();

        if (!found)
            cout << "\nUsername Not Found!\n";
    } else {
        cout << "\nUnable to open file for reading.\n";
    }
}

int main() {
    Information obj;
    int choice;

    while (true) {
        cout << "\n------------ Welcome to Login System ------------\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Flush newline

        switch (choice) {
            case 1:
                obj.SignUp();
                break;
            case 2:
                obj.Login();
                break;
            case 3:
                obj.ForgotPassword();
                break;
            case 4:
                cout << "\nExiting...\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please try again.\n";
                break;
        }
    }
}
