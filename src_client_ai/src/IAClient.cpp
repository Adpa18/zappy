//
// Created by gaspar_q on 6/7/16.
//

#include <Recipee.hpp>
#include "IAClient.hpp"
#include "LuaHandler.hpp"

const std::string    IAClient::Default   = "./src_client_ai/lua/default.lua";
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
                        "GetFullSight", &IAClient::GetFullSight
                },
                {
                        "SetParameter", &IAClient::SetParameter
                },
                {
                        "GetLevel", &IAClient::GetLevel
                },
                {
                        "CanElevate", &IAClient::CanElevate
                },
                {
                        "NeedRessources", &IAClient::NeedRessources
                },
                {
                        "ElevationPercentage", &IAClient::ElevationPercentage
                },
                {
                        "GetNbNeededPlayers", &IAClient::GetNbNeededPlayers
                },
                {
                        "GetTeamName", &IAClient::GetTeamName
                },
                {
                        "GetNbNeededPlayers", &IAClient::GetNbNeededPlayers
                },
                {
                        "GetNbNeededRessources", &IAClient::GetNbNeededRessources
                },
                {
                        "GetEnoughRessources", &IAClient::GetEnoughRessources
                },
                {
                        "IsIncanting", &IAClient::IsIncanting
                },
                {
                        "IsSaturated", &IAClient::IsSaturated
                },
                {
                        "IsPossibleToElevate", &IAClient::IsPossibleToElevate
                }
        }
};

