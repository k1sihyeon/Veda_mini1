#ifndef CLIENTSHOPPINGMALL_H
#define CLIENTSHOPPINGMALL_H

class OrderManager;
class Customer;

class ClientShoppingMall
{
public:
    ClientShoppingMall();
    // ~ClientShoppingMall();

    bool customerLogin();
    bool displayMenu();
    bool menuOrderProduct();
    bool menuViewOrder();
    void setStdinEcho(bool enable);
    bool startClientShoppingMall();
private:
    OrderManager* OM;
    int curCustomerID;
    Customer* curCustomer = nullptr;
};

#endif // CLIENTSHOPPINGMALL_H