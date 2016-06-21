//
// Created by gaspar_q on 6/14/16.
//

#include "ObjectArray.hpp"

const std::string                                ObjectArray::className = typeid(ObjectArray).name();
const Lua::LuaClass<ObjectArray>::LuaPrototype      ObjectArray::prototype = {
        {
        },
        {
                {"HasObject", &ObjectArray::HasObject},
                {"GetNbOf", &ObjectArray::GetNbOf}
        }
};

ObjectArray::ObjectArray() :
        std::vector<Inventory::Object >()
{

}

ObjectArray::ObjectArray(ObjectArray const &ref) :
        std::vector<Inventory::Object >(ref)
{
    *this = ref;
}

ObjectArray &ObjectArray::operator=(ObjectArray const &ref)
{
    static_cast<std::vector<Inventory::Object > >(*this) = ref;
    return *this;
}

int ObjectArray::HasObject(lua_State *state)
{
    Inventory::Object toCheck = static_cast<Inventory::Object >(Lua::LuaScript(state).GetInteger());
    bool has = false;

    for (Inventory::Object &curr : *this)
    {
        if (toCheck == curr)
            has = true;
    }
    Lua::LuaScript(state).PushVar(has);
    return 1;
}

int ObjectArray::GetNbOf(lua_State *state)
{
    Inventory::Object toCheck = static_cast<Inventory::Object >(Lua::LuaScript(state).GetInteger());
    int nb = 0;

    for (Inventory::Object &curr : *this)
    {
        if (curr == toCheck)
            ++nb;
    }
    Lua::LuaScript(state).PushVar(nb);
    return 1;
}

ObjectArray &ObjectArray::operator+=(ObjectArray const &ref)
{
    for (Inventory::Object const &curr : ref)
    {
        push_back(curr);
    }
    return *this;
}


std::ostream    &operator<<(std::ostream &output, ObjectArray const &ref)
{
    size_t i = 0, max = ref.size();

    output << "{";
    for (Inventory::Object const &curr : ref)
    {
        try
        {
            output << Inventory::getNameFromObject(curr);
        }
        catch (std::logic_error &error)
        {
            output << curr;
        }
        ++i;
        if (i < max)
            output << ", ";
    }
    output << "}";
    return output;
}