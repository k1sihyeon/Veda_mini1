#include "product.h"
#include <iostream>

using namespace std;

Product::Product() {
    _id = generateId();
    _totalPurchase = 0;
}

Product::Product(string name, int price, string category, string company) {
    _id = generateId();
    _name = name;
    _price = price;
    _category = category;
    _company = company;
    _totalPurchase = 0;
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

void Product::increasePurchase() {
    _totalPurchase += 1;
}

int Product::generateId() {
    if (!isInit)
        initSharedId();

    _sharedId += 1;
    return _sharedId;
}

void Product::initSharedId() {
    _sharedId = 0;
    isInit = true;
}