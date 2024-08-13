#include "product.h"

Product::Product() {}
Product::Product(int id, string vendor, int price){
    this->productId = id;
    this->vendor = vendor;
    this->price = price;
}

int Product::getProductId()const{
    return this->productId;
}
string Product::getProductVendor()const{
    return this->vendor;
}
int Product::getPrice()const{
    return this->price;
}
