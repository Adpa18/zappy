//
// Created by gaspar_q on 6/8/16.
//

#include "NetworkWatcher.hpp"

/**
 * \brief Constructor with a prepared queue and default
 * \param actionsQueue A queue of actions already prepared
 */
NetworkWatcher::NetworkWatcher(std::map<std::string, NetworkWatcher::NetworkCallback> const &exception, std::map<Client *, NetworkWatcher::CallbackQueue> const &actionsQueue) :
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
NetworkWatcher &NetworkWatcher::Update(Client &from)
{
    if (!callBacks[&from].empty())
    {
        std::string line;
        NetworkCallback func = callBacks[&from].front();
        std::map<std::string, NetworkCallback>::const_iterator  it;

        if (from.getCRLFLine(line, {0, 0}))
        {
            if ((it = exceptions.find(line)) != exceptions.end())
                it->second(line);
            else
            {
                func(line);
                callBacks[&from].pop();
            }
        }
    }
    return *this;
}
