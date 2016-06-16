//
// Created by gaspar_q on 6/7/16.
//

#include "IAClient.hpp"
#include "LuaHandler.hpp"

const std::string    IAClient::Default = "./lua/default.lua";
const std::string    IAClient::OnStart = "OnStart";
const std::string    IAClient::OnUpdate = "OnUpdate";
const std::string    IAClient::OnReceive = "OnReceive";

const std::string    IAClient::className = typeid(IAClient).name();
const Lua::LuaClass<IAClient>::LuaPrototype    IAClient::prototype = {
        {},
        {
                {"GetInventory", (int (IAClient::*)(lua_State *))&IAClient::GetInventory},
                {"GetSightAt", (int (IAClient::*)(lua_State *))&IAClient::GetSightAt},
                {"SetParameter", (int (IAClient::*)(lua_State *))&IAClient::SetParameter},
		{"GetLevel", (int (IAClient::*)(lua_State *))&IAClient::GetLevel}
        }
};

IAClient::IAClient(const std::string &scriptname) :
    script(),
    inventory(&request),
    request(this),
    map(NULL),
    position(Vector2::Zero),
    orientation(Vector2::UP),
    sight(),
    reqParam(),
    dead(false),
    lvl(0),
    incanting(false),
    moved(false),
    missing(0)
{
    script.LoadFile(scriptname);
    script.SetGlobalValue(this, "IA");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::DEFAULT), "NONE");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::MOVE), "MOVE");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::RIGHT), "RIGHT");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::LEFT), "LEFT");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::TAKE), "TAKE");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::DROP), "DROP");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::EXPULSE), "EXPULSE");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::BROADCAST), "BROADCAST");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::INCANTATION), "INCANTATION");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::LAYEGG), "LAYEGG");
    script.SetGlobalValue(static_cast<int>(ZappyRequest::CONNECTNBR), "CONNECTNBR");
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
                    map = new ZappyMap(Vector2(atoi(answer.substr(0, i - 1).c_str()), atoi(answer.substr(i + 1, answer.length() - i).c_str())), &request);
                    script.Handler()->Select(IAClient::OnStart).Call();
                    return;
                }
            }
        }
    }
    throw SocketException("Unable to connect");
}

int IAClient::Update(void)
{
    reqParam = "";
    request.MakeRequest(static_cast<ZappyRequest::Request >(script.Handler()->Select(IAClient::OnUpdate).Call()), reqParam);
    try
    {
        request.Update();
    }
    catch (Socket::SocketException &exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}

void IAClient::Receive()
{
    script.Handler()->Select(IAClient::OnReceive).Call();
}

void IAClient::Die(void)
{
    dead = true;
    std::cout << "\e[31mPlayer die\e[0m" << std::endl;
}

bool IAClient::IsDead(void) const
{
    return dead;
}

void IAClient::Upgrade(const std::string &string)
{
    std::cout << "You have been upgraded: '" << string << "'" << std::endl;
    ++lvl;
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

void IAClient::RefreshMap(std::vector<std::vector<std::string> > const &data)
{
    map->Refresh(position, Vector2::Directions[orientation], data);
}

void IAClient::Moved(void)
{
    moved = true;
}

int IAClient::GetLevel(Lua::LuaScript const &script)
{
  script.PushVar(&lvl);
  return 1;
}

int IAClient::GetInventory(Lua::LuaScript const &script)
{
    script.PushVar(&inventory);
    return 1;
}

int IAClient::GetSightAt(Lua::LuaScript const &script)
{
    if (moved)
    {
        moved = false;
        sight = map->getIaSight(position, Vector2::Directions[orientation], lvl);
    }
    size_t index = static_cast<size_t >(script.GetInteger());

    if (index >= sight.size())
        return 0;
    script.PushVar(&sight[index]);
    return 1;
}

int IAClient::SetParameter(Lua::LuaScript const &script)
{
    reqParam = script.GetString();
    return 0;
}
