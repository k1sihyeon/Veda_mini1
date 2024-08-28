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
    string managerPassword = "veda";
    void setStdinEcho(bool);

    bool menuManagementOrder();
    bool subMenuDisplayFilters();
    bool subMenuOrderStatusFilter();
    bool subMenuCreateDateFilter();
    bool subMenuShipFromFilter();
    bool subMenuShipToFilter();
};

#endif // SELLERSHOPPINGMALL_H