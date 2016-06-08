//
// Created by gaspar_q on 6/8/16.
//

#include "NetworkTrash.hpp"

NetworkWatcher::NetworkWatcher(std::vector<std::function<int()>> vector) :
    callBacks(vector)
{

}

NetworkWatcher::NetworkWatcher(NetworkWatcher const &ref) :
    NetworkWatcher(ref.callBacks)
{

}

NetworkWatcher::~NetworkWatcher()
{

}

NetworkWatcher &NetworkWatcher::operator=(NetworkWatcher const &ref)
{
    return *this;
}
