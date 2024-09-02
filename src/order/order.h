#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

class Customer;
class Product;

class Order
{
public:
    // inputOrder()에서 사용하는 생성자
    Order();

     // csv 파일을 파싱할 때 사용할 생성자
    Order(int orderId, string orderStatus, string buyerId, int productId, string vendor, int quantity, int totalPrice,
            string shipFrom, string shipTo, string createdDate, string requestedShipDate, string requestedDeiliveryDate);
    ~Order();

    // setter
    void setOrderId(int);
    void setOrderStatus(string&);
    void setBuyerId(Customer*);
    void setProductId(Product*);
    void setVendor(Product*);
    void setQuantity(int&);
    void setTotalPrice(Product*, int&);
    void setShipFrom(string&);
    void setShipTo(string&);
    void setCreatedDate();
    void setRequestedShipDate(string&);
    void setRequestedDeliveryDate(string&);

    // getter
    int getOrderId() const;
    string getOrderStatus() const;
    string getBuyerId() const;
    int getProductId() const;
    string getVendor() const;
    int getQuantity() const;
    int getTotalPrice() const;
    string getShipFrom() const;
    string getShipTo() const;
    string getCreatedDate() const;
    string getRequestedShipDate() const;
    string getRequestedDeliveryDate() const;

private:
    int m_orderId;                  // 주문번호
    string m_orderStatus;           // 주문상태 - 완료, 배송 중, 처리 중
    string m_buyerId;                  // 구매자 ID
    int m_productId;                // 구매 상품 ID
    string m_vendor;                // 판매자 이름
    int m_quantity;                 // 구매 수량
    int m_totalPrice;               // 최종 가격
    string m_shipFrom;              // 배송 시작 장소
    string m_shipTo;                // 배송 도착 장소
    string m_createdDate;           // 주문 생성 시간
    string m_requestedShipDate;     // 원하는 배송 시작 날짜
    string m_requestedDeliveryDate; // 원하는 배송 도착 날짜

    string getCurrentTime();
};

#endif // ORDER_H
