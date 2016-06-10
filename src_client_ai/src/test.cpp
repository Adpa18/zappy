//
// Created by gaspar_q on 6/8/16.
//

//#include "LuaScript.hpp"
//#include "LuaHandler.hpp"
//#include "IAClient.hpp"
#include <thread>
#include "ActionHandler.hpp"
#include "IAClient.hpp"
#include "NetworkWatcher.hpp"

/*class test
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
        std::cout << "on call la méthode0: " << toto << ", this: " << this << std::endl;
        return 1;
    }
    int le_call1(int i, int j, std::string const &coucou)
    {
        std::cout << "i: " << i << ", j: " << j << ", coucou: " << coucou << std::endl;
//        std::cout  << "le call state: " << state << std::endl;
        std::cout << "on call la méthode1: " << toto << ", this: " << this << std::endl;
        return 1;
    }
    int le_call2(int i, int j, std::string const &coucou)
    {
        std::cout << "i: " << i << ", j: " << j << ", coucou: " << coucou << std::endl;
//        std::cout  << "le call state: " << state << std::endl;
        std::cout << "on call la méthode2: " << toto << ", this: " << this << std::endl;
        return 1;
    }
    int le_call3(*//*int i, int j, std::string const &coucou, *//*std::string const &hello)
    {
//        std::cout << "i: " << i << ", j: " << j << ", coucou: " << coucou << std::endl;
//        std::cout  << "le call state: " << state << std::endl;
        std::cout << "on call la méthode2: " << toto << ", this: " << this << std::endl;
        std::cout << "hello: '" << hello << "'" << std::endl;
        return 1;
    }
    static int leBonCall(void *state)
    {
        std::cout << "Appel du bon call" << std::endl;
        return 1;
    }

private:
    int toto;
};*/

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
//    test        toto;
//    ActionHandler<test, int>   handler(toto);
//    std::function<int(int, int, std::string)>      function1;
//    std::function<int(int, int, std::string)>      function2;
//    std::function<int()>      function3;
//    std::function<int(std::string const &)>        function4;
//    coucou<test>    test2;

//    client << "Coucou";
//    client.Update();
//    client.Receive();
//    handler << &test::le_call;
//    handler << &test::le_call1;
//    handler << &test::le_call2;
//    handler << &test::le_call3;
//    function1 = handler[0].toFunction<int, int, std::string>();
//    function2 = handler[1].toFunction<int, int, std::string>();
//    function3 = handler[2].toWrapedFunction(4, -5, std::string("coucou"));
//    function4 = handler[3].toFunction<std::string>();
//    std::cout << "retour de fonction0: " << function1(4, -5, std::string("Des barres")) << std::endl;
//    std::cout << "retour de fonction1: " << function2(4, -5, std::string("Des barres")) << std::endl;
//    std::cout << "retour de fonction2: " << function3() << std::endl;
//    std::cout << "retour de fonction3: " << function4(std::string("ca marche")) << std::endl;
    IAClient    client;
    NetworkWatcher  networkWatcher;
    std::string req;

    if (ac < 3)
    {
        std::cerr << "Probl arg" << std::endl;
        return 1;
    }
    try
    {
        client.Connect(av[1], static_cast<uint16_t >(atoi(av[2])));
    }
    catch (std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    while (1)
    {
        fd_set  set;
        struct timeval  time = {0, 0};

        FD_ZERO(&set);
        FD_SET(0, &set);
        if (select(1, &set, NULL, NULL, &time) > 0)
        {
            std::getline(std::cin, req);
            if (req.empty())
                break;
            if (req.find("nick") != std::string::npos)
                networkWatcher.RequestServer(req, ActionHandler<IAClient, int>::MethodToFunction<const std::string &>(client, &IAClient::callTest), client, 0);
            else if (req.find("user") != std::string::npos)
                networkWatcher.RequestServer(req, ActionHandler<IAClient, int>::MethodToFunction<const std::string &>(client, &IAClient::callTest), client, 28);
            else
                networkWatcher.RequestServer(req, ActionHandler<IAClient, int>::MethodToFunction<const std::string &>(client, &IAClient::callTest), client);
        }
        networkWatcher.Update(client);
    }
    return 0;
}