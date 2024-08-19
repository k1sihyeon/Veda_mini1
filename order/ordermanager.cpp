#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "order.h"
#include "client.h"
#include "product.h"
#include "ordermanager.h"

OrderManager::OrderManager()
{
    ifstream file;
    file.open("orderlist.txt");
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = atoi(row[0].c_str());
                int buyerId = atoi(row[2].c_str());
                int productId = atoi(row[3].c_str());
                int quantity = atoi(row[5].c_str());
                int totalPrice = atoi(row[6].c_str());
                Order* tmp = new Order(id, row[1], buyerId, productId, row[4], quantity, totalPrice,
                                         row[7], row[8], row[9], row[10], row[11]);
                orderList.insert( { id, tmp } );
            }
        }
    }
    file.close( );
}

OrderManager::~OrderManager()
{
    ofstream file;
    file.open("orderlist.txt");
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
    file.close( );
}

int OrderManager::makeOrderId( )
{
    if(orderList.size( ) == 0) {
        return 0;
    } else {
        auto elem = orderList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

void OrderManager::inputOrder(string status, const Client& buyer, const Product& product, int quantity, string reqShipDate, string reqDeriveryDate)
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
    tmp->setCreatedDate();
    tmp->setRequestedShipDate(reqShipDate);
    tmp->setRequestedDeliveryDate(reqDeriveryDate);
    orderList.insert({id, tmp});
    cout << endl << "Input Order Successfully" << endl;
}

void OrderManager::deleteOrder(int key)
{
    orderList.erase(key);
}

void OrderManager::modifyOrder(int key)
{
    Order *tmp = search(key);
    int statusNum;
    string orderStatus;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               Select Status                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Processing                              " << endl;
    cout << "  2. In Transit                              " << endl;
    cout << "  3. Delivered                               " << endl;
    cout << "  4. <Back to Previous Window>               " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " Press number key : ";
    cin >> statusNum;
    switch (statusNum)
    {
    case 1:
        orderStatus = "Processing";
        break;
    case 2:
        orderStatus = "In Transit";
        break;
    case 3:
        orderStatus = "Delivered";
        break;
    case 4:
        return;
    default:
        cout << "Wrong Number! Press number Again" << endl;
        break;
    }
    tmp->setOrderStatus(orderStatus);
    orderList[key] = tmp;
}

Order* OrderManager::search(int id)
{
    return orderList[id];
}

void OrderManager::displayOrder()
{
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Order List                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;
    for (const auto& v : orderList) {
        Order* tmp = v.second;

        cout << setw(5) << setfill('0') << right << tmp->getOrderId() << " | ";
        cout << setw(10) << setfill(' ') << tmp->getOrderStatus() << " | ";
        cout << tmp->getCreatedDate() << endl;

        cout << "Buyer : " << setw(5) << setfill('0') << tmp->getBuyerId() << "      | ";
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

void OrderManager::displayOrder(string filter, string filterValue)
{
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Order List                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;
    for (const auto& v : orderList) {
        Order* tmp = v.second;

        if ((filter == "OrderStatus" && tmp->getOrderStatus() != filterValue) ||
            (filter == "CreatedDate" && tmp->getCreatedDate() != filterValue) ||
            (filter == "ShipFrom" && tmp->getShipFrom() != filterValue) ||
            (filter == "ShipTo" && tmp->getShipTo() != filterValue) ||
            (filter == "RequestDeliveryDate" && tmp->getRequestedDeliveryDate() != filterValue)){
            continue;
        }

        cout << setw(5) << setfill('0') << right << tmp->getOrderId() << " | ";
        cout << setw(10) << setfill(' ') << tmp->getOrderStatus() << " | ";
        cout << tmp->getCreatedDate() << endl;

        cout << "Buyer : " << setw(5) << setfill('0') << tmp->getBuyerId() << "      | ";
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

void OrderManager::displayOrder(string filter, int filterValue)
{
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Order List                  " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;
    for (const auto& v : orderList) {
        Order* tmp = v.second;

        if ((filter == "BuyerId" && tmp->getBuyerId() != filterValue) ||
            (filter == "ProductId" && tmp->getProductId() != filterValue)){
            continue;
        }

        cout << setw(5) << setfill('0') << right << tmp->getOrderId() << " | ";
        cout << setw(10) << setfill(' ') << tmp->getOrderStatus() << " | ";
        cout << tmp->getCreatedDate() << endl;

        cout << "Buyer : " << setw(5) << setfill('0') << tmp->getBuyerId() << "      | ";
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
