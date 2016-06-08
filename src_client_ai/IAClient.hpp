//
// Created by gaspar_q on 6/7/16.
//

#ifndef PSU_2015_ZAPPY_IACLIENT_HPP
#define PSU_2015_ZAPPY_IACLIENT_HPP

#include "Client.hpp"
#include "LuaScript.hpp"

class IAClient : public Client
{
public:
    static const std::string    Default;
    static const std::string    OnStart;
    static const std::string    OnUpdate;
    static const std::string    OnReceive;

    static const std::string    className;
    static const Lua::LuaClass<IAClient>::LuaPrototype    prototype;

public:
    explicit IAClient(std::string const &scriptname = Default);
    virtual ~IAClient();
    IAClient(IAClient const &ref) = delete;
    IAClient    &operator=(IAClient const &ref) = delete;

public:
    virtual void Connect(const std::string &ip, const uint16_t port);
    void Update(void);
    void Receive(void);

private:
    Lua::LuaScript      script;
};

#endif //PSU_2015_ZAPPY_IACLIENT_HPP
