//
// Created by gaspar_q on 6/6/16.
//

#ifndef PSU_2015_ZAPPY_SOCKET_HPP
#define PSU_2015_ZAPPY_SOCKET_HPP

# include <string>
#include <stdexcept>

extern "C"
{
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
};

# include "IStream.hpp"

class Socket : public IStream
{
public:
    class SocketException : std::runtime_error
    {
    public:
        SocketException(std::string const &err) :
                std::runtime_error(err)
        {

        }
        virtual ~SocketException() throw()
        {

        }
    };

public:
    enum SOCKTYPE
    {
        NOMODE,
        LISTENING,
        TALKING
    };
    static const std::string    TCP;

public:
    Socket(std::string const &protocol = Socket::TCP, const sa_family_t domain = AF_INET, int option = 1) throw(SocketException);
    virtual ~Socket();
    Socket(Socket const &ref);
    Socket  &operator=(Socket const &ref) = delete;

public:
    void Listen(const uint16_t port, const int nbc = SOMAXCONN) throw(SocketException);
    void Talk(const std::string &ip, const uint16_t port) throw(SocketException);

public:
    virtual std::string Read(void) const;
    virtual void Write(std::string const &towrite) const;

private:
    const std::string   protocol;
    const sa_family_t   domain;
    const int           option;
    struct sockaddr_in  sockaddr;
    int                 fd;
    SOCKTYPE            type;
};

#endif //PSU_2015_ZAPPY_SOCKET_HPP
