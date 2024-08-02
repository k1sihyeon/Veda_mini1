#include "client.h"

#include <iostream>

using namespace std;

Client::Client(int id, string name, string phoneNumber, string address)
          : m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address)
{
}

string Client::getName() const
{
    return m_name;
}

void Client::setName(string& name)
{
    m_name = name;
}

string Client::getPhoneNumber() const
{
    return m_phoneNumber;
}

void Client::setPhoneNumber(string& phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

string Client::getAddress() const
{
    return m_address;
}

void Client::setAddress(string& address)
{
    m_address = address;
}

int Client::id() const
{
    return m_id;
}

// Define copy assignment operator.
bool Client::operator==(const Client &other) const {
    return (this->m_name == other.m_name);
}
