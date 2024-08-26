#include <string>

#include "product.h"

using namespace std;

class Clothes : public Product {
   private:
    int size;
    string color;

    public:
    Clothes(string name, int price, string company, int size, string color)
     : Product(name, price, (string)"Clothes", company, 0), size(size), color(color) {}

    string getMoreDetails() override {
        return to_string(size) + "," + color;
    }

    int getSize() {
        return size;
    }

    string getColor() {
        return color;
    }

    void setSize(int size) {
        this->size = size;
    }

    void setColor(string color) {
        this->color = color;
    }
};