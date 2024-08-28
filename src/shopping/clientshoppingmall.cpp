#include <iostream>
#include <thread>
#include <chrono>

#include "clientshoppingmall.h"
#include "ordermanager.h"
#include "productManager.h"

using namespace std;

ClientShoppingMall::ClientShoppingMall()
{
    OM = new OrderManager();
    PM = ProductManager::getInstance();
}

bool ClientShoppingMall::displayMenu()
{
    char ch;                                                         
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                Customer Menu                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Searching Product                       " << endl;
    cout << "                                             " << endl;
    cout << "  2. View Order                              " << endl;
    cout << "                                             " << endl;
    cout << "  3. Modify Personal Information             " << endl;
    cout << "                                             " << endl;
    cout << "  4. Logout                                  " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case '1':
        // TODO for 김시현
        while (menuSearchProduct()){}
        break;
    case '2':
        while(menuViewOrder()){}
        break;
    case '3':
        // TODO for 노희진
        break;
    case '4':
        return false;
    default:
        cin.ignore();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        break;
    }
    return true;
}


bool ClientShoppingMall::menuViewOrder()
{
    int ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               Choose Filter                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Show All Order                          " << endl;
    cout << "                                             " << endl;
    cout << "  2. Show Order Processing                   " << endl;
    cout << "                                             " << endl;
    cout << "  3. Show Order In Transit                   " << endl;
    cout << "                                             " << endl;   
    cout << "  4. Show Order Delivered                    " << endl;
    cout << "                                             " << endl;
    cout << "  5. Return Customer Menu                    " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << " What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case 1: default:
        OM->displayOrder("", "", "", "");
        break;
    case 2:
        OM->displayOrder("OrderStatus", "Processing", "", "");
        break;
    case 3:
        OM->displayOrder("OrderStatus", "InTransit", "", "");
        break;
    case 4:
        OM->displayOrder("OrderStatus", "Delivered", "", "");
        break;
    case 5:
        return false;
    }

    cout << " Press ENTER to Return View Order Section" << endl;
    cin.ignore();
    getchar();
    
    return true;  
}

bool ClientShoppingMall::menuSearchProduct()
{
    int ch;                                                         
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               Search  Product               " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. View All Products                       " << endl;
    cout << "                                             " << endl;
    cout << "  2. Search By Category                      " << endl;
    cout << "                                             " << endl;
    cout << "  3. Search By Name                          " << endl;
    cout << "                                             " << endl;
    cout << "  4. Search By ID                            " << endl;
    cout << "                                             " << endl;
    cout << "  5. Return to Customer Menu                 " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you wanna do? ";
    cin >> ch;

    int productID;
    
    switch (ch) {
        case 1: {
            PM->printList();
            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출
            break;
        }

        case 2: {
            while(menuSearchProductByCategory()) {}
            break;
        }

        case 3: {
            string name;
            cout << "검색할 이름 입력 >> ";
            cin >> name;    //getline 으로 바꿔야 할 수도?

            PM->searchProductByName(name);

            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출

            break;
        }

        case 4: {
            int id;
            cout << "검색할 id 입력 >> ";
            cin >> id;

            PM->searchProductByID(id);

            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출

            break;
        }

        case 5: {
            return false;
        }

        default:
            return false;
    }

    return true;
}

bool ClientShoppingMall::menuSearchProductByCategory()
{
    int category, productID;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               Select Category               " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Computer                                " << endl;
    cout << "                                             " << endl;
    cout << "  2. Clothes                                 " << endl;
    cout << "                                             " << endl;
    cout << "  3. Book                                    " << endl;
    cout << "                                             " << endl;
    cout << "  4. reserved                                " << endl;
    cout << "                                             " << endl;
    cout << "  5. Return to Search Product                " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you wanna do? ";
    cin >> category;

    vector<Product*> v;

    switch (category) {
        case 1:
            v = PM->searchProductByCategory("Computer");
            break;
        case 2:
            v = PM->searchProductByCategory("Clothes");
            break;
        case 3:
            v = PM->searchProductByCategory("Book");
            break;
        case 5:
            return false;
        default:
            return false;
    }

    for (const auto& p : v) {
        PM->printProduct(p);
    }

    cout << "주문할 Product ID 입력 >> ";
    cin >> productID;
    // order manager 호출

    return true;
}