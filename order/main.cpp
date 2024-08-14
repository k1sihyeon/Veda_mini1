#include <iostream>

#include "client.h"
#include "product.h"
#include "ordermanager.h"

using namespace std;

int main()
{
    OrderManager om;
    Client in(12345);
    Product inp(12212, "VEDA", 500);
    om.displayOrder();
    om.inputOrder(in, inp, 10, "2024-08-13", "2024-08-15");
    om.displayOrder();
    om.inputOrder(in, inp, 10, "2024-08-13", "2024-08-15");
    om.displayOrder("BuyerId", 1001);
    return 0;
}
