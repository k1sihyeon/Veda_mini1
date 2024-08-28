#ifndef CLIENTSHOPPINGMALL_H
#define CLIENTSHOPPINGMALL_H

class OrderManager;
class ProductManager;

class ClientShoppingMall
{
public:
    ClientShoppingMall();
    // ~ClientShoppingMall();

    bool displayMenu();
    
    bool menuViewOrder();
    bool menuSearchProduct();
    bool menuSearchProductByCategory();

private:
    OrderManager *OM;
    ProductManager *PM;
    int curCustomerID;
};

#endif // CLIENTSHOPPINGMALL_H