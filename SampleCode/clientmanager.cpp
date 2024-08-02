#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "client.h"
#include "clientmanager.h"

ClientManager::ClientManager()
{
   ifstream file;
   file.open("clientlist.txt");
   if(!file.fail()) {
       while(!file.eof()) {
           vector<string> row = parseCSV(file, ',');
           if(row.size()) {
               int id = atoi(row[0].c_str());
               Client* c = new Client(id, row[1], row[2], row[3]);
               clientList.insert( { id, c } );
           }
       }
   }
   file.close( );
}

ClientManager::~ClientManager()
{
   ofstream file;
   file.open("clientlist.txt");
   if(!file.fail()) {
      for (const auto& v : clientList) {
          Client* c = v.second;
          file << c->id() << ", " << c->getName() << ", ";
          file << c->getPhoneNumber() << ", ";
          file << c->getAddress() << endl;
      }
   }
   file.close( );
}

void ClientManager::inputClient( )
{
    string name, number, address;
    cout << "name : "; cin >> name;
    cout << "number : "; cin >> number;
    cout << "address : "; cin.ignore(); getline(cin, address, '\n'); //cin >> address;

    int id = makeId( );
    Client* c = new Client(id, name, number, address);
    clientList.insert( { id, c } );
}

Client* ClientManager::search(int id)
{
    return clientList[id];
}

void ClientManager::deleteClient(int key)
{
    clientList.erase(key);
}

void ClientManager::modifyClient(int key)
{
    Client* c = search(key);
    cout << "  ID  |     Name     | Phone Number |       Address" << endl;
    cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << c->getAddress() << endl;

    string name, number, address;
    cout << "name : "; cin >> name;
    cout << "number : "; cin >> number;
    cout << "address : "; cin.ignore(); getline(cin, address, '\n'); //cin >> address;

    c->setName(name);
    c->setPhoneNumber(number);
    c->setAddress(address);
    clientList[key] = c;
}

void ClientManager::displayInfo()
{
    cout << endl << "  ID  |     Name     | Phone Number |       Address" << endl;
    for (const auto& v : clientList) {
         Client* c = v.second;
         cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
         cout << setw(12) << setfill(' ') << c->getName() << " | ";
         cout << setw(12) << c->getPhoneNumber() << " | ";
         cout << c->getAddress() << endl;
    }
}

void ClientManager::addClient(Client* c)
{
    clientList.insert( { c->id(), c } );
}

int ClientManager::makeId( )
{
    if(clientList.size( ) == 0) {
        return 0;
    } else {
        auto elem = clientList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> ClientManager::parseCSV(istream &file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while(!file.eof()) {
        char c = file.get();
        if (c==delimiter || c=='\r' || c=='\n') {
            if(file.peek()=='\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t)+1);
            row.push_back(s);
            ss.str("");
            if (c!=delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}


bool ClientManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Client Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Client List                     " << endl;
    cout << "  2. input Client                            " << endl;
    cout << "  3. Delete Client                           " << endl;
    cout << "  4. Modify Client                           " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch(ch) {
        case 1: default:
            displayInfo();
            cin.ignore();
            getchar();
            break;
        case 2:
            inputClient();
            break;
        case 3:
            displayInfo();
            cout << "   Choose Key : ";
            cin >> key;
            deleteClient(key);
            break;
        case 4:
            displayInfo();
            cout << "   Choose Key : ";
            cin >> key;
            modifyClient(key);
            break;
        case 5:
            return false;
    }
    return true;
}