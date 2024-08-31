#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> 

using namespace std;

bool isValidUsername(const string& username) {
    return !username.empty();  
}

bool isValidPassword(const string& password) {
    return password.length() >= 6; 
}

string getPassword() {
    string password;
    char ch;
    cout << "Enter a password: ";
    while ((ch = _getch()) != '\r') {  
        if (ch == '\b') {  
            if (!password.empty()) {
                cout << "\b \b";  
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void registerUser() {
    string username, password;

    cout << "Enter a username: ";
    cin >> username;

    if (!isValidUsername(username)) {
        cout << "Invalid username. Registration failed.\n";
        return;
    }

    password = getPassword();

    if (!isValidPassword(password)) {
        cout << "Password must be at least 6 characters long. Registration failed.\n";
        return;
    }

    ofstream outFile("file.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registration successful!\n";
}

bool loginUser() {
    string username, password, storedUser, storedPass;
    cout << "Enter your username: ";
    cin >> username;

    password = getPassword();

    ifstream inFile("file.txt");
    bool loginSuccess = false;

    while (inFile >> storedUser >> storedPass) {
        if (storedUser == username && storedPass == password) {
            loginSuccess = true;
            break;
        }
    }
    inFile.close();

    if (loginSuccess) {
        cout << "Login successful!\n";
    } else {
        cout << "Login failed! Invalid username or password.\n";
    }

    return loginSuccess;
}

int main() {
    while (true) {
        int choice;
        cout << "\n+---------------------------+\n";
        cout << "| 1. Register                |\n";
        cout << "| 2. Login                   |\n";
        cout << "| 3. Exit                    |\n";
        cout << "+---------------------------+\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "Welcome to the system!\n";
                }
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

