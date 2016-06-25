//
// Created by gaspar_q on 6/8/16.
//

#ifndef PSU_2015_ZAPPY_NETWORKTRASH_HPP
#define PSU_2015_ZAPPY_NETWORKTRASH_HPP

# include <functional>
# include <queue>
# include <map>
# include "Client.hpp"

class NetworkWatcher
{
public:
    typedef std::function<bool (std::string const &)> NetworkCallback;
    typedef std::function<void (std::string const &)> NetworkException;
    typedef typename std::queue<NetworkCallback>   CallbackQueue;

public:
    NetworkWatcher(std::map<std::string, NetworkException> const &exceptions = {}, std::map<Client *, CallbackQueue> const &callbacks = {});
    NetworkWatcher(NetworkWatcher const &ref);
    ~NetworkWatcher();
    NetworkWatcher  &operator=(NetworkWatcher const &ref);

public:
    NetworkWatcher &RequestServer(std::string const &request, NetworkCallback callBack, Client &from, size_t nbAnswers = 1);
    NetworkWatcher &Update(Client &from, struct timeval timeout = {0, 50});
    void    AddTempException(std::string const &name, NetworkException const &tocall);
    void    ClearTempException(void);

private:
    std::map<std::string, NetworkException>::const_iterator  GetException(std::string const &key) const;

private:
    const std::map<std::string, NetworkException> exceptions;
    std::map<std::string, NetworkException> tempException;
    std::map<Client *, CallbackQueue> callBacks;
};

#endif //PSU_2015_ZAPPY_NETWORKTRASH_HPP
