#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;
class Product
{
public:
    Product();
    Product(int, string, int);
    int getProductId() const;
    string getProductVendor() const;
    int getPrice() const;
private:
    int productId;
    string vendor;
    int price;
};

#endif // PRODUCT_H
