//
// Created by gaspar_q on 6/6/16.
//

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "Socket.hpp"

const std::string Socket::TCP = "TCP";

Socket::Socket(std::string const &protocol, const sa_family_t domain, int option) throw(SocketException) :
        protocol(protocol),
        domain(domain),
        option(option),
        sockaddr(),
        fd(-1),
        type(Socket::NOMODE)
{
    struct protoent	*proto = getprotobyname(protocol.c_str());

    if (proto == NULL)
        throw Socket::SocketException(strerror(errno));
    fd = socket(domain, SOCK_STREAM, proto->p_proto);
    if (fd == -1)
        throw Socket::SocketException(strerror(errno));
    if (setsockopt(fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char *)&option, sizeof(option)) == -1)
        throw Socket::SocketException(strerror(errno));
}

Socket::~Socket()
{
    close(fd);
}

Socket::Socket(Socket const &ref) :
        Socket(ref.protocol, ref.domain, ref.option)
{
}

void Socket::Listen(const uint16_t port, const int nbc) throw(SocketException)
{
    socklen_t len = sizeof(sockaddr);

    if (type != NOMODE)
        return;
    sockaddr.sin_family = domain;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (const struct sockaddr *)&sockaddr, len) == -1 || listen(fd, nbc) == -1)
        throw SocketException(strerror(errno));
    type = LISTENING;
}

void Socket::Talk(const std::string &ip, const uint16_t port) throw(SocketException)
{
    socklen_t len = sizeof(sockaddr);

    if (type != NOMODE)
        return;
    sockaddr.sin_family = domain;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    if (connect(fd, (struct sockaddr *)&sockaddr, len) == -1)
        throw SocketException(strerror(errno));
    type = TALKING;
}

std::string Socket::Read(void) const
{
    std::string toreturn;
    char        buff[BUFSIZ];

    memset(buff, 0, BUFSIZ);
    while (read(fd, buff, BUFSIZ - 1))
    {
        toreturn += buff;
        memset(buff, 0, BUFSIZ);
    }
    return toreturn;
}

void Socket::Write(std::string const &towrite) const
{
    size_t len = towrite.size();
    size_t wri = 0;

    do
    {
        wri += write(fd, towrite.substr(wri, len - wri).c_str(), len - wri);
    } while (wri < len);
}
