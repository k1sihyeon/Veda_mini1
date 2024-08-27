#include "customer.h"

string Customer::getUserId() const{
    return userId;
}
void Customer::setUserId(const string& id) {
    userId = id;
};
void Customer::setPassword(const string& password) {
    userPassword = password;
};
string Customer::hashPassword(const string& password) {
    return password; // make later
}
bool Customer::checkPassword(const string& password) {
    return password == this->userPassword; // fix later
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
