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
    inventory(),
    map(NULL),
    position(Vector2::Zero),
    orientation(Vector2::UP),
    dead(false),
    lvl(0),
    incanting(false),
    missing(0)
{
    script.LoadFile(scriptname);
    script.SetGlobalValue(this, "IA");
}

IAClient::~IAClient()
{
    if (map)
        delete(map);
}

void IAClient::Connect(const std::string &ip, const uint16_t port, std::string const &teamName)
{
    std::string answer;

    Client::Connect(ip, port);
    if (getCRLFLine(answer) && answer == "BIENVENUE")
    {
        Write(teamName);
        if (getCRLFLine(answer))
        {
            missing = static_cast<size_t >(atol(answer.c_str()));
            if (getCRLFLine(answer))
            {
                unsigned long i = answer.find(' ');
                if (i > 0 && i != std::string::npos && i < answer.length() - 1)
                {
                    map = new ZappyMap(Vector2(atoi(answer.substr(0, i - 1).c_str()), atoi(answer.substr(i + 1, answer.length() - i).c_str())));
                    script.Handler()->Select(IAClient::OnStart).Call();
                    return;
                }
            }

        }
    }
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
    incanting = false;
}

bool IAClient::IsIncanting(void) const
{
    return incanting;
}

void IAClient::Incant(void)
{
    incanting = true;
}

size_t IAClient::getMissingPeople(void) const
{
    return missing;
}

void IAClient::setMissingPeople(size_t miss)
{
    missing = miss;
}

Inventory &IAClient::Bag(void)
{
    return inventory;
}

void IAClient::See(std::vector<std::vector<std::string>> const &vision)
{
    map->Refresh(position, Vector2::Directions[orientation], vision);
}

void IAClient::TurnRight(void)
{
    orientation = static_cast<Vector2::DIR >((orientation + 1) % 4);
}

void IAClient::TurnLeft(void)
{
    orientation = static_cast<Vector2::DIR >(orientation - 1);
    if (orientation < 0)
        orientation = Vector2::LEFT;
}
