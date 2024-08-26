#pragma once

#include <unordered_map>

using namespace std;

class Product;

class ProductManager {
   private:
    inline static ProductManager* instance;
    unordered_map<int, Product*> prodList;

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
    Product* searchProduct(int id);
    void printProduct(Product* prod);

    void loadCSVfile();
    void saveCSVfile();
};