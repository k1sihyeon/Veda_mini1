#ifndef CLIENTSHOPPINGMALL_H
#define CLIENTSHOPPINGMALL_H

class OrderManager;
class Customer;
class ProductManager;

class ClientShoppingMall
{
public:
    ClientShoppingMall();
    ~ClientShoppingMall();

    bool customerLogin();
    bool displayMenu();
    
    bool menuViewOrder();
    bool menuSearchProduct();
    bool menuSearchAllProduct();
    bool menuSearchProductByCategory();
    bool menuSearchProductByName();
    bool menuSearchProductById();
    bool menuInputOrder();

    void setStdinEcho(bool enable);
    bool startClientShoppingMall();
private:
    OrderManager *OM;
    ProductManager *PM;
    int curCustomerID;
    Customer* curCustomer = nullptr;
};

#endif // CLIENTSHOPPINGMALL_H