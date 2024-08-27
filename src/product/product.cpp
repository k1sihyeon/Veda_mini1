#include "product.h"

using namespace std;

int Product::_sharedId = 0;

Product::Product() {
    // _id = generateId();
    // _totalPurchase = 0;
}

Product::Product(string name, int price, string category, string company, int total = 0) {
    _id = generateId();
    _name = name;
    _price = price;
    _category = category;
    _company = company;
    _totalPurchase = total;
}

Product::~Product() {

}

int Product::getId() {
    return _id;
}

string Product::getName() {
    return _name;
}

int Product::getPrice() {
    return _price;
}

string Product::getCategory() {
    return _category;
}

string Product::getCompany() {
    return _company;
}

int Product::getTotalPurchase() {
    return _totalPurchase;
}

string Product::getMoreDetails(int option) {
    return "";
}

void Product::setId(int id) {
    _id = id;
}

void Product::setName(string name) {
    _name = name;
}

void Product::setCategory(string category) {
    _category = category;
}

void Product::setCompany(string company) {
    _company = company;
}

void Product::setTotalPurchase(int count) {
    _totalPurchase = count;
}

void Product::increasePurchase(int purchase) {
    if (purchase <= 0)
        return;
    _totalPurchase += purchase;
}

int Product::generateId() {
    _sharedId += 1;
    return _sharedId;
}