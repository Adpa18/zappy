//
// Created by gaspar_q on 6/4/16.
//

#ifndef CPP_INDIE_STUDIO_LUASCRIPT_HPP
# define CPP_INDIE_STUDIO_LUASCRIPT_HPP

# include <vector>
# include "LuaClass.hpp"

namespace Lua
{
    /**
     * \brief LuaException for lua handler errors
     */
    class LuaException : std::runtime_error
    {
    public:
        LuaException(std::string const &err) :
                std::runtime_error(err)
        {
        }
        virtual ~LuaException() throw()
        {

        }
    };

    class LuaHandler;

    class LuaScript
    {
    public:
        LuaScript(lua_State *state = NULL);
        LuaScript(LuaScript const &);
        ~LuaScript();
        LuaScript   &operator=(LuaScript const &);

    public:
        template <typename toRegister>
        void RegisterClass(typename Lua::LuaClass<toRegister>::LuaPrototype const &proto)
        {
            proto.Register(state);
            registeredClasses.push_back(toRegister::className);
        }
        template <typename toInstantiate>
        toInstantiate *New(void) const
        {
            return (*Lua::LuaClass<toInstantiate>(state));
        }
        template <typename toCheck>
        bool     IsRegistered(void) const
        {
            return (std::find(registeredClasses.begin(), registeredClasses.end(), toCheck::className) != registeredClasses.end());
        }
        template <typename toGet>
        toGet *GetObject(int rank = 1) const
        {
            return Lua::LuaClass<toGet>::getThis(state, rank);
        }
        int GetInteger(int rank = 1) const;

    public:
        int          PushVar(void) const;
        int          PushVar(int topush) const;
        int          PushVar(double topush) const;
        int          PushVar(bool topush) const;
        int          PushVar(const char *topush) const;

        /**
         * \brief Polymorphism on user data argument. In that case it is recommended to use LuaClass object '&' operator
         * \param topush The argument to push
         */
        template<typename classtype>
        int          PushVar(classtype *topush) const
        {
            LuaClass<classtype> luaconv(state, topush);

            luaconv.dontDelete();
            return 0;
        }

        template<typename classtype>
        int          PushVar(classtype topush) const
        {
            LuaClass<classtype> luaconv(state, topush);

            luaconv.dontDelete();
            return 0;
        }

        template <typename topushtype>
        void        SetGlobalValue(topushtype topush, const std::string &varname)
        {
            PushVar(topush);
            lua_setglobal(state, varname.c_str());
        }

        void        LoadFile(std::string const &filename) const;
        void        LoadFiles(std::vector<std::string> const &filesname) const;

        LuaHandler  *Handler(void)
        {
            return handler;
        }

    public:
        lua_State   *operator*(void);

    private:
        lua_State                   *state;
        LuaHandler                  *handler;
        bool                        close;
        std::vector<std::string>    registeredClasses;
    };
};

#endif //CPP_INDIE_STUDIO_LUASCRIPT_HPP
