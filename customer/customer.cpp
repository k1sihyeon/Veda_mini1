#include "customer.h"

Customer::Customer(const string& id, const string& password, const string& name, bool gender)
    : userId(id), userPassword(password), userName(name), userGender(gender), totalPurchase(0){
};
Customer::~Customer() {};

string Customer::getUserId() const{
    return userId;
}
void Customer::setUserId(const string& id) {
    userId = id;
};
void Customer::setPassword(const string& password) {
    userPassword = password;
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