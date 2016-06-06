//
// Created by gaspar_q on 6/6/16.
//

#ifndef PSU_2015_ZAPPY_CLIENT_HPP
#define PSU_2015_ZAPPY_CLIENT_HPP

# include "Socket.hpp"

class Client : public Socket
{
public:
    Client(const std::string &protocol = Socket::TCP, const sa_family_t domain = AF_INET, const int option = 1);
    virtual ~Client();
    Client(Client const &ref);
    Client  &operator=(Client const &ref) = delete;

public:
    void Connect(const std::string &ip, const uint16_t port);
    bool isConnected(void) const;

private:
    bool        _connected;
    uint16_t    _port;
    std::string _ip;
};

#endif //PSU_2015_ZAPPY_CLIENT_HPP
