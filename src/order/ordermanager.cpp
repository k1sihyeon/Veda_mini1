#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include "order.h"
#include "customer.h"
#include "product.h"
#include "ordermanager.h"

using namespace std;

OrderManager::OrderManager()
{
    ifstream file;
    file.open("data/orderlist.csv");
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = atoi(row[0].c_str());
                int productId = atoi(row[3].c_str());
                int quantity = atoi(row[5].c_str());
                int totalPrice = atoi(row[6].c_str());
                Order* tmp = new Order(id, row[1], row[2], productId, row[4], quantity, totalPrice,
                                         row[7], row[8], row[9], row[10], row[11]);
                orderList[id] = tmp;  // unordered_map에 삽입
            }
        }
    }
    file.close();
}

OrderManager::~OrderManager()
{
    ofstream file;
    file.open("data/orderlist.csv", ios::trunc);
    if(!file.fail()) {
        for (const auto& v : orderList) {
            Order* tmp = v.second;
            file << tmp->getOrderId() << ", ";
            file << tmp->getOrderStatus() << ", ";
            file << tmp->getBuyerId() << ", ";
            file << tmp->getProductId() << ", ";
            file << tmp->getVendor() << ", ";
            file << tmp->getQuantity() << ", ";
            file << tmp->getTotalPrice() << ", ";
            file << tmp->getShipFrom() << ", ";
            file << tmp->getShipTo() << ", ";
            file << tmp->getCreatedDate() << ", ";
            file << tmp->getRequestedShipDate() << ", ";
            file << tmp->getRequestedDeliveryDate() << endl;
        }
    }
    file.close();
}

int OrderManager::makeOrderId()
{
    if(orderList.empty()) {
        return 0;
    } else {
        int maxId = 0;
        for (const auto& elem : orderList) {
            if (elem.first > maxId) {
                maxId = elem.first;
            }
        }
        return maxId + 1;
    }
}


void OrderManager::inputOrder(string status, Customer* buyer, Product* product, int quantity, string reqShipDate, string reqDeriveryDate)
{
    Order *tmp = new Order();
    int id = makeOrderId();
    
    tmp->setOrderId(id);
    tmp->setOrderStatus(status);
    tmp->setBuyerId(buyer);
    tmp->setProductId(product);
    tmp->setVendor(product);

    tmp->setQuantity(quantity);
    tmp->setTotalPrice(product, quantity);
    string shipfrom = "Veda Mall";
    tmp->setShipFrom(shipfrom);
    string shipto = buyer->getAddress();
    tmp->setShipTo(shipto);
    tmp->setCreatedDate();
    tmp->setRequestedShipDate(reqShipDate);
    tmp->setRequestedDeliveryDate(reqDeriveryDate);
    orderList[id] = tmp;  // unordered_map에 삽입

    ofstream file;
    file.open("data/orderlist.csv", ios::trunc | ios::out);
    if (!file.fail()) {
        vector<int> keys;
        for (const auto& v : orderList) {
            keys.push_back(v.first); // 모든 키를 벡터에 저장
        }
        sort(keys.begin(), keys.end()); // 키를 정렬

        for (int key : keys) {
            Order* tmp = orderList[key];
            file << tmp->getOrderId() << ",";
            file << tmp->getOrderStatus() << ",";
            file << tmp->getBuyerId() << ",";
            file << tmp->getProductId() << ",";
            file << tmp->getVendor() << ",";
            file << tmp->getQuantity() << ",";
            file << tmp->getTotalPrice() << ",";
            file << tmp->getShipFrom() << ",";
            file << tmp->getShipTo() << ",";
            file << tmp->getCreatedDate() << ",";
            file << tmp->getRequestedShipDate() << ",";
            file << tmp->getRequestedDeliveryDate() << endl;
        }
    }
    file.close();

    cout << endl << "Input Order Successfully" << endl;
}

