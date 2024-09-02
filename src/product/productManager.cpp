#include "productManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "book.cpp"
#include "clothes.cpp"
#include "computer.cpp"
#include "product.h"

using namespace std;

using std::ifstream;
using std::ofstream;

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
    if (prodList.count(id))
        return prodList[id];

    else
        return nullptr;
}

vector<Product*> ProductManager::searchProductByName(string name) {
    vector<Product*> v;

    if (prodList.empty()) {
        cout << "Product List is EMPTY!!" << endl;
        return v;
    }   

    for (const auto& p : prodList) {
        Product* tmp = p.second;

        if (tmp == nullptr)
            continue;

        if (tmp->getName() == name)
            v.push_back(tmp);
    }

    return v;
}

vector<Product*> ProductManager::searchProductByCategory(string category) {
    vector<Product*> v;

    if (this->prodList.empty()) {
        cout << "Product List is EMPTY!!" << endl;
        return v;
    }

    for (const auto& p : this->prodList) {
        Product* tmp = p.second;

        if (tmp == nullptr)
            continue;

        if (tmp->getCategory() == category)
            v.push_back(tmp);
    }

    return v;
}

void ProductManager::printProduct(Product* prod) {

    const int w = 9;

    cout << setw(w) << setfill(' ') << left << "ID" << ": " << setw(5) << setfill('0') << right << prod->getId() << " | ";
    cout << "Total Purchases :" << setw(5) << setfill(' ') << right << prod->getTotalPurchase() << endl;
    
    cout << setw(w) << setfill(' ') << left << "Category" << ": " << prod->getCategory() << " | " << "Name" << " : " << setw(20) << setfill(' ') << left << prod->getName() << endl;

    cout << setw(w) << setfill(' ') << left << "Price" << ": " << setw(7) << setfill(' ') << right << prod->getPrice() << "₩" << " | ";
    cout << "Maker : " << prod->getCompany() << endl;

    cout << prod->getMoreDetails(2) << "\n";

    cout << setw(50) << setfill('-') << " ";
    cout << endl;
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

    if (prodList.empty()) {
        cout << "Product List is EMPTY!!" << endl;
        return;
    }

    // totalPurchase가 많은 순서대로
    vector<pair<int, Product*>> tmp(prodList.begin(), prodList.end());

    sort(tmp.begin(), tmp.end(), [](const pair<int, Product*>& a, const pair<int, Product*>& b) -> bool {
        return a.second->getTotalPurchase() > b.second->getTotalPurchase();
    });

    for (const auto& pp : tmp) {
        Product* p = pp.second;
        if (p == nullptr)
            continue;
        this->printProduct(p);
    }
}

void ProductManager::loadCSVfile() {
    vector<vector<string>> data;
    ifstream file(filepath);

    cout << "[product.csv] Loading File..." << endl;

    if (!file.is_open()) {
        cout << "[product.csv] cannot open file : load" << endl;
        return;
    }

    cout << "[product.csv] File Open Success! (load)" << endl;

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

        if (row[0] == "Computer")
            tmp = Product::createProduct<Computer>(row[2], stoi(row[3]), row[4], row[6], stoi(row[7]), row[8]);
        
        if (row[0] == "Clothes")
            tmp = Product::createProduct<Clothes>(row[2], stoi(row[3]), row[4], stoi(row[6]), row[7]);
        
        if (row[0] == "Book")
            tmp = Product::createProduct<Book>(row[2], stoi(row[3]), row[4], row[6], stoi(row[7]), stoi(row[8]), row[9]);

        tmp->setId(stoi(row[1]));
        tmp->setTotalPurchase(stoi(row[5]));
        this->addProduct(tmp);
    }

    Product::setSharedID((int)data.size());
}

void ProductManager::saveCSVfile() {
    ofstream file(filepath, ios::trunc);
    // ios::trunc -> 파일 새로 생성

    cout << "[product.csv] Saving File..." << endl;
    if (!file.is_open()) {
        cout << "[product.csv] cannot open file in save" << endl;
        return;
    }

    if (prodList.empty()) {
        cout << "prodlist is empty!" << endl;
        cout << "[product.csv] cannot save file" << endl;
        file.close();
        return;
    }
    
    cout << "[product.csv] Opening File... (save)" << endl;

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

    cout << "[product.csv] File save success..!" << endl;
}

