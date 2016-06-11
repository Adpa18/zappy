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
        DEFAULT,
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
    typedef void (ZappyRequest::*ZappyCallback)(std::string const &);

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
    void ReceiveServerPong(Request request, std::string const &answer);
    void Req_seeForward(const std::string &answer);
    void Req_stockInventory(const std::string &answer);
    void Req_incantation(const std::string &answer);
    void Req_connectNbr(const std::string &answer);

private:
    void ResolveState(const std::string answer);

private:
    IAClient        &client;
    NetworkWatcher  watcher;
    Request         lastRequest;
    bool            status;
};

#endif //PSU_2015_ZAPPY_ZAPPYREQUEST_HPP
