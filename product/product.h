#pragma once

#include <iostream>

using namespace std;

class Product {
   private:
    int _id;
    string _name;
    string _category;
    string _company;
    int _totalPurchase;

   public:
    // getter
    int getId();
    string getName();
    string getCategory();
    string getCompany();
    int getTotalPurchase();

    // setter
    void setId(int id);
    void setName(string name);
    void setCategory(string category);
    void setCompany(string company);
    void setTotalPurchase(int count);
    void increasePurchase();        //_totalPurchase 변수 1 증가

    // id 생성
    int generateId();
};