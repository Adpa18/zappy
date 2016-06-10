//
// Created by gaspar_q on 6/10/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYREQUEST_HPP
#define PSU_2015_ZAPPY_ZAPPYREQUEST_HPP

#include <stddef.h>
#include <NetworkWatcher.hpp>
#include "IAClient.hpp"

class BadRequestException : public std::runtime_error
{
public:
    BadRequestException(const std::string &err) :
            std::runtime_error(err)
    {

    }
    virtual ~BadRequestException() throw()
    {

    }
    using std::runtime_error::what;
};

class ZappyRequest
{
public:
    enum    Request
    {
        MOVE,
        RIGHT,
        LEFT,
        SEE,
        STOCK,
        TAKE,
        DROP,
        EXPULSE,
        BROADCAST,
        INCANTATION,
        LAYEGG,
        CONNECTNBR
    };
    typedef void (ZappyRequest::*ZappyCallback)(std::string const &) const;

private:
    static const std::map<Request, std::string> requests;
    static const std::map<Request, ZappyCallback> callbacks;

public:
    ZappyRequest(IAClient &toWatch);
    ZappyRequest(ZappyRequest const &ref);
    ~ZappyRequest();
    ZappyRequest    &operator=(ZappyRequest const &ref) = delete;

public:
    void MakeRequest(Request request, std::string const &toConcat = "") throw(BadRequestException);
    void Update();
    bool IsARequest(Request request) const;

private:
    void Req_moveForward(const std::string &answer) const;
    void Req_turnRight(const std::string &answer) const;
    void Req_turnLeft(const std::string &answer) const;
    void Req_seeForward(const std::string &answer) const;
    void Req_stockInventory(const std::string &answer) const;
    void Req_takeObject(const std::string &answer) const;
    void Req_dropObject(const std::string &answer) const;
    void Req_expulsePlayers(const std::string &answer) const;
    void Req_broadcastText(const std::string &answer) const;
    void Req_incantation(const std::string &answer) const;
    void Req_layEgg(const std::string &answer) const;
    void Req_connectNbr(const std::string &answer) const;

private:
    IAClient        &client;
    NetworkWatcher  watcher;
};

#endif //PSU_2015_ZAPPY_ZAPPYREQUEST_HPP
