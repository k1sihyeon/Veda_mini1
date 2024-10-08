#include <iostream>

#include "shoppingmall.h"
#include "clientshoppingmall.h"
#include "sellershoppingmall.h"
#include "litbanner.h"

using namespace std;

ShoppingMall::ShoppingMall()
{
   
}

ShoppingMall::~ShoppingMall()
{
 
}

bool ShoppingMall::startShoppingMall()
{
    freekinAwseomeWelcomeBanner();

    char ch;
    cout << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "                        Choose Your Login Type                         " << endl;
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                                                       " << endl;
    cout << "  1. Buyer                                                             " << endl;
    cout << "                                                                       " << endl;
    cout << "  2. Shopping Mall Manager                                             " << endl; 
    cout << "                                                                       " << endl;
    cout << "  3. Quit Shopping Mall                                                " << endl; 
    cout << "                                                                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                                                       " << endl;
    cout << "  What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case '1':
        CSM = new ClientShoppingMall();
        while (!CSM->startClientShoppingMall()) {}
        delete CSM;
        break;
    case '2':
        SSM = new SellerShoppingMall();
        while(!SSM->managerLogin()){}
        while(SSM->displayManageMenu()){}
        delete SSM;
        break;
    case '3':
        freekinAwseomeGoodByeBanner();
        return false;
    default:
        getchar();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        this_thread::sleep_for(chrono::milliseconds(700));
        break;
    }
    return true;  

}