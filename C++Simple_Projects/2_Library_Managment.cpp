#include<iostream>
#include<fstream>
using namespace std;

class LibraryManagement{
    private:
        string id;
        string name;
        string author;
        string search;
        fstream file;

    public:
        void addBook();
        void searchBook();
        void deleteBook();

};

void LibraryManagement::addBook(){
    cout<< "\nEnter Book ID: ";
    getline(cin, id);
    cout<<"\nEnter Book Name: ";
    getline(cin, name);
    cout<<"\nEnter Book Author: ";
    getline(cin, author);

    file.open("loginData1.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << id << "\n" << name << "\n" << author << "\n";
        file.close();
        cout << "\nBook Added Successfully!\n";
    } else {
        cout << "\nUnable to open file for writing.\n";
    }
}

void LibraryManagement::searchBook(){
    cout<<"\nEnter Book ID to Search: ";
    getline(cin, search);

    bool found = false;
    file.open("loginData1.txt", ios::in);
    if (file.is_open()) {
        while(getline(file, id) && getline(file, name) && getline(file, author)) {
            if (id == search) {
                cout << "\nBook Found!\n";
                cout << "ID: " << id << "\nName: " << name << "\nAuthor: " << author << "\n";
                found = true;
                break;
            }else{
                cout<<"\nBook Not Found!\n";
            }
        }
        file.close();
    } else {
        cout << "\nUnable to open file for reading.\n";
    }
}

void LibraryManagement::deleteBook(){
    cout << "\nEnter Book ID to Delete: ";
    getline(cin, search); // fix: input into 'search'

    fstream tempFile;
    tempFile.open("temp.txt", ios::out);
    file.open("loginData1.txt", ios::in);

    if (file.is_open() && tempFile.is_open()) {
        bool found = false;

        while (getline(file, id) && getline(file, name) && getline(file, author)) {
            if (id != search) {
                tempFile << id << "\n" << name << "\n" << author << "\n";
            } else {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        if (found) {
            remove("loginData1.txt");         // delete old file
            rename("temp.txt", "loginData1.txt"); // rename new file
            cout << "\nBook Deleted Successfully!\n";
        } else {
            remove("temp.txt"); // clean up if nothing deleted
            cout << "\nBook Not Found!\n";
        }
    } else {
        cout << "\nUnable to open file for reading or writing.\n";
    }
}


int main(){
    LibraryManagement lib;
    int choice;

    while(true){
        cout<<"\n------------ Library Management System ------------\n";
        cout<<"1. Add Book\n";
        cout<<"2. Search Book\n";
        cout<<"3. Delete Book\n";
        cout<<"4. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore(); // Flush newline

        switch(choice){
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.searchBook();
                break;
            case 3:
                lib.deleteBook();
                break;
            case 4:
                cout<<"\nExiting...\n";
                return 0;
            default:
                cout<<"\nInvalid Choice! Please try again.\n";
        }
    }
}