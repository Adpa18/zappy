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

/**
 * TODO: Sight => ZappyMap
 */
class IAClient : public Client
{
public:
    static const std::string                                Default;
    static const std::string                                OnStart;
    static const std::string                                OnUpdate;
    static const std::string                                OnReceive;

    static const std::string                                className;
    static const Lua::LuaClass<IAClient>::LuaPrototype      prototype;

public:
    explicit IAClient(std::string const &scriptname = Default);
    virtual ~IAClient();
    IAClient(IAClient const &ref) = delete;
    IAClient    &operator=(IAClient const &ref) = delete;

public:
    void Die(void);
    bool IsDead(void) const;
    void Upgrade(const std::string &);
    bool IsIncanting(void) const;
    void Incant(void);
    void setMissingPeople(size_t miss);
    size_t getMissingPeople(void) const;
    void See(std::vector<std::vector<std::string>> const &vision);
    void TurnRight(void);
    void TurnLeft(void);

public:
    virtual void Connect(const std::string &ip, const uint16_t port, std::string const &teamName);
    void Update(void);
    void Receive(void);
    Inventory   &Bag(void);

private:
    Lua::LuaScript      script;
    Inventory           inventory;
    ZappyMap            *map;
    Vector2             position;
    Vector2::DIR        orientation;
    bool                dead;
    int                 lvl;
    bool                incanting;
    size_t              missing;
};

#endif //PSU_2015_ZAPPY_IACLIENT_HPP
