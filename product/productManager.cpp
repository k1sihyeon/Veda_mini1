#include "productManager.h"
#include "product.h"
#include "computer.cpp"
#include "clothes.cpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

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

Product* ProductManager::searchProduct(int id) {
    return prodList[id];
}

//prod 카테고리 선택 및 보여주기 + order

void ProductManager::printProduct(Product* prod) {
    cout << prod->getName() << " " << prod->getMoreDetails() << endl;
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

    for (auto& row : data) {
        Product* tmp;

        if (row[0] == "Computer") {   
            tmp = Product::createProduct<Computer>(row[2], stoi(row[3]), row[4], row[6], stoi(row[7]), row[8]);
            
        }
        else if (row[0] == "Clothes") {
            tmp = Product::createProduct<Clothes>(row[2], stoi(row[3]), row[4], stoi(row[6]), row[7]);
        }

        tmp->setId(stoi(row[1]));
        tmp->setTotalPurchase(stoi(row[5]));
        addProduct(tmp);
    }

    Product::setSharedID((int)data.size());
}

void ProductManager::saveCSVfile() {
    ofstream file("product.csv", std::ios::trunc);
    //ios::trunc -> 파일 새로 생성
    
    if (!file.is_open()) {
        cout << "cannot open file : save" << endl;
        return;
    }
    
    for (auto& p : prodList) {
        Product* prod = p.second;

        file << prod->getCategory() << ",";
        file << prod->getId() << ",";
        file << prod->getName() << ",";
        file << prod->getPrice() << ",";
        file << prod->getCompany() << ",";
        file << prod->getTotalPurchase() << ",";
        file << prod->getMoreDetails() << endl;
    }

    file.close();
}
