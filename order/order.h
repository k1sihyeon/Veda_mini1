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
    int getOrderId() const; // can't set orderId
    string getOrderStatus() const;
    int getBuyerId() const;
    int getProductId() const;
    string getVendor() const;
    int getQuantity() const;
    double getTotalValue() const;
    string getValueCurrency() const;
    string getShipFrom() const;
    string getShipTO() const;
    Date getCreatedDate() const;
    Date getRequestedShipDate() const;
    Date getRequestedDeliveryDate() const;

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
