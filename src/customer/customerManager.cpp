#include "customerManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector> 
#include "customer.h"
using namespace std;

Customer parseCustomerFromLine(const std::string& line);

bool customerManager::Login(const string& id, const string& pwd) {
    auto it = customermap.find(id);
    if (it != customermap.end()) {
        Customer customer = it->second;
        if (customer.checkPassword(pwd)) {
            cout << "Login Success!" << endl;
            return true;
        }
        else
            cout << "Incorrect Password" << endl;
    }
    else
        cout << "ID not exist." << endl;
    return false;
}


void customerManager::showManageSystem() {
    while (true) {
        cout << "Select mode:" << endl;
        cout << "1. Show customers list" << endl;
        cout << "2. Show user's info" << endl;
        cout << "3. Manage group" << endl;
        cout << "4. Quit" << endl;
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
                cout << "User not found." << endl;
            break;
        }
        case 3: {
            break;
        }
        case 4:
            cout << "Exiting system..." << endl;
            return;
        default:
            cout << "Invalid selection." << endl;
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
    customermap.insert(make_pair(id, customer));
    cout << "Register Complete! Welcome!";

    ofstream fout;
    fout.open("customersList.txt", ios::app);
    if (fout.is_open()) {
        fout << customer << endl;
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
                temp << line << endl;
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
    for (auto it : customermap) {
        cout << endl;
        cout << "==================================" << endl;
        cout << endl;
        showUserInfo(it.second);
        cout << endl;
        cout << "==================================" << endl;
        cout << endl;
    }
}

void customerManager::showUserInfo(Customer& customer) {
    cout << "ID: " << customer.getUserId() << endl;
    cout << "Name: " << customer.getName() << endl;
    cout << "Gender: " << (customer.getGender() ? "Male" : "Female") << endl;
    cout << "Phone Number: " << customer.getPhoneNumber() << endl;
    cout << "Address: " << customer.getAddress() << endl;
    cout << "Total Purchase: " << customer.getTotalPurchase() << endl;
    cout << "[" << Customer::Group(customer.getGroup()) << "]" << endl;
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

        ifstream fin(filepath);
        ofstream temp("temp.txt");
        string line;
        while (getline(fin, line)) {
            if (line.find(id) == string::npos) {
                temp << line << endl;
            }
            else {
                temp << customer << endl;
            }
        }
        fin.close();
        temp.close();
        remove(filepath.c_str());
        rename("temp.txt", filepath.c_str());

        cout << "User info updated successfully." << endl;
    }
    else 
        cout << "User not found." << endl;
}

customerManager* customerManager::instance = nullptr;
customerManager* customerManager::getInstance() {
    if (instance == nullptr) {
        instance = new customerManager();
    }
    return instance;
}


void customerManager::getRegisteredUsers() {
    try{
        ifstream file(filepath);
        if (!file.is_open()) {
            throw runtime_error("Could not open file");
        }
        string line;
        while (getline(file, line)) {
            try {
                Customer customer = parseCustomerFromLine(line);
                customerManager::getInstance()->addUser(customer);
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << e.what() << std::endl;
            }
        }

            file.close();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
    }
}

Customer parseCustomerFromLine(const std::string& line) {
    //if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
    if (line.empty() || std::all_of(line.begin(), line.end(), [](unsigned char c){ return std::isspace(c); })) {
    // 코드 본문...
        throw runtime_error("Empty or invalid line encountered.");
    }

    istringstream ss(line);
    string token;

    vector<string> tokens;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 8) {
        throw runtime_error("Invalid line format: Incorrect number of fields.");
    }

    string id = tokens[0];
    string password = tokens[1];
    string name = tokens[2];
    bool gender = (tokens[3] == "1");
    string phoneNumber = tokens[4];
    string address = tokens[5];
    int totalPurchase = stoi(tokens[6]);
    int group = stoi(tokens[7]);

    Customer customer(id, password, name, gender, phoneNumber, address);
    customer.updateTotalPurchase(totalPurchase);
    customer.updateGroup(group);

    return customer;
}


void customerManager::addUser(Customer& customer) {
    customermap.insert(make_pair(customer.getUserId(), customer));
    userCount++;
}