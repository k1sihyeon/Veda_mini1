#include "client.h"

Client::Client() {}

Client::Client(int id){
    this->clientId = id;
}

int Client::getClientId()const{
    return this->clientId;
}
