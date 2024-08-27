#pragma once

#include <iostream>
using namespace std;

class Product {
   protected:
    static int _sharedId;   //singleton? 같은 클래스면 모두 접근 가능

    int _id;
    string _name;
    int _price;
    string _category;
    string _company;
    int _totalPurchase;

   public:
    // constructor
    Product();
    Product(string name, int price, string category, string company, int total);

    // destructor
    ~Product();

    // product factory
    template <typename T, typename... Args>
    static T* createProduct(Args&&... args) {
        return new T(forward<Args>(args)...);
    }

    // getter
    int getId();
    string getName();
    int getPrice();
    string getCategory();
    string getCompany();
    int getTotalPurchase();
    virtual string getMoreDetails(int option = 0);  // 가상 함수: 상세 제품 클래스에서 구현되어야 함

    // setter
    void setId(int id);
    void setName(string name);
    void setPrice(int price);
    void setCategory(string category);
    void setCompany(string company);
    void setTotalPurchase(int count);
    void increasePurchase(int purchase = 1);    //_totalPurchase 변수 1 증가
    static void setSharedID(int id) {
        _sharedId = id;
    }

    // id 생성
    int generateId();
};