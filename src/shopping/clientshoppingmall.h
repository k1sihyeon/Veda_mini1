#ifndef CLIENTSHOPPINGMALL_H
#define CLIENTSHOPPINGMALL_H

class OrderManager;

class ClientShoppingMall
{
public:
    ClientShoppingMall();
    // ~ClientShoppingMall();

    bool displayMenu();
    bool menuOrderProduct();
    bool menuViewOrder();
private:
    OrderManager *OM;
    int curCustomerID;
};

#endif // CLIENTSHOPPINGMALL_H