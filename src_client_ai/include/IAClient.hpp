//
// Created by gaspar_q on 6/7/16.
//

#ifndef PSU_2015_ZAPPY_IACLIENT_HPP
#define PSU_2015_ZAPPY_IACLIENT_HPP

#include "Client.hpp"
#include "LuaScript.hpp"

/**
 * TODO:
 *  -   Tells if IA died
 *  -   Store:
 *          -   Sight
 *          -   Inventory
 *          -   Life
 */
class IAClient : public Client
{
public:
    struct Vector2
    {
    public:
        Vector2 &operator=(Vector2 const &ref)
        {
            x = ref.x;
            y = ref.y;
            return *this;
        }
        int x, y;
    };

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
    virtual void Connect(const std::string &ip, const uint16_t port, std::string const &teamName);
    void Update(void);
    void Receive(void);
    int callTest(std::string const &answer);

public:
    Vector2 const &getMapDimmensions(void) const;

private:
    Lua::LuaScript      script;
    Vector2             mapDimensions;
};

#endif //PSU_2015_ZAPPY_IACLIENT_HPP
