//
// Created by gaspar_q on 6/6/16.
//

#include "Client.hpp"

Client::Client(const std::string &protocol, const sa_family_t domain, const int option) :
        Socket(protocol, domain, option),
        _connected(false),
        _port(0),
        _ip()
{

}

Client::~Client()
{

}

Client::Client(Client const &ref) :
    Socket(ref),
    _connected(false),
    _port(0),
    _ip()
{

}

void Client::Connect(const std::string &ip, const uint16_t port)
{
    Talk(ip, port);
    _ip = ip;
    _port = port;
    _connected = true;
}

bool Client::isConnected(void) const
{
    return _connected;
}
