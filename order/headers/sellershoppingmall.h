#ifndef SELLERSHOPPINGMALL_H
#define SELLERSHOPPINGMALL_H

#include <iostream>

using namespace std;

class OrderManager;

class SellerShoppingMall
{
public:
    SellerShoppingMall();
    // ~SellerShoppingMall();

    bool displayManageMenu();
    bool managerLogin();
private:
    OrderManager *OM;
    string managerPassword = "VEDAisGOAT";
    void setStdinEcho(bool);
    bool menuManageOrder();
};

#endif // SELLERSHOPPINGMALL_H