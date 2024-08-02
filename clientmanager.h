#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include <map>
#include <vector>
#include "client.h"

using namespace std;

class ClientManager {
  public:
      ClientManager();
      ~ClientManager();

      void inputClient( );
      void addClient(Client*);
      void deleteClient(int);
      void modifyClient(int);
      Client* search(int);
      int makeId();
      void displayInfo();
      vector<string> parseCSV(istream&, char);

      bool displayMenu();

  private:
      map<int, Client*> clientList;
};

#endif    // __CLIENT_MANAGER_H__
