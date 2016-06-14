//
// Created by gaspar_q on 6/14/16.
//

#ifndef PSU_2015_ZAPPY_OBJECTARRAY_HPP
#define PSU_2015_ZAPPY_OBJECTARRAY_HPP

#include <vector>
#include <Inventory.hpp>
#include <LuaScript.hpp>

class ObjectArray : public std::vector<Inventory::Object>
{
public:
    static const std::string                                className;
    static const Lua::LuaClass<ObjectArray>::LuaPrototype   prototype;

public:
    ObjectArray();
    ObjectArray(ObjectArray const &ref);
    ObjectArray &operator=(ObjectArray const &ref);

public:
    int HasObject(Lua::LuaScript const &script);
};

#endif //PSU_2015_ZAPPY_OBJECTARRAY_HPP
