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
#include "productManager.h"
#include "product.h"


using namespace std;

ClientShoppingMall::ClientShoppingMall()
{
    OM = OrderManager::getInstance();
    PM = ProductManager::getInstance();
}

ClientShoppingMall::~ClientShoppingMall()
{
    delete OM;
    delete PM;
    ProductManager::getInstance()->saveCSVfile();
}

bool ClientShoppingMall::startClientShoppingMall()
{
    customerManager::getInstance()->getRegisteredUsers();
    
    int ch;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "               W E L C O M E  !              " << endl;
    cout << "\033[0m";
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
    cout << "\033[1;33m";
    cout << "                Customer Login                " << endl;
    cout << "\033[0m";
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
        cout << "\033[1;33m";
        cout << "            Login Successfully!!             " << endl;
        cout << "\033[0m";
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
        cout << "\033[1;33m";
        cout << "               Wrong Input!!                 " << endl;
        cout << "\033[0m";
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
    char ch;                                                         
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "                Customer Menu                " << endl;
    cout << "\033[0m";
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
        while (menuSearchProduct()){}
        break;
    case '2':
        while(menuViewOrder()){}
        break;
    case '3':
        customerManager::getInstance()->updateUserInfo(*curCustomer);
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
    cout << "\033[1;33m";
    cout << "               Choose Filter                 " << endl;
    cout << "\033[0m";
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
        OM->displayOrder("", "", "BuyerId", curCustomer->getUserId());
        break;
    case 2:
        OM->displayOrder("OrderStatus", "Processing", "BuyerId", curCustomer->getUserId());
        break;
    case 3:
        OM->displayOrder("OrderStatus", "InTransit", "BuyerId", curCustomer->getUserId());
        break;
    case 4:
        OM->displayOrder("OrderStatus", "Delivered", "BuyerId", curCustomer->getUserId());
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
    cout << "\033[1;33m";
    cout << "               Search  Product               " << endl;
    cout << "\033[0m";
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
    
    switch (ch) {
        case 1: {
            while (menuSearchAllProduct()) {}
            break;
        }

        case 2: {
            while (menuSearchProductByCategory()) {}
            break;
        }

        case 3: {
            while (menuSearchProductByName()) {}
            break;
        }

        case 4: {
            while (menuSearchProductById()) {}
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

bool ClientShoppingMall::menuSearchAllProduct()
{
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "               View All Product              " << endl;
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    PM->printList();
    menuInputOrder();

    return false;
}

bool ClientShoppingMall::menuSearchProductByCategory()
{
    int category;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "               Select Category               " << endl;
    cout << "\033[0m";
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
            cout << "\033[2J\033[1;1H";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "\033[1;33m";
            cout << "             Category : Computer             " << endl;
            cout << "\033[0m";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            break;
        case 2:
            v = PM->searchProductByCategory("Clothes");
            cout << "\033[2J\033[1;1H";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "\033[1;33m";
            cout << "             Category : Clothes             " << endl;
            cout << "\033[0m";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            break;
        case 3:
            v = PM->searchProductByCategory("Book");
            cout << "\033[2J\033[1;1H";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "\033[1;33m";
            cout << "              Category : Book                " << endl;
            cout << "\033[0m";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            break;
        case 5:
            return false;
        default:
            return true;
    }

    if (v.empty()) {
        cout << "              List is EMPTY!!                " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    for (const auto& p : v) {
        PM->printProduct(p);
    }

    menuInputOrder();

    return false;
}

bool ClientShoppingMall::menuSearchProductByName()
{
    vector<Product*> v;
    string name;
    cout << "검색할 이름 입력 >> ";
    cin.clear();
    cin.ignore();  // 입력 버퍼 남은거 지우기
    getline(cin, name);

    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    printf ("                 Name : %s\n", name.c_str());
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    v = PM->searchProductByName(name);

    if (v.empty()) {
        printf(" Can NOT Search Product Named in : %s !! \n", name.c_str());
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    for (const auto& p : v)
        PM->printProduct(p);

    menuInputOrder();

    return false;
}

bool ClientShoppingMall::menuSearchProductById()
{
    int id;
    cout << "검색할 id 입력 >> ";
    cin >> id;

    Product* p = PM->searchProductByID(id);
    if (p == nullptr) {
        cout << "           ID is NOT Valid!!             " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    printf("                 ID : %d\n", id);
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    PM->printProduct(p);

    menuInputOrder();

    return false;
}

bool ClientShoppingMall::menuInputOrder()
{
    int productId;
    cout << "주문할 Product ID 입력 >> ";
    cin >> productId;

    Product* prod =  PM->searchProductByID(productId);
    //ordermanager 호출..
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "\033[1;33m";
    cout << "                 Make Order                  " << endl;
    cout << "\033[0m";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  Type ""CANCEL"" If you Cancel Order        " << endl;
    cout << "                                             " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

    int quantity;
    string tmpQuantity;
    cout << "  Type Product's Quantity : ";
    cin >> tmpQuantity;
    if (tmpQuantity == "CANCEL") {
        cout << "\033[A\033[2K";
        cout << "                                             " << endl;
        cout << "               Order Canceled!!              " << endl;
        cout << "                                             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << " Press ENTER to Prev Section" << endl;
        cin.ignore();
        getchar();
        return false;
    }
    quantity = stoi(tmpQuantity);

    string addr;
    cout << "\033[A\033[2K";
    cout << "  Type Your Address : ";
    cin >> addr;
    if (addr == "CANCEL") {
        cout << "\033[A\033[2K";
        cout << "                                             " << endl;
        cout << "               Order Canceled!!              " << endl;
        cout << "                                             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << " Press ENTER to Prev Section" << endl;
        cin.ignore();
        getchar();
        return false;
    }
    
    string deliverDate;
    cout << "\033[A\033[2K";
    cout << "\033[A\033[2K";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  If you don't care about Delivery Date,     " << endl;
    cout << "  Type NULL                                  " << endl;
    cout << endl;
    cout << "  Type Requesting Delivery Date Like Below   " << endl;
    cout << "\033[1;33m";
    cout << "  YYYY-MM-DD" << endl;
    cout << "\033[0m";
    cout << "  ";
    cin >> deliverDate;
    if (deliverDate == "CANCEL") {
        cout << "\033[A\033[2K";
        cout << "                                             " << endl;
        cout << "               Order Canceled!!              " << endl;
        cout << "                                             " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                                             " << endl;
        cout << " Press ENTER to Prev Section" << endl;
        cin.ignore();
        getchar();
        return false;
    }

    OM->inputOrder("Processing", curCustomer, prod, quantity, "NULL", deliverDate);
    int purchase = quantity * (prod->getPrice());
    curCustomer->updateTotalPurchase(purchase);
    prod->increasePurchase(quantity);
    return false;
}