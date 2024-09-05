#include "shoppingmall.h"
#include "qna.h"

int main()
{
    ShoppingMall *shoppingmall = new ShoppingMall();
    while(shoppingmall->startShoppingMall()){}
    qnabanner();
    return 0;
}
