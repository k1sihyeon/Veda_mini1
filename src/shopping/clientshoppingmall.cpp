#include <iostream>

#include "clientshoppingmall.h"
#include "ordermanager.h"

using namespace std;

ClientShoppingMall::ClientShoppingMall()
{
    OM = new OrderManager();
}

bool ClientShoppingMall::displayMenu()
{
    int ch;                                                         
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                Customer Menu                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Searching Product                       " << endl;
    cout << "                                             " << endl;
    cout << "  2. Make Order                              " << endl;    // 1과 merge
    cout << "                                             " << endl;
    cout << "  3. View Order                              " << endl;
    cout << "                                             " << endl;
    cout << "  4. Modify Personal Information             " << endl;
    cout << "                                             " << endl;
    cout << "  5. Logout                                  " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case 1: default:
        // TODO for 김시현
        break;
    case 2:
        menuOrderProduct();
        break;
    case 3:
        while(menuViewOrder()){}
        break;
    case 4:
        // TODO for 노희진
        break;
    case 5:
        return false;
    }
    return true;
}

bool ClientShoppingMall::menuOrderProduct()
{
    int quan;
    string reqship;
    string reqderi;

    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               Order/Payment                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Input Quantity : ";
    cin >> quan;
    cout << endl;
    cout << "  Input Prefer Requested Shipping Date" << endl;
    cout << "  If you want shipping today press ENTER" << endl;
    cout << "  YYYY-MM-DD " << endl << "  ";
    cin >> reqship;
    cout << endl;
    cout << "  Input Prefer Requested Derivery Date" << endl;
    cout << "  If don't care about this press ENTER" << endl;
    cout << "  YYYY-MM-DD " << endl << "  ";
    cin >> reqderi;
    

    // OM->inputOrder();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
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
        OM->displayOrder("OrderStatus", "Processing", "", -1);
        break;
    case 3:
        OM->displayOrder("OrderStatus", "InTransit", "", -1);
        break;
    case 4:
        OM->displayOrder("OrderStatus", "Delivered", "", -1);
        break;
    case 5:
        return false;
    }

    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();
    
    return true;  
}

