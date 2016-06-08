//
// Created by gaspar_q on 6/8/16.
//

#include "LuaScript.hpp"
#include "LuaHandler.hpp"
#include "IAClient.hpp"

class test
{
public:
    static const std::string className;
    static const Lua::LuaClass<test>::LuaPrototype  prototype;

public:
    test()
    {
        std::cout << "this: " << this << std::endl;
        toto = 2;
    }

public:
    int le_call(lua_State *state)
    {
        std::cout << "on call la méthode: " << toto << ", this: " << this << std::endl;
        return 1;
    }
    static int leBonCall(lua_State *state)
    {
        std::cout << "Appel du bon call" << std::endl;
        return 1;
    }

private:
    int toto;
};

const std::string test::className = "test";
const Lua::LuaClass<test>::LuaPrototype  prototype = {{{"bonCall", &test::leBonCall}}, {{"call", &test::le_call}}};

int main(int ac, char **av)
{
    IAClient    client;

    if (ac < 3)
    {
        std::cerr << "Probl arg" << std::endl;
        return 1;
    }
    client.Connect(av[1], atoi(av[2]));
    client << "Coucou";
    client.Update();
    client.Receive();
    return 0;
}