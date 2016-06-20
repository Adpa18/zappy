//
// Created by gaspar_q on 6/7/16.
//

#ifndef PSU_2015_ZAPPY_IACLIENT_HPP
#define PSU_2015_ZAPPY_IACLIENT_HPP

#include "Client.hpp"
#include "LuaScript.hpp"
#include "Inventory.hpp"
#include "Vector2.hpp"
#include "ZappyMap.hpp"
#include "ZappyRequest.hpp"

/**
 * TODO: Sight => ZappyMap
 * TODO: Méthodes de l'ia client pour le lua
 */
class IAClient : public Client
{
public:
    static const std::string Default;
    static const std::string OnStart;
    static const std::string OnUpdate;
    static const std::string OnReceive;

    static const std::string                           className;
    static const Lua::LuaClass<IAClient>::LuaPrototype prototype;

public:
    explicit IAClient();

    virtual ~IAClient();

    IAClient(IAClient const &ref) = delete;

    IAClient &operator=(IAClient const &ref) = delete;

public:
    void   Die(void);

    bool   IsDead(void) const;

    void   Upgrade(const std::string &);

    void   ReceiveMessage(const std::string &);

    bool   IsIncanting(void) const;

    void   Incant(void);

    void   Moved(void);

    void   setMissingPeople(size_t miss);

    size_t getMissingPeople(void) const;

    void   See(std::vector<std::vector<std::string>> const &vision);

    void   TurnRight(void);

    void   TurnLeft(void);

    void   TakeObj(Inventory::Object obj);

    void   DropObj(Inventory::Object obj);

    void   SetScript(const std::string &script);

public:
    int GetInventory(lua_State *script);

    int GetSightAt(lua_State *script);

    int GetTeamName(lua_State *script);

    int SetParameter(lua_State *script);

    int GetLevel(lua_State *script);

public:
    virtual void  Connect(const std::string &ip, const uint16_t port, std::string const &teamName);

    int           Update(void);

    void          Receive(ZappyRequest::Request received, std::string const &answer);

    Inventory     &Bag(void);

    ZappyMap      &Map(void);

    Vector2 const &Pos(void) const;

    ZappyRequest    &Request(void);

    void          RefreshMap(std::vector<std::vector<std::string> > const &data);

    void        RefreshSight(bool canUpdate = true);

private:
    Lua::LuaScript           script;
    ZappyRequest             request;
    Inventory                inventory;
    ZappyMap                 *map;
    Vector2                  position;
    Vector2::DIR             orientation;
    std::vector<ObjectArray> sight;
    std::string              reqParam;
    bool                     dead;
    int                      lvl;
    bool                     incanting;
    bool                     moved;
    size_t                   missing;
    std::string              teamName;
};

#endif //PSU_2015_ZAPPY_IACLIENT_HPP
