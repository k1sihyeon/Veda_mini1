#include "customerManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector> 
#include <limits>
#include "customer.h"
#include "customerGroupManager.h"
using namespace std;

Customer parseCustomerFromLine(const std::string& line);

bool customerManager::Login(const string& id, const string& pwd) {
    auto it = customermap.find(id);
    if (it != customermap.end()) {
        Customer customer = it->second;
        if (customer.checkPassword(pwd)) {
            // cout << "Login Success!" << endl;
            return true;
        }
        else
            cout << endl << endl << "  Incorrect Password" << endl;
    }
    else
        cout << endl << endl << "  ID not exist." << endl;
    return false;
}


void customerManager::showManageSystem() {
    while (true) {
        customerManager::getInstance()->getRegisteredUsers();

        int sel;
        cout << "\033[2J\033[1;1H";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "\033[1;33m";
        cout << "                 Manager Menu                " << endl;
        cout << "\033[0m";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << "  1. Show customers list                     " << endl;
        cout << "                                             " << endl;
        cout << "  2. Show user's info                        " << endl;
        cout << "                                             " << endl;
        cout << "  3. Manage group                            " << endl;
        cout << "                                             " << endl;
        cout << "  4. Quit                                    " << endl;
        cout << "                                             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << "  What do you wanna do? ";
        cin >> sel;

        switch (sel) {
        case 1:
            showUserList();
            break;
        case 2: {
            cout << "\033[A\033[2K";
            cout << "  Enter Id: ";
            string id;
            cin >> id;
            auto it = customermap.find(id);
            if (it != customermap.end()) {
                showUserInfo(it->second);
                cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "  Type q to return prev page : ";
                while (1) {
                    char c;
                    cin >> c;
                    if (c == 'q')
                        break;
                }
            }
            else 
                cout << "User not found." << endl;
            break;
        }
        case 3: {
            customerGroupManager::getInstance()->showGroupManageSystem();
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
        oss << "  " << input << " is fine?";
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
            oss << "  " << (result ? "Male" : "Female") << " is fine?";
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
        cout << "\033[A\033[2K";
        cout << "\033[A\033[2K";
        cout << "  Enter password(at least 7 characters)";
        cout << endl << "  : ";
        cin >> pw;
        if (pw.length() <= 6) {
            cout << "Password should be longer than 6 characters.\n";
            continue;
        }
        cout << endl << "  Enter again";
        cout << endl << "  : ";
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

bool customerManager::registerUser() {
    string id;
    while (true) {
        id = getInputWithConfirmation<string>("  Enter Id : ");
        if (customermap.find(id) != customermap.end()) {
            cout << endl;
            cout << "\033[1;33m";
            cout << "  ID already exists. Please enter another ID.\n";
            cout << "\033[0m";
            cout << endl;
        }
        else
            break;
    }
    string pw = getPasswordInput();
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    string name = getInputWithConfirmation<string>("  Enter your name : ");
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    bool gender = getInputWithConfirmation<bool>("  Check your gender [0:Female / 1:Male] : ");
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    string number = getInputWithConfirmation<string>("  Enter your phone Number : ");
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    string addr = getInputWithConfirmation<string>("  Enter your address : ");

    Customer customer(id, pw, name, gender, number, addr, 1);
    customermap.insert(make_pair(id, customer));
    cout << endl << endl;
    cout << "\033[1;33m";
    cout << "  Register Complete! Welcome!";
    cout << "\033[0m";
    cout << " Press ENTER to Prev Section" << endl;
    cin.ignore();
    getchar();


    ofstream fout;
    fout.open(filepath, ios::app);
    if (fout.is_open()) {
        fout << customer << endl;
        fout.close();
    }
    else {
        cout << "Unable to open file for writing." << endl;
    }
    userCount++;
    return false;
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
        remove(filepath.c_str());
        rename("temp.txt", filepath.c_str());

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
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "                  User List                  " << endl;
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    for (auto it : customermap) {   
            showUserInfo(it.second);  
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Type q to return prev page : ";
    cin.get();
}

void customerManager::showUserInfo(Customer& customer) {
    cout << "=============================================" << endl;
    cout << "  ID: " << customer.getUserId() << endl;
    cout << "  Name: " << customer.getName() << endl;
    cout << "  Gender: " << (customer.getGender() ? "Male" : "Female") << endl;
    cout << "  Phone Number: " << customer.getPhoneNumber() << endl;
    cout << "  Address: " << customer.getAddress() << endl;
    cout << "  Total Purchase: " << customer.getTotalPurchase() << endl;
    cout << "  [" << customer.groupToString(Customer::Group(customer.getGroup())) << "]" << endl;
}

void customerManager::updateUserInfo(Customer& customer) {



    cout << "\033[2J\033[1;1H";
    showUserInfo(customer);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "         Modify Personal Information         " << endl;
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;


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

        updateChangedUserInfo(customer);
    }
    else 
        cout << "User not found." << endl;
}


//file update
void customerManager::updateChangedUserInfo(Customer& customer) {
    ifstream fin(filepath);
    ofstream temp("temp.csv");
    string line;
    while (getline(fin, line)) {
        // 라인을 쉼표로 분할하여 ID를 추출
        istringstream ss(line);
        string token;
        getline(ss, token, ',');  // 첫 번째 토큰은 ID입니다.

        // ID가 일치하는지 확인
        if (token == customer.getUserId()) {
            temp << customer << endl;  // 일치하면 업데이트된 고객 정보 기록
        }
        else {
            temp << line << endl;  // 그렇지 않으면 원래 라인 기록
        }
    }
    fin.close();
    temp.close();
    remove(filepath.c_str());
    rename("temp.csv", filepath.c_str());

    // cout << "User info updated successfully." << endl;
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

vector<Customer> customerManager::getGroupList(Customer::Group group) {
    std::vector<Customer> groupList;

    for (const auto& pair : customermap) {
        const Customer& customer = pair.second;
        if (customer.getGroup() == group) {
            groupList.push_back(customer);
        }
    }
    return groupList;
}