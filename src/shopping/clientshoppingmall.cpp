#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include <thread>
#include <chrono>

#include "clientshoppingmall.h"
#include "ordermanager.h"
#include "customerManager.h"


using namespace std;

ClientShoppingMall::ClientShoppingMall()
{
    OM = new OrderManager();
}


bool ClientShoppingMall::startClientShoppingMall()
{
    customerManager::getInstance()->getRegisteredUsers();
    
    int ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               W E L C O M E  !              " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Login                                   " << endl;
    cout << "                                             " << endl;
    cout << "  2. Register                                " << endl;
    cout << "                                             " << endl;
    cout << "  3. Quit                                    " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you wanna do? ";
    cin >> ch;

    switch (ch) {
    case 1:
        while (!customerLogin()) {}
        if (curCustomer != nullptr) {
            while (displayMenu()) {}
        }
        break;
    case 2:
        while (customerManager::getInstance()->registerUser());
        break;
    case 3:
        curCustomer = nullptr;
        return true;
    default:
        getchar();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return false;

}


bool ClientShoppingMall::customerLogin()
{
    string inputID;
    string inputPassword;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                Customer Login                " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Input ID : ";

    cin >> inputID;

    cout << "  Input Password : ";
    setStdinEcho(false);

    cin >> inputPassword;
    setStdinEcho(true);

    if (customerManager::getInstance()->Login(inputID, inputPassword)) {
        cout << endl << endl << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "            Login Successfully!!             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;

        curCustomer = customerManager::getInstance()->getCustomer(inputID);
        customerManager::getInstance()->showUserInfo(*curCustomer);
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }
    else {
        getchar();
        cout << endl << endl << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "               Wrong Input!!              " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return false;
    }
}


void ClientShoppingMall::setStdinEcho(bool enable) {
#if defined(_WIN32) || defined(_WIN64)
    // Windows 환경
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enable)
        mode &= ~ENABLE_ECHO_INPUT; // echo를 비활성화
    else
        mode |= ENABLE_ECHO_INPUT;  // echo를 활성화

    SetConsoleMode(hStdin, mode);
#else
    // Linux 환경
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
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

