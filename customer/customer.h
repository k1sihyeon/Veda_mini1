#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Customer {
public :
    enum Group { basic, silver, gold, platinum };

    Customer() {};
    Customer(const string& id, const string& password, const string& name, bool gender, string phonenum, string address)
        : userId(id), userPassword(hashPassword(password)), userName(name), userGender(gender), totalPurchase(0), userGroup(Group::basic), userPhoneNumber(phonenum), userAddress(address) {
    };
    ~Customer() {};

    string getUserId() const;
    void setUserId(const string& id);

    // prohibit get password
    string hashPassword(const string& password);
    void setPassword(const string& password);
    bool checkPassword(const string& password);


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

    int getGroup() const;
    void updateGroup(int group);

    friend std::ostream& operator<<(std::ostream& os, const Customer& customer) {
        os << customer.userId << ',' << customer.userPassword << ',' << customer.userName << ','
            << customer.userGender << ',' << customer.userPhoneNumber << ',' << customer.userAddress 
            << ',' << customer.totalPurchase << ',' << customer.userGroup;
        return os;
    }
    


private:

    string userId;
    string userPassword;
    string userName;
    bool userGender; // 0 female, 1 male
    
    string userPhoneNumber;
    string userAddress;

    int totalPurchase;
    Group userGroup;
};

