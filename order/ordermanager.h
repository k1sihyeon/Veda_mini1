#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <map>
#include <vector>
#include "order.h"

using namespace std;

class Client;
class Product;

class OrderManager
{
public:
    OrderManager();
    ~OrderManager();

    int makeOrderId();

    void inputOrder(const Client&, const Product&, int quantity, string reqShipDate, string reqDeriveryDate);
    void deleteOrder(int key);
    // void deleteOrder(int key, int key); // 필터로 삭제
    void modifyOrder(int key); // only modify orderStatus
    // void modifyOrder(int key, int key); // 필터로 변경
    Order* search(int key);
    // Order* search(string); // 필터로 서치

    void displayOrder();
    void displayOrder(string, string);
    void displayOrder(string, int);

    bool displayMenu();

    vector<string> parseCSV(istream& , char);
private:
    map<int, Order*> orderList;
};

#endif // ORDERMANAGER_H
