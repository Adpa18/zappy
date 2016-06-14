//
// Created by gaspar_q on 6/14/16.
//

#include "ObjectArray.hpp"

const std::string                                ObjectArray::className = typeid(ObjectArray).name();
const Lua::LuaClass<ObjectArray>::LuaPrototype      ObjectArray::prototype = {
        {},
        {
                {"HasObject", (int (ObjectArray::*)(lua_State *))&ObjectArray::HasObject},
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

int ObjectArray::HasObject(Lua::LuaScript const &script)
{
    Inventory::Object toCheck = static_cast<Inventory::Object >(script.GetInteger());
    bool has = false;

    for (Inventory::Object &curr : *this)
    {
        if (toCheck == curr)
            has = true;
    }
    script.PushVar(has);
    return 1;
}