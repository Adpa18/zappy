//
// Created by gaspar_q on 5/14/16.
//

#ifndef CPP_INDIE_STUDIO_LUACLASS_HPP
#define CPP_INDIE_STUDIO_LUACLASS_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <string.h>

extern "C" {
#include "lua-5.3.2/src/lua.h"
#include "lua-5.3.2/src/lualib.h"
#include "lua-5.3.2/src/lauxlib.h"
}

namespace Lua
{
    /**
     * \brief constants for internal Lua usage
     */
    static const std::string luaPrefix = "luaL_";

    /**
     * \brief Template class that overload a class to be a Lua usable class
     * \param classType the type of the class to overload
     */
    template <typename classType>
    class LuaClass
    {
    public:
        /**
         * \brief The principal constructor of a lua class that bind the metatable to the object
         * \param thisptr A pointer on the object to overload
         * \param todelete Tell if the object will be delete on ~LuaClass() call
         */
        LuaClass(lua_State *state, classType *thisptr) :
                userData(NULL),
                thisptr(thisptr),
                todelete(false),
                state(state)
        {
            userData = static_cast<classType **>(lua_newuserdata(state, sizeof(*userData)));
            bindMetatable();
            *userData = thisptr;
        }
        /**
         * \brief An other constructor that will be used like the constructor of the object
         * \param todelete Tells if the object will be delete on ~LuaClass() call
         * \param args The arguments of the constructor of the new object
         */
        template <typename ... Types>
        LuaClass(lua_State *state, Types ... args) :
                LuaClass(state, new classType(args...))
        {
        }
        /**
         * \brief A default constructor like
         * \param todelete Tells if the object will be delete on ~LuaClass() call
         */
        LuaClass(lua_State *state) :
                LuaClass(state, new classType())
        {
        }
        /**
         * \brief A Copy constructor implementation
         * \param ref The object to copy
         */
        LuaClass(lua_State *state, classType const &ref) :
            LuaClass(state, new classType(ref))
        {
        }
        /**
         * \brief The lua class copy constructor
         * \param ref A reference on the object to copy
         */
        LuaClass(LuaClass<classType> const &ref) :
                LuaClass(ref.state, ref.thisptr)
        {
            dontDelete();
        }
        /**
         * \brief The copy operator of a lua class
         * \param ref A reference on the object to copy
         * \return A reference on this pointer
         */
        LuaClass    &operator=(LuaClass<classType> const &ref)
        {
            thisptr = ref.thisptr;
            *userData = thisptr;
            dontDelete();
            return (*this);
        }
        /**
         * \brief overload of referencing operator to get the adress of the real object
         * \return The adress of the real object
         */
        classType   **getUserData()
        {
            return (userData);
        }
        /**
         * \brief Destructor that will delete the object only if the todelete construcor argument have been set to true
         */
        ~LuaClass()
        {
            if (todelete)
                delete(thisptr);
        }
        /**
         * \brief Tells to the class to not detele the object on destruction
         */
        void dontDelete(void)
        {
            todelete = false;
        }
        /**
         * \brief Bind a metatable to the user data
         */
        void bindMetatable(void)
        {
            luaL_getmetatable(state, (luaPrefix + classType::className).c_str());
            lua_setmetatable(state, -2);
        }
        /**
         * \brief Access the reference of the overloaded pointer
         * \return A reference on internal pointer
         */
        classType   &operator*(void)
        {
            return (*thisptr);
        }
        /**
         * \brief Allow the user to access methods on internal pointer
         * \return The internal pointer
         */
        classType   *operator->(void)
        {
            return (thisptr);
        }

    public:
        /**
         * \brief Nested class that will define the metatable of the LuaClass inside Lua
         */
        class LuaPrototype
        {
        private:
            typedef int (classType::*classMethods)(lua_State *);

        public:
            /**
             * \brief Contructor with brackets
             * \param sSyms Static symbols
             * \param sMeth Class methods
             */
            LuaPrototype(std::map<std::string, lua_CFunction> const &sSyms = {}, std::map<std::string, classMethods> const &sMeth = {}) :
                    symbols{sSyms},
                    methods{sMeth}
            {

            }

