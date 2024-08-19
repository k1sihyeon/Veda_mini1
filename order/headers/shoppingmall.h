#ifndef SHOPPINGMALL_H
#define SHOPPINGMALL_H

class ClientShoppingMall;
class SellerShoppingMall;

class ShoppingMall
{
public:
    ShoppingMall();
    ~ShoppingMall();
    bool startShoppingMall();
private:
    ClientShoppingMall *CSM;
    SellerShoppingMall *SSM;
};

#endif // SHOPPINGMALL_H