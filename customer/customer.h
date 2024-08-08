#pragma once
#include <iostream>
using namespace std;

class Customer {
public :
    Customer(const string& id, const string& password, const string& name, bool gender);
    ~Customer();

    string getUserId() const;
    void setUserId(const string& id);

    // prohibit get password
    void setPassword(const string& newpassword);

    string getName() const;
    void setName(const string& name);

    bool getGender() const;
    void setGender(bool gender);

    string getPhoneNumber() const;
    void setPhoneNumber(const string& phoneNumber);
    
    string getAddress() const;
    void setAddress(const string& address);

    void printCustomerInfo() const;
    void changeCustomerInfo();

    int getTotalPurchase() const;
    void updateTotalPurchase(int amount);

private:
    string userId;
    string userPassword;
    string userName;
    bool userGender; // 0 female, 1 male
    
    string userPhoneNumber;
    string userAddress;

    int totalPurchase;
};

