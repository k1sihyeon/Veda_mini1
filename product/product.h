#pragma once

using namespace std;

class Product {
   private:
    static int _sharedId;   //singleton? 같은 클래스면 모두 접근 가능
    bool isInit = false;

   protected:
    int _id;
    string _name;
    int _price;
    string _category;
    string _company;
    int _totalPurchase;

   public:
    // generator
    Product();
    Product(string name, int price, string category, string company);

    // destructor
    ~Product();

    // getter
    int getId();
    string getName();
    int getPrice();
    string getCategory();
    string getCompany();
    int getTotalPurchase();

    // setter
    void setId(int id);
    void setName(string name);
    void setPrice(int price);
    void setCategory(string category);
    void setCompany(string company);
    void setTotalPurchase(int count);
    void increasePurchase();
    //_totalPurchase 변수 1 증가

    // id 생성
    int generateId();
    void initSharedId();
};