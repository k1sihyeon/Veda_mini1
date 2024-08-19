#include "customerManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "customer.h"
using namespace std;


void customerManager::showManageSystem() {
    while (true) {
        cout << "Select mode:" << '\n';
        cout << "1. Show customers list" << '\n';
        cout << "2. Show user's info" << '\n';
        cout << "3. Register user" << '\n';
        cout << "4. Delete user" << '\n';
        cout << "5. Change user info" << '\n';
        cout << "6. Quit" << '\n';
        int sel;
        cin >> sel;

        switch (sel) {
        case 1:
            showUserList();
            break;
        case 2: {
            cout << "Enter Id: ";
            string id;
            cin >> id;
            auto it = customermap.find(id);
            if (it != customermap.end()) {
                showUserInfo(it->second);
            }
            else 
                cout << "User not found." << '\n';
            break;
        }
        case 3:
            registerUser();
            break;
        case 4: {
            cout << "Enter Id: ";
            string id;
            cin >> id;
            auto it = customermap.find(id);
            if (it != customermap.end()) {
                deleteUser(it->second);
            }
            else
                cout << "User not found." << '\n';
            break;
        }
        case 5: {
            cout << "Enter Id: ";
            string id;
            cin >> id;
            auto it = customermap.find(id);
            if (it != customermap.end()) {
                updateUserInfo(it->second);
            }
            else
                cout << "User not found." << '\n';
            break;
        }
        case 6:
            cout << "Exiting system..." << '\n';
            return;
        default:
            cout << "Invalid selection." << '\n';
            break;
        }
    }
}

bool confirmInput(const string& prompt) {
    char sel;
    cout << prompt << " [Y/N]: ";
    cin >> sel;
    return sel == 'Y' || sel == 'y';
}

template <class T>
T getInputWithConfirmation(const string& prompt) {
    T input;
    while (true) {
        cout << prompt;
        string strInput;
        cin >> strInput;

        std::istringstream iss(strInput);
        if (!(iss >> input)) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        std::ostringstream oss;
        oss << input << " is fine?";
        if (confirmInput(oss.str())) {
            break;
        }
    }
    return input;
}


template <>
bool getInputWithConfirmation<bool>(const string& prompt) {
    while (true) {
        cout << prompt;
        string strInput;
        cin >> strInput;

        if (strInput == "0" || strInput == "1") {
            bool result = strInput == "1";
            std::ostringstream oss;
            oss << (result ? "Male" : "Female") << " is fine?";
            if (confirmInput(oss.str())) {
                return result;
            }
        }
        else {
            cout << "Please enter 0 for Female or 1 for Male.\n";
        }
    }
}

string getPasswordInput() {
    string pw, pw2;
    while (true) {
        cout << "Enter password (at least 6 characters): ";
        cin >> pw;
        if (pw.length() <= 6) {
            cout << "Password should be longer than 6 characters.\n";
            continue;
        }
        cout << "Enter again: ";
        cin >> pw2;
        if (pw != pw2) {
            cout << "Passwords do not match. Please try again.\n";
        }
        else {
            break;
        }
    }
    return pw;
}

void customerManager::registerUser() {
    string id;
    while (true) {
        id = getInputWithConfirmation<string>("Enter Id : ");
        if (customermap.find(id) != customermap.end()) {
            cout << "ID already exists. Please enter another ID.\n";
        }
        else
            break;
    }
    string pw = getPasswordInput();
    string name = getInputWithConfirmation<string>("Enter your name : ");
    bool gender = getInputWithConfirmation<bool>("Check your gender [ 0 : Female / 1 : male ] : ");
    string number = getInputWithConfirmation<string>("Enter your phone Number : ");
    string addr = getInputWithConfirmation<string>("Enter your address : ");

    Customer customer(id, pw, name, gender, number, addr);
    customermap[id] = customer;
    cout << "Register Complete! Welcome!";

    ofstream fout;
    fout.open("customersList.txt", ios::app);
    if (fout.is_open()) {
        fout << customer << '\n';
        fout.close();
    }
    else {
        cout << "Unable to open file for writing." << endl;
    }
    userCount++;
}


void customerManager::deleteUser(Customer& customer) {
    string id = customer.getUserId();
    auto it = customermap.find(id);
    if (it != customermap.end()) {
        customermap.erase(it); 

        ifstream fin("customersList.txt");
        ofstream temp("temp.txt");
        string line;
        while (getline(fin, line)) {
            if (line.find(id) == string::npos) {
                temp << line << '\n';
            }
        }
        fin.close();
        temp.close();
        remove("customersList.txt");
        rename("temp.txt", "customersList.txt");

        cout << "User " << id << " deleted successfully." << endl;
        userCount--;
    }
    else {
        cout << "User not found." << endl;
    }
}


void customerManager::showUserList() {
    if (customermap.empty()) {
        cout << "No users registered." << endl;
        return;
    }

    vector<Customer> customers;
    for (const auto& pair : customermap) {
        customers.push_back(pair.second);
    }

    /* 필터나 소팅 기준 주는 기능 구현하기
    sort(customers.begin(), customers.end(), [](const Customer& a, const Customer& b) {
        if (a.getTotalPurchase() == b.getTotalPurchase()) {
            return a.getName() < b.getName();
        }
        return a.getTotalPurchase() > b.getTotalPurchase();
        });
       */
    cout << "User List:" << endl;
    for (const auto& customer : customers) {
        cout << customer << endl;
    }
}

void customerManager::showUserInfo(Customer& customer) {
    cout << "User Info:" << '\n';
    cout << "ID: " << customer.getUserId() << '\n';
    cout << "Name: " << customer.getName() << '\n';
    cout << "Gender: " << (customer.getGender() ? "Male" : "Female") << '\n';
    cout << "Phone Number: " << customer.getPhoneNumber() << '\n';
    cout << "Address: " << customer.getAddress() << '\n';
    cout << "Total Purchase: " << customer.getTotalPurchase() << '\n';
    cout << "You are in [ " << customer.getGroup() << " ] group. << '\n";
}

void customerManager::updateUserInfo(Customer& customer) {
    string id = customer.getUserId();
    if (customermap.find(id) != customermap.end()) {
        cout << "Updating info for user " << id << endl;

        string newName = getInputWithConfirmation<string>("Enter new name: ");
        bool newGender = getInputWithConfirmation<bool>("Check your gender [ 0 : Female / 1 : male ] : ");
        string newNumber = getInputWithConfirmation<string>("Enter new phone Number: ");
        string newAddr = getInputWithConfirmation<string>("Enter new address: ");

        customer.setName(newName);
        customer.setGender(newGender);
        customer.setPhoneNumber(newNumber);
        customer.setAddress(newAddr);
        customermap[id] = customer;

        ifstream fin("customersList.txt");
        ofstream temp("temp.txt");
        string line;
        while (getline(fin, line)) {
            if (line.find(id) == string::npos) {
                temp << line << '\n';
            }
            else {
                temp << customer << '\n';
            }
        }
        fin.close();
        temp.close();
        remove("customersList.txt");
        rename("temp.txt", "customersList.txt");

        cout << "User info updated successfully." << endl;
    }
    else 
        cout << "User not found." << endl;
}


