//
// Created by gaspar_q on 6/8/16.
//

#ifndef PSU_2015_ZAPPY_NETWORKTRASH_HPP
#define PSU_2015_ZAPPY_NETWORKTRASH_HPP

# include <functional>
# include <queue>
# include <map>
# include "Client.hpp"

/**
 * TODO:
 *  -   Connect The ia
 *  -   Do the commands (make a système with callBacks when getting a server notification)
 */
class NetworkWatcher
{
public:
    typedef std::function<void (std::string const &)> NetworkCallback;
    typedef typename std::queue<NetworkCallback>   CallbackQueue;

public:
    NetworkWatcher(std::map<std::string, NetworkCallback> const &exceptions = {}, std::map<Client *, CallbackQueue> const &callbacks = {});
    NetworkWatcher(NetworkWatcher const &ref);
    ~NetworkWatcher();
    NetworkWatcher  &operator=(NetworkWatcher const &ref);

public:
    NetworkWatcher &RequestServer(std::string const &request, NetworkCallback callBack, Client &from, size_t nbAnswers = 1);
    NetworkWatcher &Update(Client &from);

private:
    const std::map<std::string, NetworkCallback> exceptions;
    std::map<Client *, CallbackQueue> callBacks;
};

#endif //PSU_2015_ZAPPY_NETWORKTRASH_HPP
