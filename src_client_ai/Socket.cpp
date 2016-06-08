//
// Created by gaspar_q on 6/6/16.
//

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <iostream>
#include "Socket.hpp"

const std::string Socket::TCP = "TCP";
const std::string Socket::CRLF = "\r\n";
const std::string Socket::LF = "\n";

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

std::string Socket::Read(int flags) const
{
    std::string toreturn;
    char        buff[BUFSIZ];

    memset(buff, 0, BUFSIZ);
    if (recv(fd, buff, BUFSIZ - 1, flags) == -1)
        throw SocketException(strerror(errno));
    toreturn += buff;
    return toreturn;
}

void Socket::Write(std::string const &towrite, int flags) const
{
    if (send(fd, (towrite + Socket::LF).c_str(), towrite.length() + Socket::LF.length(), flags) == -1)
        throw SocketException(strerror(errno));
}

Socket &Socket::operator>>(std::string &dest)
{
    dest = Read();
    return *this;
}

Socket &Socket::operator<<(std::string const &towrite)
{
    Write(towrite);
    return *this;
}

int Socket::getCRLFLine(std::string &dest, struct timeval timeout, int flags) const
{
    unsigned long   posCRLF = save.find(Socket::CRLF);
    unsigned long   posLF = save.find(Socket::LF);

    if (posCRLF != std::string::npos)
    {
        dest = save.substr(0, posCRLF);
        save = save.substr(posCRLF + Socket::CRLF.length(), save.length() - posCRLF - Socket::CRLF.length());
    }
    else if (posLF != std::string::npos)
    {
        dest = save.substr(0, posLF);
        save = save.substr(posLF + Socket::LF.length(), save.length() - posLF - Socket::LF.length());
    }
    else if (canRead(timeout))
    {
        save += Read(flags);
        return getCRLFLine(dest, timeout, flags);
    }
    else
    {
        dest = save;
        save.clear();
    }
    return !dest.empty();
}

bool Socket::canRead(struct timeval timeout) const
{
    fd_set  set;

    FD_ZERO(&set);
    FD_SET(fd, &set);
    return select(fd + 1, &set, NULL, NULL, &timeout) != 0;
}
