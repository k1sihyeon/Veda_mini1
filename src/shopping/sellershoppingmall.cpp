#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include <thread>
#include <chrono>

#include "sellershoppingmall.h"
#include "ordermanager.h"
#include "customerManager.h"

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
    cout << "  Input Password : ";

    setStdinEcho(false);
    cin >> inputPassword;
    setStdinEcho(true);

    if (inputPassword == managerPassword) {
        cout << endl << endl << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "            Login Successfully!!             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }
    else {
        getchar();
        cout << endl << endl << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "               Wrong Password!!              " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
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
    case 1:
        // TODO for 김시현
        break;
    case 2:
        customerManager::getInstance()->showManageSystem();
        break;
    case 3:
        while(menuManagementOrder()){}
        break;
    case 4:
        return false;
    default:
        getchar();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        break;
    }
    return true;
}

// void SellerShoppingMall::setStdinEcho(bool enable)
// {
//     struct termios tty;
//     tcgetattr(STDIN_FILENO, &tty);
//     if (!enable)
//         tty.c_lflag &= ~ECHO;
//     else
//         tty.c_lflag |= ECHO;
//     (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
// }

void SellerShoppingMall::setStdinEcho(bool enable) {
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

bool SellerShoppingMall::menuManagementOrder()
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
    case 1:
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
    default:
        cin.ignore();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        break;
    }

    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();
    
    return true;  
}
