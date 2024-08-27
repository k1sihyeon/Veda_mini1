#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <unordered_map>
#include <vector>

#include "order.h"

using namespace std;

class Customer;
class Product;

class OrderManager
{
public:
    OrderManager();
    ~OrderManager();

    int makeOrderId();
    void displayOrder(string filter1 = "", string filterValue1 = "", string filter2 = "", string filterValue2 = "");
    void displayOrder(string filter1 = "", string filterValue1 = "", string filter2 = "", int filterValue2 = -1);
    
    void inputOrder(string status, const Customer&, const Product&, int quantity, string reqShipDate, string reqDeriveryDate);
    // void deleteOrder(string filter1 = "", string filterValue);
    void deleteOrder(int key);
    // void modifyOrder(string filter1 = "", string filterValue);
    void modifyOrder(int key);
    // void search(string filter = "", string filterValue = "");
    Order* search(int key);

    vector<string> parseCSV(istream& , char);

    static OrderManager* getInstance()
    {
        if (instance == nullptr)
            instance = new OrderManager();
        return instance;
    }

private:
    inline static OrderManager* instance;
    unordered_map<int, Order*> orderList;
};

#endif // ORDERMANAGER_H