void OrderManager::deleteOrder(string filter, string filterValue)
{
    bool found = false;
    vector<int> keysToDelete;

    for (const auto& v : orderList) {
        Order* tmp = v.second;
        bool filterPassed = false;
        if (filter == "OrderStatus") {
            filterPassed = (tmp->getOrderStatus() == filterValue);
        } else if (filter == "CreatedDate") {
            filterPassed = (tmp->getCreatedDate() == filterValue);
        } else if (filter == "ShipFrom") {
            filterPassed = (tmp->getShipFrom() == filterValue);
        } else if (filter == "ShipTo") {
            filterPassed = (tmp->getShipTo() == filterValue);
        } else {
            cout << "Invalid filter provided!" << endl;
            return;
        }

        // 조건을 만족하는 경우 주문을 삭제할 키를 저장
        if (filterPassed) {
            keysToDelete.push_back(v.first);
            found = true;
        }
    }

    // 저장된 키를 사용하여 주문 삭제
    for (int key : keysToDelete) {
        delete orderList[key]; // 메모리 할당된 주문 삭제
        orderList.erase(key);  // unordered_map에서 삭제
    }

    // 결과 출력
    if (found) {
        cout << endl;
        cout << "  Orders deleted successfully for matching filter." << endl;
        cout << endl;
    } else {
        cout << endl;
        cout << "  No matching orders found with the specified filter." << endl;
        cout << endl;
    }

        // 주문이 삭제된 후 파일에 다시 저장
    ofstream file;
    file.open("data/orderlist.csv", ios::trunc | ios::out);
    if (!file.fail()) {
        vector<int> keys;
        for (const auto& v : orderList) {
            keys.push_back(v.first); // 모든 키를 벡터에 저장
        }
        sort(keys.begin(), keys.end()); // 키를 정렬

        for (int key : keys) {
            Order* tmp = orderList[key];
            file << tmp->getOrderId() << ",";
            file << tmp->getOrderStatus() << ",";
            file << tmp->getBuyerId() << ",";
            file << tmp->getProductId() << ",";
            file << tmp->getVendor() << ",";
            file << tmp->getQuantity() << ",";
            file << tmp->getTotalPrice() << ",";
            file << tmp->getShipFrom() << ",";
            file << tmp->getShipTo() << ",";
            file << tmp->getCreatedDate() << ",";
            file << tmp->getRequestedShipDate() << ",";
            file << tmp->getRequestedDeliveryDate() << endl;
        }
    }
    file.close();
}


void OrderManager::modifyOrder(string filter, string filterValue, string newOrderStatus)
{
    bool found = false; // 하나 이상의 주문이 수정되었는지 여부 확인

    for (auto& v : orderList) {
        Order* tmp = v.second;

        // 필터에 따른 조건 확인
        bool filterPassed = false;

        if (filter == "OrderStatus") {
            filterPassed = (tmp->getOrderStatus() == filterValue);
        } else if (filter == "CreatedDate") {
            filterPassed = (tmp->getCreatedDate() == filterValue);
        } else if (filter == "ShipFrom") {
            filterPassed = (tmp->getShipFrom() == filterValue);
        } else if (filter == "ShipTo") {
            filterPassed = (tmp->getShipTo() == filterValue);
        } else {
            cout << "Invalid filter provided!" << endl;
            return;
        }

        // 조건을 만족하는 경우 주문 상태 변경
        if (filterPassed) {
            tmp->setOrderStatus(newOrderStatus);
            found = true; // 변경된 주문이 있음을 표시
        }
    }

    // 결과 출력
    if (found) {
        cout << endl;
        cout << "  Order status updated successfully for matching orders." << endl;
        cout << endl;
    } else {
        cout << endl;
        cout << "  No matching orders found with the specified filter." << endl;
        cout << endl;
    }

        // 주문이 삭제된 후 파일에 다시 저장
    ofstream file;
    file.open("data/orderlist.csv", ios::trunc | ios::out);
    if (!file.fail()) {
        vector<int> keys;
        for (const auto& v : orderList) {
            keys.push_back(v.first); // 모든 키를 벡터에 저장
        }
        sort(keys.begin(), keys.end()); // 키를 정렬

        for (int key : keys) {
            Order* tmp = orderList[key];
            file << tmp->getOrderId() << ",";
            file << tmp->getOrderStatus() << ",";
            file << tmp->getBuyerId() << ",";
            file << tmp->getProductId() << ",";
            file << tmp->getVendor() << ",";
            file << tmp->getQuantity() << ",";
            file << tmp->getTotalPrice() << ",";
            file << tmp->getShipFrom() << ",";
            file << tmp->getShipTo() << ",";
            file << tmp->getCreatedDate() << ",";
            file << tmp->getRequestedShipDate() << ",";
            file << tmp->getRequestedDeliveryDate() << endl;
        }
    }
    file.close();
}

Order* OrderManager::search(int id)
{
    return orderList[id];
}

