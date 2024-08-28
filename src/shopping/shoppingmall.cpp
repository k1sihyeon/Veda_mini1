#include <iostream>

#include "shoppingmall.h"
#include "clientshoppingmall.h"
#include "sellershoppingmall.h"
#include "litbanner.h"

using namespace std;

ShoppingMall::ShoppingMall()
{
    CSM = new ClientShoppingMall();
    SSM = new SellerShoppingMall();
}

ShoppingMall::~ShoppingMall()
{
    delete CSM;
    delete SSM;
}

bool ShoppingMall::startShoppingMall()
{
    freekinAwseomeWelcomeBanner();

    char ch;
    cout << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                        Choose Your Login Type                         " << endl;
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
        while (!CSM->startClientShoppingMall()) {}
        break;
    case '2':
        while(!SSM->managerLogin()){}
        while(SSM->displayManageMenu()){}
        break;
    case '3':
        freekinAwseomeGoodByeBanner();
        return false;
    default:
        getchar();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        this_thread::sleep_for(chrono::milliseconds(1000));
        break;
    }
    return true;  

}