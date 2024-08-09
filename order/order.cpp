#include "order.h"
#include "client.h"
#include "product.h"

Order::Order()
{
}

Order::~Order()
{
}

int Order::getOrderId()
{
    return orderId;
} // can't set orderId

void Order::setOrderStatus(string& orderStatus)
{
    this->orderStatus = orderStatus;
}

string Order::getOrderStatus()
{
    return this->orderStatus;
}

void Order::setBuyerId(const Client buyer)
{
    this->buyerId = buyer.getClinetId();
}

int Order::getBuyerId()
{
    return this->buyerId;
}

void Order::setProductId(const Product product)
{
    this->productId = product.getProductId();
}

int Order::getProductId()
{
    return this->productId;
}

void Order::setVendor(const Product product)
{
    this->vendor = product.getProductvendor;
}

string Order::getVendor()
{
    return this->vendor;
}

void Order::setQuantity(int& quantity)
{
    this->quantity = quantity;
}

int Order::getQuantity()
{
    return this->quantity;
}

void Order::setTotalValue(double& totalValue)
{
    this->totalValue = totalValue;
}

double Order::getTotalValue()
{
    return this->totalValue;
}

void Order::setValueCurrency(string& valueCurrency)
{
    this->valueCurrency = valueCurrency;
}

string Order::getValueCurrency()
{
    return this->valueCurrency;
}

void Order::setShipFrom(string& shipFrom)
{
    this->shipFrom = shipFrom;
}

string Order::getShipFrom()
{
    return this->shipFrom;
}

void Order::setShipTo(string& shipTo)
{
    this->shipTo = shipTo;
}

string Order::getShipTO()
{
    return this->shipTo;
}

void Order::setCreatedDate(Date& createdDate)
{
    this->createdDate = createdDate;
}

Date Order::getCreatedDate()
{
    return this->createdDate;
}

void Order::setRequestedShipDate(Date& requestedShipDate)
{
    this->requestedShipDate = requestedShipDate;
}

Date Order::getRequestedShipDate()
{
    return this->requestedShipDate;
}

void Order::setRequestedDeliveryDate(Date& requestedDeliveryDate)
{
    this->requestedDeliveryDate = requestedDeliveryDate;
}

Date Order::getRequestedDeliveryDate()
{
    return this->requestedDeliveryDate;
}
