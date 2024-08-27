#include <iostream>

#include "clothes.cpp"
#include "computer.cpp"
#include "product.h"
#include "productManager.h"

using namespace std;

// Product 디버그 위한 임시 main file

void ORDER() {
    ProductManager* productMannager = ProductManager::getInstance();

    // 상품 보기 옵션 선택
    // 1. 모든 상품을 누적 주문 수량 내림차순으로
    // 2. 카테고리 별로
    // 3. 이름 검색으로 (동일해야함)
    // 4. id 검색으로

    cout << "1: 모든 상품 조회" << endl;
    cout << "2: 카테고리별 조회" << endl;
    cout << "3: 이름 별 조회" << endl;
    cout << "4. id 검색으로 조회" << endl;

    int input, productID;
    cin >> input;

    switch (input) {
        case 1:{
            productMannager->printList();
            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출
            break;
        }

        case 2:{
            cout << "카테고리 선택" << endl;
            cout << "1: Computer" << endl;
            cout << "2: Clothes" << endl;
            cout << "3: Book" << endl;

            int category;
            cin >> category;

            vector<Product *> v;

            switch (category) {
                case 1:
                    v = productMannager->searchProductByCategory("Computer");
                    break;
                case 2:
                    v = productMannager->searchProductByCategory("Clothes");
                    break;
                case 3:
                    v = productMannager->searchProductByCategory("Book");
                    break;
                default:
                    cout << "input error" << endl;
                    break; //continue?
            }

            for (const auto& p : v) {
                productMannager->printProduct(p);
            }

            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출

            break;
        }

        case 3:{
            string name;
            cout << "검색할 이름 입력 >> ";
            cin >> name;    //getline 으로 바꿔야 할 수도?

            productMannager->searchProductByName(name);

            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출

            break;
        }
        
        case 4:{
            int id;
            cout << "검색할 id 입력 >> ";
            cin >> id;

            productMannager->searchProductByID(id);

            cout << "주문할 Product ID 입력 >> ";
            cin >> productID;
            // order manager 호출

            break;
        }
        
        default:
            cout << "input error" << endl;
            break;
    }
}

int main(void) {
    ProductManager* productMannager = ProductManager::getInstance();

    // Product* shirts = Product::createProduct<Clothes>("T-Shirt1000", 20000, "Nike", 100, "Black");
    // shirts->setTotalPurchase(100);
    // productMannager->addProduct(shirts);

    Product* laptop = Product::createProduct<Computer>("MacBook Pro", 1500000, "Apple", "M1", 16, "None");
    laptop->setTotalPurchase(50);
    productMannager->addProduct(laptop);

    // Product* l2 = Product::createProduct<Computer>("Mac Pro", 2000000, "Apple", "M2", 16, "NVIDIA RTX 4070");
    // ProductManager::getInstance()->addProduct(l2);

    // ProductManager::getInstance()->printProduct(shirts);
    // ProductManager::getInstance()->printProduct(laptop);

    productMannager->printAll();

    // ProductManager::getInstance()->deleteProduct(3);
    // ProductManager::getInstance()->printProduct(ProductManager::getInstance()->searchProduct(4));

    // ProductManager::getInstance()->printAll();
    // ProductManager::getInstance()->printProduct(ProductManager::getInstance()->searchProductByID(1));
    // vector<Product *> tmp = ProductManager::getInstance()->searchProductByName("T-Shirt2");
    // for (auto& p : tmp) {
    //     ProductManager::getInstance()->printProduct(p);
    // }

    // tmp = ProductManager::getInstance()->searchProductByCategory("Clothes");
    // for (auto& p : tmp) {
    //     ProductManager::getInstance()->printProduct(p);
    // }

    productMannager->printList();

    cout << "=====================================" << endl;

    ORDER();

    productMannager->~ProductManager();

    return 0;
}