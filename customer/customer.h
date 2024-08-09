#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Customer {
public :
    Customer(const string& id, const string& password, const string& name, bool gender);
    ~Customer();

    int getUniqueId() const;
    void setUniqueId(int id);

    string getUserId() const;
    void setUserId(const string& id);

    // prohibit get password
    void setPassword(const string& password);

    string getName() const;
    void setName(const string& name);

    bool getGender() const;
    void setGender(bool gender);

    string getPhoneNumber() const;
    void setPhoneNumber(const string& phoneNumber);
    
    string getAddress() const;
    void setAddress(const string& address);

    int getTotalPurchase() const;
    void updateTotalPurchase(int amount);

private:
    int uniqueId; // manager gives it 
    string userId;
    string userPassword;
    string userName;
    bool userGender; // 0 female, 1 male
    
    string userPhoneNumber;
    string userAddress;

    int totalPurchase;
};

