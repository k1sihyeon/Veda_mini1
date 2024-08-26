#include "productManager.h"
#include "product.h"
#include "computer.cpp"
#include "clothes.cpp"
#include "book.cpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

ProductManager::ProductManager() {
    Product::setSharedID(0);
    this->loadCSVfile();
}

ProductManager::~ProductManager() {
    this->saveCSVfile();
}

void ProductManager::addProduct(Product* prod) {
    prodList.insert(make_pair(prod->getId(), prod));
}

void ProductManager::deleteProduct(int id) {
    prodList.erase(id);
}

Product* ProductManager::searchProductByID(int id) {
    return prodList[id];
}

std::vector<Product *> ProductManager::searchProductByName(string name) {
    std::vector<Product *> v;
    
    for (const auto& p : prodList) {
        Product *tmp = p.second;

        if (tmp->getName() == name)
            v.push_back(tmp);
    }

    return v;
}

vector<Product *> ProductManager::searchProductByCategory(string category) {
    vector<Product *> v;
    
    for (const auto& p : prodList) {
        Product *tmp = p.second;

        if (tmp->getCategory() == category)
            v.push_back(tmp);
    }

    return v;
}

//prod 카테고리 선택 및 보여주기 + order

void ProductManager::printProduct(Product* prod) {
    cout << prod->getName() << " " << prod->getMoreDetails() << endl;
}

void ProductManager::printAll() {
    for (const auto& p : prodList) {
        Product* prod = p.second;

        cout << prod->getCategory() << ",";
        cout << prod->getId() << ",";
        cout << prod->getName() << ",";
        cout << prod->getPrice() << ",";
        cout << prod->getCompany() << ",";
        cout << prod->getTotalPurchase() << ",";
        cout << prod->getMoreDetails() << endl;
    }
}

void ProductManager::printList() {
    //totalPurchase가 많은 순서대로
    vector<pair<int, Product *>> tmp(prodList.begin(), prodList.end());
    
    sort(tmp.begin(), tmp.end(), []
    (const pair<int, Product *>& a, const pair<int, Product *>& b) -> bool {
        return a.second->getTotalPurchase() > b.second->getTotalPurchase();
    });

    for (const auto& pp : tmp) {
        Product *p = pp.second;
        this->printProduct(p);
    }
}

void ProductManager::loadCSVfile() {
    vector<vector<string>> data;
    ifstream file("product.csv");

    if (!file.is_open()) {
        cout << "cannot open file : load" << endl;
        return;
    }

    string line, word;
    while (getline(file, line)) {
        vector<string> row;
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        data.push_back(row);
    }

    file.close();

    for (const auto& row : data) {
        Product* tmp;

        if (row[0] == "Computer") {   
            tmp = Product::createProduct<Computer>(row[2], stoi(row[3]), row[4], row[6], stoi(row[7]), row[8]);
        }
        if (row[0] == "Clothes") {
            tmp = Product::createProduct<Clothes>(row[2], stoi(row[3]), row[4], stoi(row[6]), row[7]);
        }

        tmp->setId(stoi(row[1]));
        tmp->setTotalPurchase(stoi(row[5]));
        this->addProduct(tmp);
    }

    Product::setSharedID((int)data.size());
}

void ProductManager::saveCSVfile() {
    ofstream file("product.csv", ios::trunc);
    //ios::trunc -> 파일 새로 생성
    
    cout << "[save] opening File..." << endl;
    if (!file.is_open()) {
        cout << "[save] cannot open file : save" << endl;
        return;
    }

    cout << "[save] File open success..!" << endl;

    if (prodList.empty())
        cout << "prodlist is empty!" << endl;
    
    for (const auto& p : prodList) {
        Product* prod = p.second;

        file << prod->getCategory() << ",";
        file << prod->getId() << ",";
        file << prod->getName() << ",";
        file << prod->getPrice() << ",";
        file << prod->getCompany() << ",";
        file << prod->getTotalPurchase() << ",";
        file << prod->getMoreDetails() << "\n";
    }

    file.close();
}
