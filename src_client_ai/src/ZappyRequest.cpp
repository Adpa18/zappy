//
// Created by gaspar_q on 6/10/16.
//

#include <ActionHandler.hpp>
#include "ZappyRequest.hpp"

/**
 * \brief Variable for associating a Request code to a request string command
 */
const std::map<ZappyRequest::Request, std::string> ZappyRequest::requests = {
        {ZappyRequest::MOVE, ""},
        {ZappyRequest::RIGHT, ""},
        {ZappyRequest::LEFT, ""},
        {ZappyRequest::SEE, ""},
        {ZappyRequest::STOCK, ""},
        {ZappyRequest::TAKE, ""},
        {ZappyRequest::DROP, ""},
        {ZappyRequest::EXPULSE, ""},
        {ZappyRequest::BROADCAST, ""},
        {ZappyRequest::INCANTATION, ""},
        {ZappyRequest::LAYEGG, ""},
        {ZappyRequest::CONNECTNBR, ""}
};

/**
 * \brief Variable to associate a Request code to a method pointer
 */
const std::map<ZappyRequest::Request, ZappyRequest::ZappyCallback> ZappyRequest::callbacks = {
        {ZappyRequest::MOVE, &ZappyRequest::Req_moveForward},
        {ZappyRequest::RIGHT, &ZappyRequest::Req_turnRight},
        {ZappyRequest::LEFT, &ZappyRequest::Req_turnLeft},
        {ZappyRequest::SEE, &ZappyRequest::Req_seeForward},
        {ZappyRequest::STOCK, &ZappyRequest::Req_stockInventory},
        {ZappyRequest::TAKE, &ZappyRequest::Req_takeObject},
        {ZappyRequest::DROP, &ZappyRequest::Req_dropObject},
        {ZappyRequest::EXPULSE, &ZappyRequest::Req_expulsePlayers},
        {ZappyRequest::BROADCAST, &ZappyRequest::Req_broadcastText},
        {ZappyRequest::INCANTATION, &ZappyRequest::Req_incantation},
        {ZappyRequest::LAYEGG, &ZappyRequest::Req_layEgg},
        {ZappyRequest::CONNECTNBR, &ZappyRequest::Req_connectNbr}
};

/**
 * \brief Constructor in which you have to give a reference on the client you make requests
 */
ZappyRequest::ZappyRequest(IAClient &toWatch) :
    client(toWatch)
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
 * \brief Resolve the request Move Forward
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_moveForward(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Turn Right
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_turnRight(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Turn Left
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_turnLeft(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request See Forward
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_seeForward(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Stock Inventory
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_stockInventory(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Move Forward
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_takeObject(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Drop object
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_dropObject(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Expulse Players
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_expulsePlayers(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Broadcast Text
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_broadcastText(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Incantation
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_incantation(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Lay Egg
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_layEgg(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Resolve the request Connect Nbr
 * \param answer The answer received from the server
 */
void ZappyRequest::Req_connectNbr(const std::string &answer) const
{
    (void)answer;
}

/**
 * \brief Make a Zappy Request you can set 'toConcat' parameter to insert a request parameter
 * \param toConcat Allow user to add a request parameter
 */
void ZappyRequest::MakeRequest(ZappyRequest::Request request, const std::string &toConcat)  throw(BadRequestException)
{
    if (!IsARequest(request))
        throw BadRequestException("No request found");

    std::string req = ZappyRequest::requests.find(request)->second + (toConcat.empty() ? "" : " " + toConcat);
    ZappyRequest::ZappyCallback tobind = callbacks.find(request)->second;
    NetworkWatcher::NetworkCallback tocall = ActionHandler<ZappyRequest>::MethodToFunction<ZappyCallback, std::string>(*this, tobind);

    watcher.RequestServer(req, tocall, client);
}

/**
 * \brief Will call NetworkWatcher update function with to corresponding client
 */
void ZappyRequest::Update()
{
    watcher.Update(client);
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
