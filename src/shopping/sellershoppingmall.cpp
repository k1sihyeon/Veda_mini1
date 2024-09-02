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
#include "product.h"
#include "computer.cpp"
#include "clothes.cpp"
#include "book.cpp"

SellerShoppingMall::SellerShoppingMall()
{
    OM = new OrderManager();
    PM = ProductManager::getInstance();
}

SellerShoppingMall::~SellerShoppingMall()
{
    ProductManager::getInstance()->saveCSVfile();
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
    cout << "  3. Add New Product                         " << endl;
    cout << "                                             " << endl;
    cout << "  4. Delete Product                          " << endl;
    cout << "                                             " << endl;
    cout << "  5. Return to Manager Menu                  " << endl;
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
            while (subMenuAddProduct()) {}
            break;

        case 4:
            while (subMenuDeleteProduct()) {}
            break;

        case 5:
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

    int attr;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "         Select Attribute to Modify          " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  1. Name                                    " << endl;
    cout << "                                             " << endl;
    cout << "  2. Price                                   " << endl;
    cout << "                                             " << endl;
    cout << "  3. Maker                                   " << endl;
    cout << "                                             " << endl;
    
    // getMoreDetails를 순수 가상 함수로 바꾸고 싶은데 dependency가 좀 있음;;
    if (Computer* cp = dynamic_cast<Computer*>(p))
        cout << cp->getMoreDetails(3);
    else if (Clothes* ct = dynamic_cast<Clothes*>(p))
        cout << ct->getMoreDetails(3);
    else if (Book* bk = dynamic_cast<Book*>(p))
        cout << bk->getMoreDetails(3);
    else
        cout << "err" << endl;

    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                                             " << endl;
    cout << "  What do you want to Modify? ";
    cin >> attr;

    switch (attr) {
        case 1: {
            string name;
            
            cout << "\033[A\033[2K";
            cout << "Input Name >> ";
            cin.clear();
            cin.ignore();
            getline(cin, name);

            cout << "\033[A\033[2K";
            cout << "Name: " << p->getName() << " will be changed into " << name << endl;

            cin.clear();
            cin.ignore();
            char in;
            cout << "Are You Sure To Modify? (Y/N) >> ";
            cin >> in;

            if (in == 'y' || in == 'Y') { 
                p->setName(name);
                return false;
            }
            else if (in == 'n' || in == 'N') { 
                return false;
            }
            else {
                cout << "          Input is NOT Valid!!           " << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                return true;
            }
            
            break;
        }
        
        case 2: {
            int price;
            
            cout << "\033[A\033[2K";
            cout << "Input Price >> ";
            cin >> price;

            cout << "\033[A\033[2K";
            cout << "Price: " << p->getPrice() << " will be changed into " << price << endl;

            cin.clear();
            cin.ignore();
            char in;
            cout << "Are You Sure To Modify? (Y/N) >> ";
            cin >> in;

            if (in == 'y' || in == 'Y') { 
                p->setPrice(price);
                return false;
            }
            else if (in == 'n' || in == 'N') { 
                return false;
            }
            else {
                cout << "          Input is NOT Valid!!           " << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                return true;
            }

            break;
        }

        case 3: {
            string maker;

            cout << "\033[A\033[2K";
            cout << "Input Maker >> ";
            cin.clear();
            cin.ignore();
            getline(cin, maker);

            cout << "\033[A\033[2K";
            cout << "Maker: " << p->getCompany() << " will be changed into " << maker << endl;

            cin.clear();
            cin.ignore();
            char in;
            cout << "Are You Sure To Modify? (Y/N) >> ";
            cin >> in;

            if (in == 'y' || in == 'Y') { 
                p->setCompany(maker);
                return false;
            }
            else if (in == 'n' || in == 'N') { 
                return false;
            }
            else {
                cout << "          Input is NOT Valid!!           " << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                return true;
            }

            break;
        }

        default: {
            if (Computer* cp = dynamic_cast<Computer*>(p)) {
                switch (attr) {
                    case 4: {
                        string cpu;

                        cout << "\033[A\033[2K";
                        cout << "Input CPU >> ";
                        cin.clear();
                        cin.ignore();
                        getline(cin, cpu);

                        cout << "\033[A\033[2K";
                        cout << "CPU: " << cp->getCpu() << " will be changed into " << cpu << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            cp->setCompany(cpu);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    case 5: {
                        int ram;

                        cout << "\033[A\033[2K";
                        cout << "Input RAM >> ";
                        cin >> ram;

                        cout << "\033[A\033[2K";
                        cout << "RAM: " << cp->getRam() << " will be changed into " << ram << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            cp->setRam(ram);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    break;

                    case 6: {
                        string gpu;

                        cout << "\033[A\033[2K";
                        cout << "Input GPU >> ";
                        cin.clear();
                        cin.ignore();
                        getline(cin, gpu);

                        cout << "\033[A\033[2K";
                        cout << "GPU: " << cp->getGpu() << " will be changed into " << gpu << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            cp->setGpu(gpu);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    default:
                        cout << "          Input is NOT Valid!!           " << endl;
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        return true;
                }
            }
            else if (Clothes* ct = dynamic_cast<Clothes*>(p)) {
                switch (attr) {
                    case 4: {
                        int size;

                        cout << "\033[A\033[2K";
                        cout << "Input SIZE >> ";
                        cin >> size;

                        cout << "\033[A\033[2K";
                        cout << "SIZE: " << ct->getSize() << " will be changed into " << size << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            ct->setSize(size);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    case 5: {
                        string color;

                        cout << "\033[A\033[2K";
                        cout << "Input COLOR >> ";
                        cin.clear();
                        cin.ignore();
                        getline(cin, color);

                        cout << "\033[A\033[2K";
                        cout << "COLOR: " << ct->getColor() << " will be changed into " << color << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            ct->setColor(color);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    default:
                        cout << "          Input is NOT Valid!!           " << endl;
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        return true;
                }
            }
            else if (Book* bk = dynamic_cast<Book*>(p)) {
                switch (attr) {
                    case 4: {
                        string auther;

                        cout << "\033[A\033[2K";
                        cout << "Input AUTHOR >> ";
                        cin.clear();
                        cin.ignore();
                        getline(cin, auther);

                        cout << "\033[A\033[2K";
                        cout << "AUTHOR: " << bk->getAuther() << " will be changed into " << auther << endl;

                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            bk->setAuther(auther);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    case 5: {
                        int page;

                        cout << "\033[A\033[2K";
                        cout << "Input PAGES >> ";
                        cin >> page;

                        cout << "\033[A\033[2K";
                        cout << "PAGES: " << bk->getPages() << " will be changed into " << page << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            bk->setPages(page);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }

                    case 6: {
                        int year;

                        cout << "\033[A\033[2K";
                        cout << "Input YEAR >> ";
                        cin >> year;

                        cout << "\033[A\033[2K";
                        cout << "YEAR: " << bk->getYear() << " will be changed into " << year << endl;

                        cin.clear();
                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            bk->setYear(year);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }


                    case 7: {
                        string isbn;

                        cout << "\033[A\033[2K";
                        cout << "Input ISBN >> ";
                        cin.clear();
                        cin.ignore();
                        getline(cin, isbn);

                        cout << "\033[A\033[2K";
                        cout << "ISBN: " << bk->getIsbn() << " will be changed into " << isbn << endl;

                        cin.ignore();
                        char in;
                        cout << "Are You Sure To Modify? (Y/N) >> ";
                        cin >> in;

                        if (in == 'y' || in == 'Y') {
                            bk->setIsbn(isbn);
                            return false;
                        }
                        else if (in == 'n' || in == 'N') {
                            return false;
                        }
                        else {
                            cout << "          Input is NOT Valid!!           " << endl;
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            return true;
                        }

                        break;
                    }


                    default:
                        cout << "          Input is NOT Valid!!           " << endl;
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        return true;
                }
            }

            break;
        }
    }

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
        PM->deleteProduct(pid);
        return false;
    }
    else if (in == 'n' || in == 'N') {
        return false;
    }
    else {
        cout << "          Input is NOT Valid!!           " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

    return false;
}

bool SellerShoppingMall::subMenuAddProduct() {
    int category;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "    Select Category of Product want to add   " << endl;
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

    switch (category) {
        case 1:
            cout << "\033[2J\033[1;1H";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "     Add New Product (Category : Computer)   " << endl;
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            break;
        case 2:
            cout << "\033[2J\033[1;1H";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "     Add New Product (Category : Clothes)    " << endl;
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            break;
        case 3:
            cout << "\033[2J\033[1;1H";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "       Add New Product (Category : Book)     " << endl;
            cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
            break;
        case 5:
            return false;
        default:
            return true;
    }

    string name, maker;
    int price;

    cout << "Input Name >> ";
    cin.clear();
    cin.ignore();
    getline(cin, name);

    cout << "\033[A\033[2K";
    cout << "Input Maker >> ";
    cin.clear();
    cin.ignore();
    getline(cin, maker);

    cout << "\033[A\033[2K";
    cout << "Input Price >> ";
    cin >> price;

    Product* p;

    switch (category) {
        case 1: {
            string cpu, gpu;
            int ram;
            cout << "\033[A\033[2K";
            cout << "Input CPU >> ";
            cin.clear();
            cin.ignore();
            getline(cin, cpu);

            cout << "\033[A\033[2K";
            cout << "Input GPU >> ";
            cin.clear();
            cin.ignore();
            getline(cin, gpu);

            cout << "\033[A\033[2K";
            cout << "Input RAM >> ";
            cin >> ram;

            p = Product::createProduct<Computer>(name, price, maker, cpu, ram, gpu);

            break;
        }

        case 2: {
            int size;
            string color;
            
            cout << "\033[A\033[2K";
            cout << "Input SIZE >> ";
            cin >> size;

            cout << "\033[A\033[2K";
            cout << "Input COLOR >> ";
            cin.clear();
            cin.ignore();
            getline(cin, color);

            p = Product::createProduct<Clothes>(name, price, maker, size, color);

            break;
        }

        case 3: {
            string auther, isbn;
            int pages, year;

            cout << "\033[A\033[2K";
            cout << "Input AUTHER >> ";
            cin.clear();
            cin.ignore();
            getline(cin, auther);

            cout << "\033[A\033[2K";
            cout << "Input ISBN >> ";
            cin.clear();
            cin.ignore();
            getline(cin, isbn);

            cout << "\033[A\033[2K";
            cout << "Input PAGES >> ";
            cin >> pages;

            cout << "\033[A\033[2K";
            cout << "Input YEAR of published >> ";
            cin >> year;

            p = Product::createProduct<Book>(name, price, maker, auther, pages, year, isbn);

            break;
        }

        case 5:
            return false;
        default:
            return true;
    }

    cout << "\033[A\033[2K";
    PM->printProduct(p);

    cin.ignore();
    char in;
    cout << "Are You Sure To ADD? (Y/N) >> ";
    cin >> in;

    if (in == 'y' || in == 'Y') {
        PM->addProduct(p);
        return false;
    }
    else if (in == 'n' || in == 'N') {
        return false;
    }
    else {
        cout << "          Input is NOT Valid!!           " << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    }

}