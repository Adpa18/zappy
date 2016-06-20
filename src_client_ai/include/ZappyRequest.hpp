//
// Created by gaspar_q on 6/10/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYREQUEST_HPP
#define PSU_2015_ZAPPY_ZAPPYREQUEST_HPP

#include <stddef.h>
#include <ctime>
#include <NetworkWatcher.hpp>

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

class IAClient;

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
    typedef void (ZappyRequest::*ZappyCallback)(std::string const &, std::string const &);

private:
    static const std::map<Request, std::string> requests;
    static const std::map<Request, ZappyCallback> callbacks;
    static const std::map<Request, std::clock_t > requTimer;
    static const int maxRequest;
    static std::clock_t getRequTimer(Request const &request);

public:
    ZappyRequest(IAClient *client);
    ZappyRequest(ZappyRequest const &ref);
    ~ZappyRequest();
    ZappyRequest    &operator=(ZappyRequest const &ref) = delete;

public:
    void MakeRequest(Request request, std::string const &toConcat = "") throw(BadRequestException);
    void Update();
    bool IsARequest(Request request) const;
    bool IsTimerFinished(Request const &request) const;
    void AddTimer(Request request, size_t timer);

private:
    void ReceiveServerPong(Request request, std::string const &answer, std::string const &param);
    void Req_move(const std::string &answer, const std::string &param);
    void Req_takeObj(const std::string &answer, const std::string &param);
    void Req_dropObj(const std::string &answer, const std::string &param);
    void Req_seeForward(const std::string &answer, const std::string &param);
    void Req_stockInventory(const std::string &answer, const std::string &param);
    void Req_incantation(const std::string &answer, const std::string &param);
    void Req_connectNbr(const std::string &answer, const std::string &param);

private:
    void ResolveState(const std::string answer);

private:
    IAClient                                        *client;
    NetworkWatcher                                  watcher;
    Request                                         lastRequest;
    bool                                            status;
    int                                             nbRequest;
    std::map<Request, std::clock_t >                lastReqOf;
    std::map<Request, size_t>                       timers;
    std::queue<std::pair<Request, std::clock_t > >  requestQueue;
    double                                          serverT;
    std::clock_t                                    lastAnswer;
};

#endif //PSU_2015_ZAPPY_ZAPPYREQUEST_HPP
