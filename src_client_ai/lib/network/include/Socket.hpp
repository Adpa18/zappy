//
// Created by gaspar_q on 6/6/16.
//

#ifndef PSU_2015_ZAPPY_SOCKET_HPP
#define PSU_2015_ZAPPY_SOCKET_HPP

# include <string>
#include <stdexcept>

extern "C"
{
# ifdef __linux__
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/select.h>
#  include <netdb.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
# elif _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
# endif
};

# include "INetStream.hpp"

# ifdef __linux__
    typedef int SOCKET;
# elif _WIN32
    typedef short sa_family_t;
# endif

class Socket : public INetStream
{
public:
    class SocketException : public std::runtime_error
    {
    public:
        SocketException(std::string const &err) :
                std::runtime_error(err)
        {

        }
        virtual ~SocketException() throw()
        {

        }
        using std::runtime_error::what;
    };

# ifdef _WIN32

    enum Action
    {
        START,
        STOP
    };

    static void WinSocket(Action todo);
# endif

public:
    enum SOCKTYPE
    {
        NOMODE,
        LISTENING,
        TALKING
    };
    static const std::string    TCP;
    static const std::string    CRLF;
    static const std::string    LF;

public:
    Socket(std::string const &protocol = Socket::TCP, const sa_family_t domain = AF_INET, int option = 1) throw(SocketException);
    virtual ~Socket();
    Socket(Socket const &ref);
    Socket  &operator=(Socket const &ref) = delete;

public:
    void Listen(const uint16_t port, const int nbc = SOMAXCONN) throw(SocketException);
    void Talk(const std::string &ip, const uint16_t port) throw(SocketException);

public:
    virtual std::string Read(int flags = 0) const;

# ifdef __linux__
    virtual void Write(std::string const &towrite, int flags = MSG_NOSIGNAL) const;
# elif _WIN32
    virtual void Write(std::string const &towrite, int flags = 0) const;
# endif
    Socket  &operator<<(std::string const &towrite);
    Socket  &operator>>(std::string &dest);
    int getCRLFLine(std::string &dest, struct timeval timeout = {1, 0}, int flags = 0) const;
    bool canRead(struct timeval timeout) const;
    bool canRead(void) const;

private:
    const std::string   protocol;
    const sa_family_t   domain;
    const int           option;
    struct sockaddr_in  sockaddr;
    SOCKET              fd;
    SOCKTYPE            type;
    mutable std::string save;
};

#endif //PSU_2015_ZAPPY_SOCKET_HPP
