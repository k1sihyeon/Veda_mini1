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
#include "checkdate.h"
#include "customerManager.h"
#include "productManager.h"


SellerShoppingMall::SellerShoppingMall()
{
    OM = new OrderManager();
    PM = ProductManager::getInstance();
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

    // 입력 버퍼 정리
    cin.clear();                  // cin 상태 플래그 초기화
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 정리

    if(inputPassword == managerPassword){
        cout << endl << endl << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "            Login Successfully!!             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    } else {
        getchar(); // 입력을 기다림 (이전의 getchar())
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
        while (menuProductManagement()) {}
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
    orderCmdStatus = 0;
    char ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Order Management               " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. View & Search Order                     " << endl;
    cout << "                                             " << endl;
    cout << "  2. Modify Order                            " << endl;
    cout << "                                             " << endl;
    cout << "  3. Delete Order                            " << endl;
    cout << "                                             " << endl;   
    cout << "  4. Return Manager Menu                     " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << " What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case '1':
        orderCmdStatus = 1;
        while(subMenuDisplayFilters()){}
        break;
    case '2':
        orderCmdStatus = 2;
        while(subMenuDisplayFilters()){}
        break;
    case '3':
        orderCmdStatus = 3;
        while(subMenuDisplayFilters()){}
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

bool SellerShoppingMall::subMenuDisplayFilters()
{
    char ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "             Choose Filter Type              " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Order Status                            " << endl;
    cout << "                                             " << endl;
    cout << "  2. Created Date                            " << endl;
    cout << "                                             " << endl;
    cout << "  3. Ship From  <   >                        " << endl;
    cout << "                                             " << endl;   
    cout << "  4. Ship To <   >                           " << endl;
    cout << "                                             " << endl;
    cout << "  5. Display ALL                             " << endl;
    cout << "                                             " << endl;
    cout << "  6. Return Customer Menu                    " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << " What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case '1':
        while(subMenuOrderStatusFilter()){}
        break;
    case '2':
        while(subMenuCreateDateFilter()){}
        break;
    case '3':
        while(subMenuShipFromFilter()){}
        break;
    case '4':
        while(subMenuShipToFilter()){}
        break;
    case '5':
        OM->displayOrder("","","","");
        cout << " Press ENTER to return View Order Section" << endl;
        cin.ignore();
        getchar();
        break;
    case '6':
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

bool SellerShoppingMall::subMenuOrderStatusFilter()
{
    char ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "             Choose Order Status             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Processing                              " << endl;
    cout << "                                             " << endl;
    cout << "  2. In Transit                              " << endl;
    cout << "                                             " << endl;
    cout << "  3. Delivered                               " << endl;
    cout << "                                             " << endl;
    cout << "  4. Return Previous Menu                    " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << " What do you wanna do? ";
    cin >> ch;

    switch(ch) {
    case '1':
        OM->displayOrder("OrderStatus", "Processing", "", "");
        if(orderCmdStatus==2)
            while(subMenuModifyOrder("OrderStatus", "Processing")){}
        else if(orderCmdStatus==3)
            while(subMenuDeleteOrder("OrderStatus", "Processing")){}
        break;
    case '2':
        OM->displayOrder("OrderStatus", "InTransit", "", "");
        if(orderCmdStatus==2)
            while(subMenuModifyOrder("OrderStatus", "InTransit")){}
        else if(orderCmdStatus==3)
            while(subMenuDeleteOrder("OrderStatus", "InTransit")){}
        break;
    case '3':
        OM->displayOrder("OrderStatus", "Delivered", "", -1);
        if(orderCmdStatus==2)
            while(subMenuModifyOrder("OrderStatus", "Delivered")){}
        else if(orderCmdStatus==3)
            while(subMenuDeleteOrder("OrderStatus", "Delivered")){}
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

    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();
    
    return true; 
}

bool SellerShoppingMall::subMenuCreateDateFilter()
{
    string date;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "         Type Searching Created Date         " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  Type 0 to Return Prev Section              " << endl;
    cout << "                                             " << endl;
    cout << "                                             " << endl;
    cout << "  Type Like Below Format                     " << endl;
    cout << "                                             " << endl;
    cout << "  YYYY-MM-DD                                 " << endl;
    cout << "  ";
    cin >> date;

    if (date == "0") {
        return false;
    } else if (!isValidDateFormat(date)) {
        cin.ignore();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    OM->displayOrder("CreatedDate", date, "", "");
    if(orderCmdStatus==2)
        while(subMenuModifyOrder("CreatedDate", date)){}
    else if(orderCmdStatus==3)
        while(subMenuDeleteOrder("CreatedDate", date)){}
    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();

    return true;
}



bool SellerShoppingMall::subMenuShipFromFilter()
{
    string addr;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "        Type Searching Shipping Addr         " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  Type 0 to Return Prev Section              " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Type Address : ";
    cin >> addr;

    if (addr == "0")
        return false;

    OM->displayOrder("ShipFrom", addr, "", "");
    if(orderCmdStatus==2)
        while(subMenuModifyOrder("ShipFrom", addr)){}
    else if(orderCmdStatus==3)
        while(subMenuDeleteOrder("ShipFrom", addr)){}
    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();

    return true;
}

bool SellerShoppingMall::subMenuShipToFilter()
{
    string addr;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "        Type Searching Delivery Addr         " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  Type 0 to Return Prev Section              " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Type Address : ";
    cin >> addr;

    if (addr == "0")
        return false;

    OM->displayOrder("ShipTo", addr, "", "");
    if(orderCmdStatus==2)
        while(subMenuModifyOrder("ShipTo", addr)){}
    else if(orderCmdStatus==3)
        while(subMenuDeleteOrder("ShipTo", addr)){}
    cout << " Press ENTER to return View Order Section" << endl;
    cin.ignore();
    getchar();

    return true;
}

bool SellerShoppingMall::subMenuModifyOrder(string filter, string filterValue)
{
    char ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "            Choose Modify Option             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Status To In Transit                    " << endl;
    cout << "                                             " << endl;
    cout << "  2. Status To Delivered                     " << endl;
    cout << "                                             " << endl;
    cout << "  3. Return Previous Menu                    " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Type Option Number : ";
    cin >> ch;

    switch(ch) {
    case '1':
        OM->modifyOrder(filter, filterValue, "InTransit");
        break;
    case '2':
        OM->modifyOrder(filter, filterValue, "Delivered");
        break;
    case '3':
        return false;
    default:
        cin.ignore();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        break;
    }

    return false;
}

bool SellerShoppingMall::subMenuDeleteOrder(string filter, string filterValue)
{
    char ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "     Are you Sure to Delete this orders?     " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Yes                                     " << endl;
    cout << "                                             " << endl;
    cout << "  2. No                                      " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  Type Option Number : ";
    cin >> ch;

    switch(ch) {
    case '1':
        OM->deleteOrder(filter, filterValue);
        break;
    case '2':
        return false;
    default:
        cin.ignore();
        cout << endl << endl;
        cout << "                 Wrong Input!!               " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        break;
    }
    return false;
}

bool SellerShoppingMall::menuProductManagement()
{
    int ch;                                                         
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Managemet              " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Search Product                          " << endl;
    cout << "                                             " << endl;
    cout << "  2. Modify Product                          " << endl;
    cout << "                                             " << endl;
    cout << "  3. Delete Product                          " << endl;
    cout << "                                             " << endl;
    cout << "  4. Return to Manager Menu                  " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you wanna do? ";
    cin >> ch;

    switch (ch) {
        case 1:
            while (subMenuSearchProduct()) {}
            break;
        
        case 2:
            while (subMenuModifyProduct()) {}
            break;

        case 3:
            while (subMenuDeleteProduct()) {}
            break;

        case 4:
            return false;

        default:
            return true;
    }

    return true;
}

bool SellerShoppingMall::subMenuSearchProduct() {
    // 일단은 전체 리스트 보여주기..
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "               View All Product              " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    PM->printList();

    cout << "\nPress ENTER to Return" << endl;
    cin.clear();
    cin.ignore();
    getchar();

    return false;
}

bool SellerShoppingMall::subMenuModifyProduct() {
    int pid;

    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                Modify Product               " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "Input Prodcut ID to Modify >> ";
    cin >> pid;

    Product* p = PM->searchProductByID(pid);
    if (p == nullptr) {
        cout << "           ID is NOT Valid!!             " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    printf ("         Modify Product | ID : %d\n", pid);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    PM->printProduct(p);

    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "         Select Attribute to Modify          " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;



    return false;
}

bool SellerShoppingMall::subMenuDeleteProduct() {
    int pid;
    
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                Delete Product               " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "Input Prodcut ID to Delete >> ";
    cin >> pid;

    Product* p = PM->searchProductByID(pid);
    if (p == nullptr) {
        cout << "           ID is NOT Valid!!             " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    printf ("         Delete Product | ID : %d\n", pid);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    PM->printProduct(p);

    cin.clear();
    cin.ignore();
    char in;
    cout << "Are You Sure To DELETE? (Y/N) >> ";
    cin >> in;

    if (in == 'y' || in == 'Y') {
        
        return false;
    }
    else if (in == 'n' || in == 'N') {
        return false;
    }
    else {

    }


    return false;
}