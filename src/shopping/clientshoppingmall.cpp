#include <iostream>
#include <thread>
#include <chrono>

#include "clientshoppingmall.h"
#include "ordermanager.h"

using namespace std;

ClientShoppingMall::ClientShoppingMall()
{
    OM = new OrderManager();
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

