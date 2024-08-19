#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "sellershoppingmall.h"
#include "ordermanager.h"

SellerShoppingMall::SellerShoppingMall()
{
    OM = new OrderManager();
}

bool SellerShoppingMall::managerLogin()
{
    string inputPassword;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                Manager Login                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Input Password ";
    setStdinEcho(false);
    cin >> inputPassword;
    setStdinEcho(true);
    if(inputPassword==managerPassword){
        cout << endl << "Login Successfully!" << endl;
        return true;
    } else {
        return false;
    }
}

bool SellerShoppingMall::displayManageMenu()
{
    int ch;                                                         
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Manager Menu                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Product Mangement                       " << endl;
    cout << "                                             " << endl;
    cout << "  2. Customer Management                     " << endl;
    cout << "                                             " << endl;
    cout << "  3. Order Management                        " << endl;
    cout << "                                             " << endl;
    cout << "  4. Logout                                  " << endl;
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
        // TODO for 노희진
        break;
    case 3:
        
        break;
    case 4:
        return false;
    }
    return true;
}

void SellerShoppingMall::setStdinEcho(bool enable)
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;
    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

bool SellerShoppingMall::menuManageOrder()
{
    int ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Choose Menu                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. View Order                              " << endl;
    cout << "                                             " << endl;
    cout << "  2. Modify Order                            " << endl;
    cout << "                                             " << endl;
    cout << "  3. Show Order In Transit                   " << endl;
    cout << "                                             " << endl;   
    cout << "  4. Show Order Delivered                    " << endl;
    cout << "                                             " << endl;
    cout << "  5. Return Manager Menu                     " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << " What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case 1: default:
        OM->displayOrder();
        break;
    case 2:
        OM->displayOrder("OrderStatus", "Processing");
        break;
    case 3:
        OM->displayOrder("OrderStatus", "InTransit");
        break;
    case 4:
        OM->displayOrder("OrderStatus", "Derivered");
        break;
    case 5:
        return false;
    }

    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();
    
    return true;  
}