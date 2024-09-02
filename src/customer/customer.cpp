#include "customer.h"

string Customer::getUserId() const{
    return userId;
}
void Customer::setUserId(const string& id) {
    userId = id;
};

string Customer::hashPassword(const string& password) {
    unsigned long hash = 0;
    for (char c : password) {
        hash = hash * 31 + c;
    }
    return std::to_string(hash);
}

bool Customer::checkPassword(const string& password) {
    return hashPassword(password) == this->userPassword;
};



string Customer::getName() const {
    return userName;
};
void Customer::setName(const string& name) {
    userName = name;
};
bool Customer::getGender() const {
    return userGender;
}
void Customer::setGender(bool gender) {
    userGender = gender;
}
string Customer::getPhoneNumber() const {
    return userPhoneNumber;
}
void Customer::setPhoneNumber(const string& phoneNumber) {
    userPhoneNumber = phoneNumber;
}
string Customer::getAddress() const {
    return userAddress;
}
void Customer::setAddress(const string& address) {
    userAddress = address;
}

int Customer::getTotalPurchase() const {
    return totalPurchase;
}
void Customer::updateTotalPurchase(int amount) {
    totalPurchase += amount;
}

int Customer::getGroup() const {
    return userGroup;
}

void Customer::updateGroup(int group) {
    userGroup = Group(group);
}

string Customer::groupToString(Group group) {
    switch (group) {
    case Group::basic: return "Basic";
    case Group::gold: return "Gold";
    case Group::platinum: return "Platinum";
    case Group::silver: return "Silver";
    default: return "Unknown";
    }
}
