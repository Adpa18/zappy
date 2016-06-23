//
// Created by gaspar_q on 6/4/16.
//

#include "LuaScript.hpp"
#include "LuaHandler.hpp"

std::vector<std::function<void(void)> > Lua::LuaScript::garbage;

Lua::LuaScript::LuaScript(lua_State *state) :
    state(state),
    handler(new LuaHandler(*this)),
    close(false)
{
    if (state == NULL)
    {
        close = true;
        this->state = luaL_newstate();
        luaL_openlibs(this->state);
    }
}

Lua::LuaScript::LuaScript(const Lua::LuaScript &script) :
    LuaScript(script.state)
{
    *this = script;
}

Lua::LuaScript::~LuaScript()
{
    if (close)
        lua_close(state);
    delete(handler);
}

Lua::LuaScript &Lua::LuaScript::operator=(const Lua::LuaScript &script)
{
    state = script.state;
    registeredClasses = script.registeredClasses;
    *handler = *script.handler;
    close = false;
    return *this;
}

lua_State *Lua::LuaScript::operator*(void)
{
    return state;
}

int Lua::LuaScript::GetInteger(int rank) const
{
    return luaL_checkinteger(state, rank);
}

/**
 * \brief Polymorphism on no argument
 */
int Lua::LuaScript::PushVar(void) const
{
    return 0;
}

/**
 * \brief Polymorphism on integer argument
 * \param topush The argument to push
 */
int Lua::LuaScript::PushVar(int topush) const
{
    lua_pushinteger(state, static_cast<lua_Integer >(topush));
    return 0;
}

/**
 * \brief Polymorphism on double argument
 * \param topush The argument to push
 */
int Lua::LuaScript::PushVar(double topush) const
{
    lua_pushnumber(state, topush);
    return 0;
}

/**
 * \brief Polymorphism on boolean argument
 * \param topush The argument to push
 */
int Lua::LuaScript::PushVar(bool topush) const
{
    lua_pushboolean(state, topush);
    return 0;
};

/**
 * \brief Polymorphism on string argument
 * \param topush The argument to push
 */
int Lua::LuaScript::PushVar(const char *topush) const
{
    lua_pushstring(state, topush);
    return 0;
}

void Lua::LuaScript::LoadFile(const std::string &filename) const
{
    luaL_dofile(state, filename.c_str());
}

void Lua::LuaScript::LoadFiles(std::vector<std::string> const &filesname) const
{
    for (std::vector<std::string>::const_iterator it = filesname.begin(), end = filesname.end(); it != end; ++it)
    {
        LoadFile(*it);
    }
}

std::string Lua::LuaScript::GetString(int rank) const
{
    return luaL_checkstring(state, rank);
}

void Lua::LuaScript::freeGarbage(void)
{
    for (std::function<void(void)> &curr : garbage)
    {
        curr();
    }
}