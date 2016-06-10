//
// Created by gaspar_q on 5/6/16.
//

#ifndef CPP_INDIE_STUDIO_LUAHANDLER_HPP
#define CPP_INDIE_STUDIO_LUAHANDLER_HPP

# include <string>
# include <stdexcept>
# include <iostream>
# include "LuaScript.hpp"

namespace Lua
{
    /**
     * \brief LuaHandler that allow the user use functions of a Lua script in C++
     */
    class LuaHandler
    {
    public:
        /**
         * \brief The constructor of the handler with a state
         * \param state The lua state to use
         * \param script The script name to use
         * \param methodName The Method to call
         */
        LuaHandler(LuaScript &state, std::string const &script = "", std::string const &methodName = "") :
                state(state),
                script(),
                toCall(methodName)
        {
            setScript(script);
        }
        /**
         * \brief Copy constructor
         */
        LuaHandler(LuaHandler const &ref) :
                state(ref.state)
        {
            *this = ref;
        }
        /**
         * \brief Copy operator. Will copy the state, the method to call and the script to execute
         * \param ref The reference to copy
         * \return A Reference on this
         */
        LuaHandler  &operator=(LuaHandler const &ref)
        {
            state = ref.state;
            toCall = ref.toCall;
            setScript(ref.script);
            return (*this);
        }
        /**
         * \brief Handler destructor, if you have any idea, call me
         */
        ~LuaHandler()
        {

        }

    public:
        /**
         * \brief Select a method name
         * \param methodName The function you want to select
         * \return A reference on this pointer
         */
        LuaHandler  &Select(const std::string &methodName)
        {
            toCall = methodName;
            return *this;
        }
        /**
         * \brief Access operator that will allow you to choose a method to call
         * \param methodname The function name you choose to select
         * \return A reference on this pointer
         */
        LuaHandler  &operator[](const std::string &methodname)
        {
            return (Select(methodname));
        }
        /**
         * \brief Call the selected function
         */
        template <typename returnType = int, typename ... Types>
        returnType  Call(Types ... args)
        {
            return operator()(args...);
        }
        /**
         * \brief Template method for calling the handler choosen function
         * \param args The arguments needed by the method
         * \return An integer corresponding to the lua function return (TODO add more polymorphism)
         */
        template <typename ... Types>
        int     operator()(Types ... args)
        {
            int result;
            lua_getglobal(*state, toCall.c_str());
            int dum[sizeof...(Types)] = { (state.PushVar(args))... };

            (void)dum;
            lua_call(*state, sizeof...(Types), 1);
            result = lua_tointeger(*state, -1);
            lua_pop(*state, 1);
            return result;
        }
        /**
         * \brief Set and execute the script represented by scriptname
         * \param scriptname The name of the script to execute
         */
        void setScript(std::string const &scriptname)
        {
            if (!scriptname.empty())
                luaL_dofile(*state, scriptname.c_str());
            script = scriptname;
        }
        /**
         * \brief A simple getter on the lua state used by the handler
         * \return The lua state used
         */
        lua_State   *getState(void)
        {
            return *state;
        }

    private:
        LuaScript   &state;
        std::string script;
        std::string toCall;
    };
}

#endif //CPP_INDIE_STUDIO_LUAHANDLER_HPP
