#include <iostream>
#include "client.h"
#include "clientmanager.h"

int main()
{
    ClientManager cm;
//    ProductManager pm;
//    Shoplist sl;
/*
    for(int i = 0; i < 5; i++) {
        cm.inputClient( );
        cout << endl;
    }
*/
//    cm.inputClient( );
    cm.displayInfo( );
/*
    for(int i = 0; i < 5; i++) 
        cout << cm.search(i)->getName() << endl;
*/
    return 0;
}
