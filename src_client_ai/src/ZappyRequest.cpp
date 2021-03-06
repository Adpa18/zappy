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
        {ZappyRequest::DROP, &ZappyRequest::Req_dropObj},
        {ZappyRequest::RIGHT, &ZappyRequest::Req_turnRight},
        {ZappyRequest::LEFT, &ZappyRequest::Req_turnLeft}
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
                    {"message", ActionHandler<IAClient>::MethodToFunction<void (IAClient::*)(std::string const &), std::string>(*client, &IAClient::ReceiveMessage)},
                    {"deplacement", ActionHandler<IAClient>::MethodToFunction<void (IAClient::*)(std::string const &), std::string>(*client, &IAClient::PushedTo)}
            }),
    lastRequest(DEFAULT),
    status(false),
    nbRequest(0),
    lastReqOf(),
    timers(),
    requestQueue(),
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
void ZappyRequest::MakeRequest(ZappyRequest::Request request, const std::string &toConcat)
{
    if (request == DEFAULT || IsSaturated())
        return;
    if (!IsARequest(request))
        throw BadRequestException("No request found");

    std::string req = ZappyRequest::requests.find(request)->second + (toConcat.empty() ? "" : " " + toConcat);

    lastReqOf[request] = std::clock();
    requestQueue.push(std::make_pair(request, std::clock()));
    try
    {
        watcher.RequestServer(req, [this, request, toConcat] (std::string const &s)
            {
                return (ReceiveServerPong(request, s, toConcat));
            }, *client);
        ++nbRequest;
    }
    catch (std::exception &exception)
    {
        std::cerr << "Make request: " << exception.what() << std::endl;
    }
}

/**
 * \brief Will call NetworkWatcher update function with to corresponding client
 */
void ZappyRequest::Update(struct timeval timeout)
{
    watcher.Update(*client, timeout);
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
bool ZappyRequest::ReceiveServerPong(ZappyRequest::Request request, std::string const &answer, const std::string &param)
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
    ResolveState(answer);
    try
    {
        it = callbacks.find(request);
        if (it != callbacks.end())
        {
            (*this.*it->second)(answer, param);
        }
        client->Receive(request, answer);
    }
    catch (std::exception &exception)
    {
        std::cerr << "\e[31mReceive server pong:\e[0m " << exception.what() << std::endl;
        return false;
    }
    --nbRequest;
    requestQueue.pop();
    return (true);
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
void ZappyRequest::Req_incantation(const std::string &answer, const std::string &s)
{
    if (answer == "elevation en cours")
    {
        client->Incant();
        watcher.AddTempException("ko", [this] (std::string const &line)
            {
                this->client->IncantationFailure(line);
            });
    }
    else if (answer != "ko")
        throw BadRequestException("Bad answer received for incantation '" + s + "'");
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
        client->TakeObj(Inventory::getObjectFromName(param));
}

/**
 * \brief Resolve the request take object
 * \param param The parameter giver in the request
 */
void ZappyRequest::Req_dropObj(const std::string &answer, const std::string &param)
{
    if (status)
        client->DropObj(Inventory::getObjectFromName(param));
    if (answer != "ok" && answer != "ko")
        throw BadRequestException("Bad answer received drop '" + param + "'");
}

/**
 * \brief Resolve the request move
 */
void ZappyRequest::Req_move(const std::string &a, const std::string &s)
{
    client->Moved();
    if (a != "ok")
        throw BadRequestException("Bad answer received move '" + s + "'");
}

/**
 * \brief Resolve turn right
 */
void ZappyRequest::Req_turnRight(const std::string &a, const std::string &s)
{
    client->TurnRight();
    if (a != "ok")
        throw BadRequestException("Bad answer received right '" + s + "'");
}

/**
 * \brief Resolve turn left
 */
void ZappyRequest::Req_turnLeft(const std::string &a, const std::string &s)
{
    client->TurnLeft();
    if (a != "ok")
        throw BadRequestException("Bad answer received left '" + s + "'");
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
bool ZappyRequest::IsTimerFinished(const ZappyRequest::Request &request) const
{
    std::map<Request, size_t >::const_iterator reqT = timers.find(request);
    std::map<Request, std::clock_t>::const_iterator lastR = lastReqOf.find(request);

    if (reqT == timers.end() || lastR == lastReqOf.end())
        return true;
    return std::clock() >= lastR->second + ((reqT->second * CLOCKS_PER_SEC) / serverT);
}

void ZappyRequest::AddTimer(Request request, size_t timer)
{
    timers[request] = timer;
}

void ZappyRequest::MakeBlockedRequest(Request request, const std::string &toContat)
{
    MakeRequest(request, toContat);
    if (client->canRead())
        Update({0, 0});
}

bool ZappyRequest::IsSaturated(void) const
{
    return nbRequest == ZappyRequest::maxRequest;
}

void ZappyRequest::ClearTempException()
{
    watcher.ClearTempException();
}