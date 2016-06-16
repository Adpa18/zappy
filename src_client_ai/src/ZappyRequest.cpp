//
// Created by gaspar_q on 6/10/16.
//

#include <ActionHandler.hpp>
#include <ZappyData.hpp>
#include <Inventory.hpp>
#include <IAClient.hpp>
#include "ZappyRequest.hpp"

/**
 * \brief Variable for associating a Request code to a request string command
 */
const std::map<ZappyRequest::Request, std::string> ZappyRequest::requests = {
        {ZappyRequest::MOVE, "avance"},
        {ZappyRequest::RIGHT, "droite"},
        {ZappyRequest::LEFT, "gauche"},
        {ZappyRequest::SEE, "voir"},
        {ZappyRequest::STOCK, "inventaire"},
        {ZappyRequest::TAKE, "prend"},
        {ZappyRequest::DROP, "pose"},
        {ZappyRequest::EXPULSE, "expulse"},
        {ZappyRequest::BROADCAST, "broadcast"},
        {ZappyRequest::INCANTATION, "incantation"},
        {ZappyRequest::LAYEGG, "fork"},
        {ZappyRequest::CONNECTNBR, "connect_nbr"}
};

/**
 * \brief Variable to associate a Request code to a method pointer
 */
const std::map<ZappyRequest::Request, ZappyRequest::ZappyCallback> ZappyRequest::callbacks = {
        {ZappyRequest::MOVE, &ZappyRequest::Req_move},
        {ZappyRequest::SEE, &ZappyRequest::Req_seeForward},
        {ZappyRequest::STOCK, &ZappyRequest::Req_stockInventory},
        {ZappyRequest::INCANTATION, &ZappyRequest::Req_incantation},
        {ZappyRequest::CONNECTNBR, &ZappyRequest::Req_connectNbr},
        {ZappyRequest::TAKE, &ZappyRequest::Req_takeObj},
        {ZappyRequest::DROP, &ZappyRequest::Req_dropObj}
};

const std::map<ZappyRequest::Request, std::clock_t> ZappyRequest::requTimer = {
        {ZappyRequest::MOVE, 7},
        {ZappyRequest::RIGHT, 7},
        {ZappyRequest::LEFT, 7},
        {ZappyRequest::SEE, 7},
        {ZappyRequest::STOCK, 1},
        {ZappyRequest::TAKE, 7},
        {ZappyRequest::DROP, 7},
        {ZappyRequest::EXPULSE, 7},
        {ZappyRequest::BROADCAST, 7},
        {ZappyRequest::INCANTATION, 300},
        {ZappyRequest::LAYEGG, 42},
        {ZappyRequest::CONNECTNBR,  0}
};

const int ZappyRequest::maxRequest = 10;

/**
 * \brief Constructor in which you have to give a reference on the client you make requests
 */
ZappyRequest::ZappyRequest(IAClient *client) :
    client(client),
    watcher({
                    {"mort", ActionHandler<IAClient>::MethodToFunction<void (IAClient::*)(std::string), std::string>(*client, (void (IAClient::*)(std::string))&IAClient::Die)},
                    {"niveau actuel : ", ActionHandler<IAClient>::MethodToFunction<void (IAClient::*)(std::string const &), std::string>(*client, &IAClient::Upgrade)},
                    {"message", ActionHandler<IAClient>::MethodToFunction<void (IAClient::*)(std::string const &), std::string>(*client, &IAClient::ReceiveMessage)}
            }),
    lastRequest(DEFAULT),
    status(false),
    nbRequest(0),
    nextRequest({
                        {ZappyRequest::Request::MOVE, std::clock()},
                        {ZappyRequest::Request::RIGHT, std::clock()},
                        {ZappyRequest::Request::LEFT, std::clock()},
                        {ZappyRequest::Request::STOCK, std::clock()},
                        {ZappyRequest::Request::TAKE, std::clock()},
                        {ZappyRequest::Request::DROP, std::clock()},
                        {ZappyRequest::Request::EXPULSE, std::clock()},
                        {ZappyRequest::Request::BROADCAST, std::clock()},
                        {ZappyRequest::Request::INCANTATION, std::clock()},
                        {ZappyRequest::Request::LAYEGG, std::clock()},
                        {ZappyRequest::Request::CONNECTNBR, std::clock()}
                }),
    serverT(100),
    lastAnswer(std::clock())
{

}

/**
 * \brief Copy constructor
 */
ZappyRequest::ZappyRequest(ZappyRequest const &ref) :
    ZappyRequest(ref.client)
{

}

/**
 * \brief Destructor
 */
ZappyRequest::~ZappyRequest()
{

}

/**
 * \brief Make a Zappy Request you can set 'toConcat' parameter to insert a request parameter
 * \param toConcat Allow user to add a request parameter
 */
