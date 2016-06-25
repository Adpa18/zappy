//
// Created by gaspar_q on 6/8/16.
//

#include <iostream>
#include "NetworkWatcher.hpp"

/**
 * \brief Constructor with a prepared queue and default
 * \param actionsQueue A queue of actions already prepared
 */
NetworkWatcher::NetworkWatcher(std::map<std::string, NetworkWatcher::NetworkException> const &exception, std::map<Client *, NetworkWatcher::CallbackQueue> const &actionsQueue) :
        exceptions(exception),
        callBacks(actionsQueue)
{

}

/**
 * \brief Copy constructor
 * \param ref A reference on a already prepared NetworkWatcher
 */
NetworkWatcher::NetworkWatcher(NetworkWatcher const &ref) :
    NetworkWatcher(ref.exceptions, ref.callBacks)
{

}

/**
 * \brief Destructor
 */
NetworkWatcher::~NetworkWatcher()
{

}

/**
 * \brief Copy operator for coplience
 * \param ref A reference on the object to copy
 * \return A reference on 'this' pointer
 */
NetworkWatcher &NetworkWatcher::operator=(NetworkWatcher const &ref)
{
    callBacks = ref.callBacks;
    return *this;
}

/**
 * \brief Will request to the server pointed by the client 'from' the request 'request' and associate a callback
 * \param request The request to ping to the server
 * \param callBack The callback associated to the request ping
 * \param from The client linked to the server to ping
 */
NetworkWatcher &NetworkWatcher::RequestServer(std::string const &request, NetworkWatcher::NetworkCallback callBack,
                                              Client &from, size_t nbAnswers)
{
    from.Write(request);
    for (size_t i = 0; i < nbAnswers; ++i)
    {
        callBacks[&from].push(callBack);
    }
    return *this;
}

/**
 * \brief Will update the watcher for a specific client
 * \param from The client to which update the action queue
 */
NetworkWatcher &NetworkWatcher::Update(Client &from, struct timeval timeout)
{
    std::map<std::string, NetworkException>::const_iterator  it;
    std::string line;

    if (from.getCRLFLine(line, timeout))
    {
        std::cout << "LINE : " << line.substr(0, 20) << std::endl;
        if ((it = GetException(line)) != exceptions.end())
            it->second(line);
        else if ((!callBacks[&from].empty()))
        {
            if (callBacks[&from].front()(line))
                callBacks[&from].pop();
        }
    }
    return *this;
}

std::map<std::string, NetworkWatcher::NetworkException>::const_iterator NetworkWatcher::GetException(std::string const &key) const
{
    for (std::map<std::string, NetworkException>::const_iterator  it = exceptions.begin(), end = exceptions.end(); it != end; ++it)
    {
        if (key.find(it->first) != std::string::npos)
            return it;
    }
    return exceptions.end();
}
