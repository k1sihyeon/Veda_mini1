#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using std::string;

class Product;

class ProductManager {
   private:
    inline static ProductManager* instance;
    unordered_map<int, Product*> prodList;
    const string filepath = "./data/productList.csv";

   public:
    ProductManager();
    ~ProductManager();

    static ProductManager* getInstance() {
        if (instance == nullptr) {
            instance = new ProductManager();
        }

        return instance;
    }

    void addProduct(Product* prod);
    void deleteProduct(int id);
    Product* searchProductByID(int id);
    vector<Product *> searchProductByName(string name);
    vector<Product *> searchProductByCategory(string category);
    void printProduct(Product* prod);
    void printAll();
    void printList();

    void loadCSVfile();
    void saveCSVfile();
};