void ZappyRequest::MakeRequest(ZappyRequest::Request request, const std::string &toConcat) throw(BadRequestException)
{
    if (request == DEFAULT || nbRequest == ZappyRequest::maxRequest)
        return;
    if (!IsARequest(request))
        throw BadRequestException("No request found");

    std::string req = ZappyRequest::requests.find(request)->second + (toConcat.empty() ? "" : " " + toConcat);

    nextRequest[request] = std::clock() + static_cast<std::clock_t >((static_cast<double>(getRequTimer(request)) / serverT) * CLOCKS_PER_SEC);
    requestQueue.push(std::make_pair(request, std::clock()));
    watcher.RequestServer(req, [this, request, toConcat] (std::string const &s) { ReceiveServerPong(request, s, toConcat); }, *client);
    ++nbRequest;
}

/**
 * \brief Will call NetworkWatcher update function with to corresponding client
 */
void ZappyRequest::Update()
{
    watcher.Update(*client);
}

/**
 * \brief Will check if a request code is a good request code
 * \return True if it is, false either
 */
bool ZappyRequest::IsARequest(ZappyRequest::Request request) const
{
    if (request >= MOVE && request <= CONNECTNBR)
        return true;
    return false;
}

/**
 * \brief Will resolve the state of the command pong received and will set the status approriately
 * \param answer The answer of the server, if 'ko' the state will be set to false, true either
 */
void ZappyRequest::ResolveState(const std::string answer)
{
    if (answer.find("ko") != std::string::npos)
        status = false;
    else
        status = true;
}

/**
 * \brief Callback when we receive a pong command replied
 * \param request The request to which the command is linked
 * \param answer The answer of the server
 */
void ZappyRequest::ReceiveServerPong(ZappyRequest::Request request, std::string const &answer, const std::string &param)
{
    std::map<Request, ZappyCallback>::const_iterator    it;
    std::clock_t duration = std::clock();

    lastRequest = request;
    if (requestQueue.front().second <= lastAnswer)
        duration -= lastAnswer;
    else
        duration -= requestQueue.front().second;
    serverT = static_cast<double >(getRequTimer(requestQueue.front().first) * CLOCKS_PER_SEC) / static_cast<double>(duration);
    lastAnswer = std::clock();
    requestQueue.pop();
    ResolveState(answer);
    try
    {
        it = callbacks.find(request);
        if (it != callbacks.end())
            (*this.*it->second)(answer, param);
        client->Receive(request, answer);
    }
    catch (std::exception &exception)
    {
        std::cerr << "Receive server pong: " << exception.what() << std::endl;
    }
    --nbRequest;
}

/**
 * \brief Resolve the request See Forward
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_seeForward(const std::string &answer, const std::string &)
{
    client->RefreshMap(ZappyData::deserialize(answer));
}

/**
 * \brief Resolve the request Stock Inventory
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_stockInventory(const std::string &answer, const std::string &)
{
    client->Bag().Refresh(ZappyData::deserialize(answer));
}

/**
 * \brief Resolve the request Incantation
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_incantation(const std::string &answer, const std::string &)
{
    if (answer == "elevation en cours")
        client->Incant();
}

/**
 * \brief Resolve the request Connect Nbr
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_connectNbr(const std::string &answer, const std::string &)
{
    client->setMissingPeople(strtoul(answer.c_str(), NULL, 10));
}

/**
 * \brief Resolve the request take object
 * \param param The parameter giver in the request
 */
void ZappyRequest::Req_takeObj(const std::string &, const std::string &param)
{
    if (status)
        client->Bag().Add(Inventory::getObjectFromName(param));
}

/**
 * \brief Resolve the request take object
 * \param param The parameter giver in the request
 */
void ZappyRequest::Req_dropObj(const std::string &, const std::string &param)
{
    if (status)
        client->Bag().Remove(Inventory::getObjectFromName(param));
}

/**
 * \brief Resolve the request move
 */
void ZappyRequest::Req_move(const std::string &, const std::string &)
{
    client->Moved();
}

/**
 * \brief Get the time of a specific request
 * \param request The request you want to get the time
 * \return The time of a specific request
 */
std::clock_t ZappyRequest::getRequTimer(const ZappyRequest::Request &request)
{
    std::map<ZappyRequest::Request, std::clock_t>::const_iterator   it = requTimer.find(request);

    if (it == requTimer.end())
        throw BadRequestException("No such request: " + std::to_string(request));
    return it->second;
}

/**
 * \brief Check if you can make a command that is not currently working (not safe)
 * \param request The request you want to check
 * \return If you can make an unstacked request
 */
bool ZappyRequest::CanMakeUnStackedRequest(const ZappyRequest::Request &request) const
{
    return std::clock() >= nextRequest.find(request)->second;
}