        public:
            /**
             * \brief Getter of prototype symbols
             * \return The table of methods of the prototypes
             */
            const std::map<std::string, lua_CFunction>  &getSymbols(void) const
            {
                return (symbols);
            }
            /**
             * \brief Convert the map into a luaL_Reg array needed by luaL_setfuncs
             * \return A unique ptr (for garbage collection) of luaL_Reg[] that can be used for metatable registration
             */
            std::unique_ptr<luaL_Reg[]>    getRegs(void) const
            {
                luaL_Reg    *regs;
                size_t      i = 0;

                regs = new luaL_Reg[symbols.size() + 1];
                for (std::map<std::string, lua_CFunction>::const_iterator it = symbols.begin(), end = symbols.end(); it != end; ++it, ++i)
                {
                    regs[i].func = it->second;
                    regs[i].name = it->first.c_str();
                }
                regs[i].name = NULL, regs[i].func = NULL;
                return (std::unique_ptr<luaL_Reg[]>(regs));
            }
            /**
             * \brief The access operator for assiging a new function to the prototype
             * \param name The name that will bind the function you will assign
             * \return A reference on the function binded by name
             */
            lua_CFunction &operator[](const std::string &name)
            {
                return (symbols[name]);
            }
            /**
             * \brief A simple getter ultra-const to get the function binded by name
             * \param name The name of the function to get
             * \return The function binded by name
             */
            lua_CFunction const &operator[](const std::string &name) const
            {
                return (symbols.find(name)->second);
            }

            /**
             * \brief Will register the prototype into a lua metatable, it will allow you to use the LuaClass into lua script
             */
            void Register(lua_State *state) const
            {
                lua_newtable(state);
                int meth = lua_gettop(state);

                luaL_newmetatable(state, (luaPrefix + classType::className).c_str());
                int metatable = lua_gettop(state);

                lua_pushvalue(state, meth);
                Set(state, -1, classType::className);

                lua_pushvalue(state, meth);
                Set(state, metatable, "__metatable");

                lua_pushvalue(state, meth);
                Set(state, metatable, "__index");

                lua_newtable(state);
                lua_setmetatable(state, meth);

                luaL_setfuncs(state, &getRegs()[0], 1);
                for (typename std::map<std::string, classMethods>::const_iterator it = methods.begin(), end = methods.end(); it != end; ++it)
                {
                    lua_pushstring(state, it->first.c_str());
                    lua_pushlightuserdata(state, (void *)&it->second);
                    lua_pushcclosure(state, Call, 1);
                    lua_settable(state, meth);
                }
                lua_pop(state, 2);
            }

        private:
            /**
             * \brief Static function for calling methods of the class
             * \param state The lua state called
             * \return An index in the lua stack
             */
            static int Call(lua_State *state)
            {
                classType *obj = getThis(state);
                lua_remove(state, 1);
                classMethods method = *static_cast<classMethods *>(lua_touserdata(state, lua_upvalueindex(1)));
                return (obj->*method)(state);
            }
            /**
             * \brief Insert a new table with the name key at tableIndex in state
             * \param state The lua state used
             * \param tableIndex The index in the lua stack
             * \param key The key of the table to push
             */
            void Set(lua_State *state, int tableIndex, std::string const &key) const
            {
                lua_pushstring(state, key.c_str());
                lua_insert(state, -2);
                lua_settable(state, tableIndex);
            }

        private:
            std::map<std::string, lua_CFunction>    symbols;
            std::map<std::string, classMethods>     methods;
        };
        /**
         * \brief Allows you to get the 'this' pointer when a method is called
         * \param n The correspond to the index of the object to get in the lua stack (1 if you are nice)
         * \return The this arguments if you call it in very first inside the method
         */
        static classType *getThis(lua_State *state, int n = 1)
        {
            return *(classType **)luaL_checkudata(state, n, (luaPrefix + classType::className).c_str());
        }
        /**
         * \brief An implementation of the most basic constructor for a lua class
         * \return The index of the new instance in the lua stack
         */
        static int defaultConstructor(lua_State *state)
        {
            Lua::LuaClass<classType>   thisptr(state);

            thisptr.dontDelete();
            return (1);
        }
        /**
         * \brief An implementation of the most basic destructor for a lua class
         */
        static int defaultDestructor(lua_State *state)
        {
            classType   *thisptr = getThis(state);

            delete(thisptr);
            return (1);
        }
        /**
         * \brief An implementation of a null destructor for classes you don't want to delete but for garbage collection
         */
        static int destrucNull(lua_State *)
        {
            return (1);
        }

    private:
        classType   **userData;
        classType   *thisptr;
        bool        todelete;

    protected:
        lua_State   *state;
    };
};

#endif //CPP_INDIE_STUDIO_LUACLASS_HPP
