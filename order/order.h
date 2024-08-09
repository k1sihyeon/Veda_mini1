#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "date.h"
using namespace std;

class Client;
class Product;

class Order :
{
public:
    Order();
    ~Order();

    // setter
    void setOrderStatus(string&);
    void setBuyerId(const Client);
    void setProductId(const Product);
    void setVendor(const Product);
    void setQuantity(int&);
    void setTotalValue(double&);
    void setValueCurrency(string&);
    void setShipFrom(string&);
    void setShipTo(string&);
    void setCreatedDate(Date&);
    void setRequestedShipDate(Date&);
    void setRequestedDeliveryDate(Date&);

    // getter
    int getOrderId(); // can't set orderId
    string getOrderStatus();
    int getBuyerId();
    int getProductId();
    string getVendor();
    int getQuantity();
    double getTotalValue();
    string getValueCurrency();
    string getShipFrom();
    string getShipTO();
    Date getCreatedDate();
    Date getRequestedShipDate();
    Date getRequestedDeliveryDate();

private:
    int orderId;
    string orderStatus;
    int buyerId;
    int productId;
    string vendor;
    int quantity;
    int totalValue;
    string valueCurrency;
    string shipFrom;
    string shipTo;
    Date createdDate;
    Date requestedShipDate;
    Date requestedDeliveryDate;
};

#endif // ORDER_H