IAClient::IAClient() :
        script(), request(this), inventory(&request), map(NULL), position(Vector2::Zero), orientation(Vector2::UP),
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
    script.LoadFile(scriptname);
    script.RegisterLuaClass<IAClient>();
    script.RegisterLuaClass<Inventory>();
    script.RegisterLuaClass<ObjectArray>();
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
    script.SetGlobalValue(0, "PLAYER");
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
                    map = new ZappyMap(Vector2(atoi(answer.substr(0, i).c_str()),
                                               atoi(answer.substr(i + 1, answer.length() - i).c_str())), &request);
                    script.SetGlobalValue(map->Dimmensions().x, "MAPW");
                    script.SetGlobalValue(map->Dimmensions().y, "MAPH");
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
    try
    {
        request.Update();
    }
    catch (Socket::SocketException &exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    if (map->IsUpdated() && !IsDead())
    {
        reqParam = "";
        request.MakeRequest(static_cast<ZappyRequest::Request >(script.Handler()->Select(IAClient::OnUpdate).Call()),
                            reqParam);
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
    Receive(ZappyRequest::INCANTATION, string);
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
    RefreshSight(false);
}

void IAClient::Moved(void)
{
    position += Vector2::Directions[orientation];
    position.limit(Vector2::Zero, map->Dimmensions());
    moved = true;
}

int IAClient::GetLevel(lua_State *state)
{
    Lua::LuaScript(state).PushVar(lvl + 1);
    return 1;
}

int IAClient::GetInventory(lua_State *state)
{
    Lua::LuaScript(state).PushVar(&inventory);
    return 1;
}

int IAClient::GetSightAt(lua_State *state)
{
    if (moved || request.IsTimerFinished(ZappyRequest::SEE))
    {
        moved = false;
        RefreshSight();
    }
    size_t index = static_cast<size_t >(script.GetInteger());

    if (index >= sight.size())
        return 0;
    Lua::LuaScript(state).PushVar(&sight[index]);
    return 1;
}

int IAClient::GetFullSight(lua_State *state)
{
    Lua::LuaScript  script(state);
    ObjectArray     fullSight;

    if (moved || request.IsTimerFinished(ZappyRequest::SEE))
    {
        moved = false;
        RefreshSight();
    }
    for (ObjectArray const &curr : sight)
    {
        fullSight += curr;
    }
    script.PushVar(fullSight);
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
    Receive(ZappyRequest::BROADCAST, message);
}

ZappyMap &IAClient::Map()
{
    return *map;
}

Vector2 const &IAClient::Pos(void) const
{
    return position;
}

ZappyRequest &IAClient::Request(void)
{
    return request;
}

void IAClient::TakeObj(Inventory::Object obj)
{
    inventory.Add(obj);
    map->TakeObjAt(position, obj);
    RefreshSight(false);
}

void IAClient::DropObj(Inventory::Object obj)
{
    inventory.Remove(obj);
    map->DropObjAt(position, obj);
    RefreshSight(false);
}

void IAClient::RefreshSight(bool canUpdate)
{
    sight = map->getIaSight(position, Vector2::Directions[orientation], lvl, canUpdate);
}

int IAClient::CanElevate(lua_State *script)
{
    Lua::LuaScript(script).PushVar(Recipee::recipeesPerLevel[lvl].CanBeMade(inventory));
    return 1;
}

int IAClient::GetEnoughRessources(lua_State *script)
{
    if (sight.size() == 0)
        return 0;
    Lua::LuaScript(script).PushVar(Recipee::recipeesPerLevel[lvl].CanBeMade(inventory + sight[0]));
    return 1;
}

int IAClient::NeedRessources(lua_State *state)
{
    Lua::LuaScript  script(state);
    Inventory::Object obj = static_cast<Inventory::Object >(script.GetInteger());

    script.PushVar(Recipee::recipeesPerLevel[lvl].NeedRessource(obj));
    return 1;
}

int IAClient::ElevationPercentage(lua_State *script)
{
    Lua::LuaScript(script).PushVar(Recipee::recipeesPerLevel[lvl].GetMissingPercentage(inventory));
    return 1;
}

int IAClient::GetNbNeededPlayers(lua_State *state)
{
    Lua::LuaScript  script(state);

    script.PushVar(Recipee::GetNbOfNeededPlayers(lvl + 1));
    return 1;
}

int IAClient::GetNbNeededRessources(lua_State *state)
{
    int obj;
    Lua::LuaScript  script(state);

    obj = script.GetInteger();
    script.PushVar(static_cast<int>(Recipee::recipeesPerLevel[lvl][static_cast<Inventory::Object>(obj)]));
    return 1;
}

int IAClient::CanMakeElevation(lua_State *)
{
//    if (Recipee::recipeesPerLevel[lvl].CanBeMade(sight[0]) &&
//        sight[0])
//        Lua::LuaScript(state).PushVar(true);
//    else
//        Lua::LuaScript(state).PushVar(false);
    return 1;
}

int IAClient::IsIncanting(lua_State *state)
{
    Lua::LuaScript(state).PushVar(incanting);
    return 1;
}

void IAClient::IncantationFailure(std::string const &answer)
{
    Receive(ZappyRequest::INCANTATION, answer);
    incanting = false;
}

void IAClient::PushedTo(const std::string &answer)
{
    size_t i = answer.find(": ");

    if (i != std::string::npos)
    {
        std::string nb = answer.substr(i + 2, answer.size() - i - 2);

        if (nb.size() > 0)
        {
            int ori = atoi(nb.c_str());

            if (ori >= 1 && ori <= 4)
            {
                position += Vector2::Directions[ori - 1];
                position.limit(Vector2::Zero, map->Dimmensions());
                moved = true;
                Receive(ZappyRequest::EXPULSE, answer);
                std::cout << "\e[32mPushed\e[0m" << std::endl;
            }
        }
    }
}

int IAClient::IsSaturated(lua_State *state)
{
    Lua::LuaScript(state).PushVar(request.IsSaturated());
    return 1;
}

int IAClient::IsPossibleToElevate(lua_State *state)
{
    Lua::LuaScript  script(state);

    if (sight.size() > 0 && Recipee::recipeesPerLevel[lvl].CanBeMade(sight[0]) && sight[0].GetNbOf(Inventory::NONE) == Recipee::GetNbOfNeededPlayers(lvl + 1))
        script.PushVar(true);
    else
        script.PushVar(false);
    return 1;
}