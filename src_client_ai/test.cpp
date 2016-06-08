//
// Created by gaspar_q on 6/8/16.
//

//#include "LuaScript.hpp"
//#include "LuaHandler.hpp"
//#include "IAClient.hpp"
#include <thread>
#include "ActionHandler.hpp"

class test
{
public:
//    static constexpr std::string className = std::forward<const char *>(typeid(test).name());
//    static const Lua::LuaClass<test>::LuaPrototype  prototype;

public:
    test()
    {
        std::cout << "this: " << this << std::endl;
        toto = 2;
    }

public:
    int le_call(int i, int j, std::string const &coucou)
    {
        std::cout << "i: " << i << ", j: " << j << ", coucou: " << coucou << std::endl;
//        std::cout  << "le call state: " << state << std::endl;
//        std::cout << "on call la méthode: " << toto << ", this: " << this << std::endl;
        return 1;
    }
    static int leBonCall(void *state)
    {
        std::cout << "Appel du bon call" << std::endl;
        return 1;
    }

private:
    int toto;
};

//template <typename test2>
//class coucou
//{
//public:
//    static constexpr std::string className = std::forward<const char *>(typeid(test2).name());

//public:
//    coucou()
//    {
//        std::cout << className << std::endl;
//    }
//};

//const std::string test::className = "test";
//const Lua::LuaClass<test>::LuaPrototype  prototype = {{{"bonCall", &test::leBonCall}}, {{"call", &test::le_call}}};

int main(int ac, char **av)
{
//    IAClient    client;
    test        toto;
    ActionHandler<test, int>   handler(toto);
    std::function<int()>      function;
//    coucou<test>    test2;

//    if (ac < 3)
//    {
//        std::cerr << "Probl arg" << std::endl;
//        return 1;
//    }
//    client.Connect(av[1], atoi(av[2]));
//    client << "Coucou";
//    client.Update();
//    client.Receive();
    handler << &test::le_call;
    function = handler.toFunction(4, -5, std::string("Des barres"));
    std::cout << "retour de fonction: " << function() << std::endl;
    return 0;
}