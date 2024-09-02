#include "customerGroupManager.h"
#include "customerManager.h"

#include <thread>
#include <chrono>


customerGroupManager* customerGroupManager::instance = nullptr;
customerGroupManager* customerGroupManager::getInstance() {
    if (instance == nullptr) {
        instance = new customerGroupManager();
    }
    return instance;
}

void customerGroupManager::showGroupManageSystem() {
    while (true) {

        int sel;
        cout << "\033[2J\033[1;1H";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "             Group Manage Menu               " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << "  1. Show Group list                         " << endl;
        cout << "                                             " << endl;
        cout << "  2. Change User's group                     " << endl;
        cout << "                                             " << endl;
        cout << "  3. Make Notice                             " << endl;
        cout << "                                             " << endl;
        cout << "  4. Quit                                    " << endl;
        cout << "                                             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << "  What do you wanna do? ";
        cin >> sel;

        switch (sel) {
        case 1:
            while (viewGroup());
            break;

        case 2: {
            changeUserGroup();
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

bool customerGroupManager::viewGroup() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 View Group                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Basic                                   " << endl;
    cout << "                                             " << endl;
    cout << "  2. Silver                                  " << endl;
    cout << "                                             " << endl;
    cout << "  3. Gold                                    " << endl;
    cout << "                                             " << endl;
    cout << "  4. Platinum                                " << endl;
    cout << "                                             " << endl;
    cout << "  5. Quit                                    " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  Select the group you want to view. ";
    int sel;
    cin >> sel;

    vector<Customer> customers;
    switch (sel) {
    case 1:
        customers = customerManager::getInstance()->getGroupList(Customer::Group::basic);
        break;
    case 2:
        customers = customerManager::getInstance()->getGroupList(Customer::Group::silver);
        break;
    case 3:
        customers = customerManager::getInstance()->getGroupList(Customer::Group::gold);
        break;
    case 4:
        customers = customerManager::getInstance()->getGroupList(Customer::Group::platinum);
        break;
    case 5:
        return false;
    default:
        cout << "Invalid selection." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    if (customers.empty()) {
        cout << "\033[2J\033[1;1H";
        cout << "No customers in this group." << endl;
        cout << endl;
    }
    else {
        cout << "\033[2J\033[1;1H";
        cout << "Customers in the selected group:" << endl;
        for (const Customer& customer : customers) {
            cout << "ID: " << customer.getUserId() << endl;
            cout << "Name: " << customer.getName() << endl;
            cout << "Phone Number: " << customer.getPhoneNumber() << endl;
            cout << "Address: " << customer.getAddress() << endl;
            cout << "Total Purchase: " << customer.getTotalPurchase() << endl;
            cout << "-------------------------------------" << endl;
            cout << endl;
        }
    }

    cout << "Press Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();  

    return true;

}

void customerGroupManager::changeUserGroup() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "          Updating User's Group              " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Enter the ID of the user you want to change group: ";
    string userId;
    cin >> userId;

    Customer* customer = customerManager::getInstance()->getCustomer(userId);
    if (customer == nullptr) {
        cout << "User not found." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return;
    }

    cout << "\033[2J\033[1;1H";
    cout << endl;
    cout << " " << customer->getUserId() << "'s Current Group : [ " << customer->groupToString(Customer::Group(customer->getGroup())) << " ]" << endl;
    cout << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Basic" << endl;
    cout << "                                             " << endl;
    cout << "  2. Silver" << endl;
    cout << "                                             " << endl;
    cout << "  3. Gold" << endl;
    cout << "                                             " << endl;
    cout << "  4. Platinum" << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  Select new group:";
    int groupSel;
    cin >> groupSel;

    Customer::Group newGroup;
    switch (groupSel) {
    case 1:
        newGroup = Customer::Group::basic;
        break;
    case 2:
        newGroup = Customer::Group::silver;
        break;
    case 3:
        newGroup = Customer::Group::gold;
        break;
    case 4:
        newGroup = Customer::Group::platinum;
        break;
    default:
        cout << "Invalid selection." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return;
    }

    customer->updateGroup(newGroup);
    customerManager::getInstance()->updateChangedUserInfo(*customer);
    cout << endl;
    cout << "User's group has been updated successfully." << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    
}

