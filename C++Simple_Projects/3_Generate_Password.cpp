#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;

string generatePassword(int length){
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+";
    string password;
    srand(time(0)); // Seed for random number generation

    for(int i = 0; i < length; i++){
        int index = rand() % characters.length();
        password += characters[index];
    }
    return password;
}

int main(){
    int length;
    cout << "Enter the desired length of the password: ";
    cin >> length;

    if(length < 6){
        cout << "Password length should be at least 6 characters.\n";
        return 1;
    }

    string password = generatePassword(length);
    cout << "Generated Password: " << password << endl;

    return 0;
}