#ifndef CLIENT_H
#define CLIENT_H

class Client
{
public:
    Client();
    Client(int);

    int getClientId() const;
private:
    int clientId;
};

#endif // CLIENT_H
