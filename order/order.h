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
    int orderId;                // 주문번호
    string orderStatus;         // 주문상태 - 완료, 배송 중, 처리 중
    int buyerId;                // 구매자 ID
    int productId;              // 구매 상품 ID
    string vendor;              // 판매자나 상품 브랜드
    int quantity;               // 구매 수량
    int totalValue;             // 최종 가격
    string valueCurrency;       // 가격 단위
    string shipFrom;            // 배송 시작 장소
    string shipTo;              // 배송 도착 장소
    Date createdDate;           // 주문 생성 시간
    Date requestedShipDate;     // 원하는 배송 시작 날짜
    Date requestedDeliveryDate; // 원하는 배송 도착 날짜
};

#endif // ORDER_H
