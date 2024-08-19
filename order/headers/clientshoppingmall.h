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
};

#endif // CLIENTSHOPPINGMALL_H