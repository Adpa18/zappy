//
// Created by gaspar_q on 6/8/16.
//

#ifndef PSU_2015_ZAPPY_NETWORKTRASH_HPP
#define PSU_2015_ZAPPY_NETWORKTRASH_HPP

#include <functional>
#include <bits/stl_bvector.h>

/**
 * TODO:
 *  -   Connect The ia
 *  -   Do the commands (make a système with callBacks when getting a server notification)
 */
class NetworkWatcher
{
public:
    typedef std::function<int (std::string const &)> NetworkCallback;

private:
    typedef typename std::vector<NetworkCallback>   CallbackVectors;

public:
    NetworkWatcher(CallbackVectors callbacks = {});
    NetworkWatcher(NetworkWatcher const &ref);
    ~NetworkWatcher();
    NetworkWatcher  &operator=(NetworkWatcher const &ref);

public:
    //todo implement a call to the callbacks after a server notif

private:
    CallbackVectors callBacks;
};

#endif //PSU_2015_ZAPPY_NETWORKTRASH_HPP
