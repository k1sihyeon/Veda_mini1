#include <ctime> 
#include <string>

#include "order.h"
#include "customer.h"
#include "product.h"

using namespace std;

Order::Order()
{
}

Order::Order(int orderId, string orderStatus, string buyerId, int productId, string vendor, int quantity, int totalValue,
                string shipFrom, string shipTo, string createdDate, string requestedShipDate, string requestedDeiliveryDate)
            : m_orderId(orderId), m_orderStatus(orderStatus), m_buyerId(buyerId), m_productId(productId), m_vendor(vendor),
                m_quantity(quantity), m_totalPrice(totalValue), m_shipFrom(shipFrom), m_shipTo(shipTo),
                m_createdDate(createdDate), m_requestedShipDate(requestedShipDate), m_requestedDeliveryDate(requestedDeiliveryDate)
{
} // csv 파일을 파싱할 때 사용하는 생성자

Order::~Order()
{
}

void Order::setOrderId(int orderId)
{
    this->m_orderId = orderId;
}

int Order::getOrderId() const
{
    return m_orderId;
}

void Order::setOrderStatus(string& orderStatus)
{
    this->m_orderStatus = orderStatus;
}

string Order::getOrderStatus() const
{
    return this->m_orderStatus;
}

void Order::setBuyerId(const Customer buyer)
{
    this->m_buyerId = buyer.getUserId();
}

string Order::getBuyerId() const
{
    return this->m_buyerId;
}

void Order::setProductId(const Product product)
{
    this->m_productId = product.getId();
}

int Order::getProductId() const
{
    return this->m_productId;
}

void Order::setVendor(const Product product)
{
    this->m_vendor = product.getCompany();
}

string Order::getVendor() const
{
    return this->m_vendor;
}

void Order::setQuantity(int& quantity)
{
    this->m_quantity = quantity;
}

int Order::getQuantity() const
{
    return this->m_quantity;
}

void Order::setTotalPrice(const Product product, int& quantity)
{
    this->m_totalPrice = product.getPrice() * quantity;
}

int Order::getTotalPrice() const
{
    return this->m_totalPrice;
}

void Order::setShipFrom(string& shipFrom)
{
    this->m_shipFrom = shipFrom;
}

string Order::getShipFrom() const
{
    return this->m_shipFrom;
}

void Order::setShipTo(string& shipTo)
{
    this->m_shipTo = shipTo;
}

string Order::getShipTo() const
{
    return this->m_shipTo;
}

void Order::setCreatedDate()
{
    this->m_createdDate = getCurrentTime();
}

string Order::getCreatedDate() const
{
    return this->m_createdDate;
}

void Order::setRequestedShipDate(string& requestedShipDate)
{
    this->m_requestedShipDate = requestedShipDate;
}

string Order::getRequestedShipDate() const
{
    return this->m_requestedShipDate;
}

void Order::setRequestedDeliveryDate(string& requestedDeliveryDate)
{
    this->m_requestedDeliveryDate = requestedDeliveryDate;
}

string Order::getRequestedDeliveryDate() const
{
    return this->m_requestedDeliveryDate;
}

string Order::getCurrentTime() {
    time_t t = time(0);  // 현재 시간을 가져옴
    tm* now = localtime(&t);  // 현재 시간을 tm 구조체로 변환

    string year = to_string(now->tm_year + 1900);  // tm_year는 1900년부터 시작하므로, 1900을 더해야 함
    string month = to_string(now->tm_mon + 1);  // tm_mon은 0부터 시작하므로, 1을 더해야 함
    string day = to_string(now->tm_mday);
    
    string currentTime = year + "-" + month + "-" + day;
    return currentTime;
}
