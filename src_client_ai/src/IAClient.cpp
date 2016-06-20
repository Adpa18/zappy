//
// Created by gaspar_q on 6/7/16.
//

#include "IAClient.hpp"
#include "LuaHandler.hpp"

const std::string    IAClient::Default   = "./lua/default.lua";
const std::string    IAClient::OnStart   = "OnStart";
const std::string    IAClient::OnUpdate  = "OnUpdate";
const std::string    IAClient::OnReceive = "OnReceive";

const std::string                              IAClient::className = typeid(IAClient).name();
const Lua::LuaClass<IAClient>::LuaPrototype    IAClient::prototype = {
        {},
        {
                {
                        "GetInventory", &IAClient::GetInventory
                },
                {
                        "GetSightAt", &IAClient::GetSightAt
                },
                {
                        "SetParameter", &IAClient::SetParameter
                },
                {
                        "GetLevel", &IAClient::GetLevel
                }
        }
};

IAClient::IAClient() :
        script(), inventory(&request), request(this), map(NULL), position(Vector2::Zero), orientation(Vector2::UP),
        sight(), reqParam(), dead(false), lvl(0), incanting(false), moved(true), missing(0)
{
}

IAClient::~IAClient()
{
    if (map)
        delete (map);
}

void IAClient::SetScript(const std::string &scriptname)
{
    std::cout << "Loading script: " << scriptname << std::endl;
    script.LoadFile(scriptname);
    script.RegisterClass<IAClient>();
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
    script.SetGlobalValue(static_cast<int>(Inventory::NONE), "NOOBJ");
    script.SetGlobalValue(static_cast<int>(Inventory::FOOD), "FOOD");
    script.SetGlobalValue(static_cast<int>(Inventory::LINEMATE), "LINEMATE");
    script.SetGlobalValue(static_cast<int>(Inventory::DERAUMERE), "DERAUMERE");
    script.SetGlobalValue(static_cast<int>(Inventory::SIBUR), "SIBUR");
    script.SetGlobalValue(static_cast<int>(Inventory::MENDIANE), "MENDIANE");
    script.SetGlobalValue(static_cast<int>(Inventory::PHIRAS), "PHIRAS");
    script.SetGlobalValue(static_cast<int>(Inventory::THYSTAME), "THYSTAME");
}

void IAClient::Connect(const std::string &ip, const uint16_t port, std::string const &teamName)
{
    std::string answer;

    this->teamName = teamName;
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
                    map = new ZappyMap(Vector2(atoi(answer.substr(0, i - 1).c_str()),
                                               atoi(answer.substr(i + 1, answer.length() - i).c_str())), &request);
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
    request.MakeRequest(static_cast<ZappyRequest::Request >(script.Handler()->Select(IAClient::OnUpdate).Call()),
                        reqParam);
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

void IAClient::Receive(ZappyRequest::Request received, std::string const &answer)
{
    script.Handler()->Select(IAClient::OnReceive).Call(static_cast<int>(received), answer.c_str());
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
    orientation     = static_cast<Vector2::DIR >(orientation - 1);
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

int IAClient::GetLevel(lua_State *state)
{
    Lua::LuaScript(state).PushVar(lvl);
    return 1;
}

int IAClient::GetInventory(lua_State *state)
{
    Lua::LuaScript(state).PushVar(&inventory);
    return 1;
}

int IAClient::GetSightAt(lua_State *state)
{
    if (moved)
    {
        std::cout << "getIaSight" << std::endl;
        moved = false;
        sight = map->getIaSight(position, Vector2::Directions[orientation], lvl);
    }
    size_t index = static_cast<size_t >(script.GetInteger());

    if (index >= sight.size())
        return 0;
    Lua::LuaScript(state).PushVar(&sight[index]);
    return 1;
}

int IAClient::GetTeamName(lua_State *state)
{
    Lua::LuaScript(state).PushVar(teamName.c_str());
    return 1;
}

int IAClient::SetParameter(lua_State *state)
{
    reqParam = Lua::LuaScript(state).GetString();
    return 0;
}

void IAClient::ReceiveMessage(const std::string &message)
{
    std::cout << "Receive broadcast: " << message << std::endl;
    Receive(ZappyRequest::BROADCAST, message);
}
