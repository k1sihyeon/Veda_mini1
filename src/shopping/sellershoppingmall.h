#ifndef SELLERSHOPPINGMALL_H
#define SELLERSHOPPINGMALL_H

#include <iostream>

using namespace std;

class OrderManager;
class ProductManager;

class SellerShoppingMall
{
public:
    SellerShoppingMall();
    ~SellerShoppingMall();

    bool displayManageMenu();
    bool managerLogin();
private:
    OrderManager *OM;
    ProductManager *PM;
    string managerPassword = "veda";
    int orderCmdStatus = 0;
    void setStdinEcho(bool);

    bool menuManagementOrder();
    bool subMenuDisplayFilters();
    bool subMenuOrderStatusFilter();
    bool subMenuCreateDateFilter();
    bool subMenuShipFromFilter();
    bool subMenuShipToFilter();
    bool subMenuModifyOrder(string, string);
    bool subMenuDeleteOrder(string, string);

    bool menuProductManagement();
    bool subMenuSearchProduct();
    bool subMenuModifyProduct();
    bool subMenuDeleteProduct();
    bool subMenuAddProduct();
};

#endif // SELLERSHOPPINGMALL_H