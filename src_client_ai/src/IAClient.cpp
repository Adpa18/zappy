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
    script(),
    mapDimensions(),
    dead(false),
    lvl(0)
{
    script.LoadFile(scriptname);
    script.SetGlobalValue(this, "IA");
}

IAClient::~IAClient()
{

}

void IAClient::Connect(const std::string &ip, const uint16_t port, std::string const &teamName)
{
    std::string answer;

    Client::Connect(ip, port);
    if (getCRLFLine(answer) && answer == "BIENVENUE")
    {
        Write(teamName);
        if (getCRLFLine(answer) && atoi(answer.c_str()) > 0 && getCRLFLine(answer))
        {
            unsigned long i = answer.find(' ');

            if (i > 0 && i != std::string::npos && i < answer.length() - 1)
            {
                mapDimensions = {atoi(answer.substr(0, i - 1).c_str()), atoi(answer.substr(i + 1, answer.length() - i).c_str())};
                script.Handler()->Select(IAClient::OnStart).Call();
            }
        }
    }
    else
        throw SocketException("Unable to connect");
}

void IAClient::Update(void)
{
    script.Handler()->Select(IAClient::OnUpdate).Call();
}

void IAClient::Receive()
{
    script.Handler()->Select(IAClient::OnReceive).Call();
}

const IAClient::Vector2 &IAClient::getMapDimmensions(void) const
{
    return mapDimensions;
}

void IAClient::Die(void)
{
    dead = true;
}

bool IAClient::IsDead(void) const
{
    return dead;
}

void IAClient::Upgrade(const std::string &string)
{
    std::cout << "You have been upgraded: '" << string << "'" << std::endl;
    lvl++;
}
