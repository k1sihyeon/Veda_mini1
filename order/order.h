#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "date.h"
using namespace std;

class Order : public Date
{
public:
    Order();
    ~Order();
    int getOrderId(); // can't set orderId
    void setOrderStatus(string&);
    string getOrderStatus();
    void setBuyerId(int&);
    int getBuyerId();
    void setProductId(int&);
    int getProductId();
    void setVendor(string&);
    string getVendor();
    void setQuantity(int&);
    int getQuantity();
    void setTotalValue(double&);
    double getTotalValue();
    void setValueCurrency(string&);
    string getValueCurrency();
    void setShipFrom(string&);
    string getShipFrom();
    void setShipTo(string&);
    string getShipTO();
    void setCreatedDate(Date&);
    Date getCreatedDate();
    void setRequestedShipDate(Date&);
    Date getRequestedShipDate();
    void setRequestedDeliveryDate(Date&);
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
