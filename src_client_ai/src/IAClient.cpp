//
// Created by gaspar_q on 6/7/16.
//

#include "IAClient.hpp"
#include "LuaHandler.hpp"

const std::string    IAClient::Default = "default.lua";
const std::string    IAClient::OnStart = "OnStart";
const std::string    IAClient::OnUpdate = "OnUpdate";
const std::string    IAClient::OnReceive = "OnReceive";

const std::string    IAClient::className = typeid(IAClient).name();
Lua::LuaClass<IAClient>::LuaPrototype    prototype = {{}, {}};

IAClient::IAClient(const std::string &scriptname) :
    script()
{
    script.LoadFile(scriptname);
    script.SetGlobalValue(this, "IA");
}

IAClient::~IAClient()
{

}

void IAClient::Connect(const std::string &ip, const uint16_t port)
{
    Client::Connect(ip, port);
    script.Handler()->Select(IAClient::OnStart).Call();
}

void IAClient::Update(void)
{
    script.Handler()->Select(IAClient::OnUpdate).Call();
}

void IAClient::Receive()
{
    script.Handler()->Select(IAClient::OnReceive).Call();
}

int IAClient::callTest(std::string const &res)
{
    std::cout << res << std::endl;
    return 0;
}
