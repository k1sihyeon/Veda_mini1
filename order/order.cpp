#include "order.h"

Order::Order() {}
Order::~Order(){}
int Order::getOrderId(){
    return orderId;
} // can't set orderId
void Order::setOrderStatus(string& orderStatus){
    this->orderStatus = orderStatus;
}
string Order::getOrderStatus(){
    return this->orderStatus;
}
void Order::setBuyerId(int& buyerId){
    this->buyerId = buyerId;
}
int Order::getBuyerId(){
    return this->buyerId;
}
void Order::setProductId(int& productId){
    this->productId = productId;
}
int Order::getProductId(){
    return this->productId;
}
void Order::setVendor(string& vendor){
    this->vendor = vendor;
}
string Order::getVendor(){
    return this->vendor;
}
void Order::setQuantity(int& quantity){
    this->quantity = quantity;
}
int Order::getQuantity(){
    return this->quantity;
}
void Order::setTotalValue(double& totalValue){
    this->totalValue = totalValue;
}
double Order::getTotalValue(){
    return this->totalValue;
}
void Order::setValueCurrency(string& valueCurrency){
    this->valueCurrency = valueCurrency;
}
string Order::getValueCurrency(){
    return this->valueCurrency;
}
void Order::setShipFrom(string& shipFrom){
    this->shipFrom = shipFrom;
}
string Order::getShipFrom(){
    return this->shipFrom;
}
void Order::setShipTo(string& shipTo){
    this->shipTo = shipTo;
}
string Order::getShipTO(){
    return this->shipTo;
}
void Order::setCreatedDate(Date& createdDate){
    this->createdDate = createdDate;
}
Date Order::getCreatedDate(){
    return this->createdDate;
}
void Order::setRequestedShipDate(Date& requestedShipDate){
    this->requestedShipDate = requestedShipDate;
}
Date Order::getRequestedShipDate(){
    return this->requestedShipDate;
}
void Order::setRequestedDeliveryDate(Date& requestedDeliveryDate){
    this->requestedDeliveryDate = requestedDeliveryDate;
}
Date Order::getRequestedDeliveryDate(){
    return this->requestedDeliveryDate;
}