void OrderManager::displayOrder(string filter1, string filterValue1, string filter2, string filterValue2)
{
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Order List                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;

    for (const auto& v : orderList) {
        Order* tmp = v.second;

        bool filter1Passed = 
            (filter1.empty() || 
            (filter1 == "OrderStatus" && tmp->getOrderStatus() == filterValue1) ||
            (filter1 == "CreatedDate" && tmp->getCreatedDate() == filterValue1) ||
            (filter1 == "ShipFrom" && tmp->getShipFrom() == filterValue1) ||
            (filter1 == "ShipTo" && tmp->getShipTo() == filterValue1) ||
            (filter1 == "RequestDeliveryDate" && tmp->getRequestedDeliveryDate() == filterValue1));

        bool filter2Passed = 
            (filter2.empty() || 
            (filter2 == "BuyerId" && tmp->getBuyerId() == filterValue2) ||
            (filter2 == "ProductId" && to_string(tmp->getProductId()) == filterValue2));

        if (!filter1Passed || !filter2Passed) {
            continue;
        }

        cout << setw(5) << setfill('0') << right << tmp->getOrderId() << " | ";
        cout << setw(10) << setfill(' ') << tmp->getOrderStatus() << " | ";
        cout << tmp->getCreatedDate() << endl;
        cout << left;
        cout << "Buyer : " << setw(5) << setfill(' ') << tmp->getBuyerId() << "      | ";
        cout << right;
        cout << tmp->getVendor();
        cout << "'s product : " << setw(5) << setfill('0') << tmp->getProductId() << endl;
        cout << left;
        cout << "Quantity : " << setw(5) << setfill(' ') << tmp->getQuantity() << "   | ";
        cout << right;
        cout << "Value : " << setw(7) << setfill(' ') << tmp->getTotalPrice() << " KRW" << endl;

        cout << "From : " << tmp->getShipFrom() << endl;
        cout << "To : " << tmp->getShipTo() << endl;

        cout << "Prepare : " << tmp->getRequestedShipDate() << endl;
        cout << "Deliver : " << tmp->getRequestedDeliveryDate() << endl << endl;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void OrderManager::displayOrder(string filter1, string filterValue1, string filter2, int filterValue2)
{
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Order List                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;

    for (const auto& v : orderList) {
        Order* tmp = v.second;

        bool filter1Passed = 
            (filter1.empty() || 
            (filter1 == "OrderStatus" && tmp->getOrderStatus() == filterValue1) ||
            (filter1 == "CreatedDate" && tmp->getCreatedDate() == filterValue1) ||
            (filter1 == "ShipFrom" && tmp->getShipFrom() == filterValue1) ||
            (filter1 == "ShipTo" && tmp->getShipTo() == filterValue1) ||
            (filter1 == "RequestDeliveryDate" && tmp->getRequestedDeliveryDate() == filterValue1));

        bool filter2Passed = 
            (filter2.empty() || 
            (filter2 == "BuyerId" && tmp->getBuyerId() == to_string(filterValue2)) ||
            (filter2 == "ProductId" && tmp->getProductId() == filterValue2));

        if (!filter1Passed || !filter2Passed) {
            continue;
        }

        cout << setw(5) << setfill('0') << right << tmp->getOrderId() << " | ";
        cout << setw(10) << setfill(' ') << tmp->getOrderStatus() << " | ";
        cout << tmp->getCreatedDate() << endl;
        cout << left;
        cout << "Buyer : " << setw(5) << setfill(' ') << tmp->getBuyerId() << "      | ";
        cout << right;
        cout << tmp->getVendor();
        cout << "'s product : " << setw(5) << setfill('0') << tmp->getProductId() << endl;
        cout << left;
        cout << "Quantity : " << setw(5) << setfill(' ') << tmp->getQuantity() << "   | ";
        cout << right;
        cout << "Value : " << setw(7) << setfill(' ') << tmp->getTotalPrice() << " KRW" << endl;

        cout << "From : " << tmp->getShipFrom() << endl;
        cout << "To : " << tmp->getShipTo() << endl;

        cout << "Prepare : " << tmp->getRequestedShipDate() << endl;
        cout << "Deliver : " << tmp->getRequestedDeliveryDate() << endl << endl;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

vector<string> OrderManager::parseCSV(istream &file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while(!file.eof()) {
        char c = file.get();
        if (c==delimiter || c=='\r' || c=='\n') {
            if(file.peek()=='\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t)+1);
            row.push_back(s);
            ss.str("");
            if (c!=delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}
