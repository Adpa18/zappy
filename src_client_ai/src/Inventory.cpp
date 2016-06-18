//
// Created by gaspar_q on 6/11/16.
//

#include <climits>
#include <algorithm>
#include "Inventory.hpp"

const std::string    Inventory::className = typeid(Inventory).name();
const Lua::LuaClass<Inventory>::LuaPrototype Inventory::prototype = {
        {},
        {
                {"GetNbOf", (int (Inventory::*)(lua_State *))&Inventory::GetNbOf}
        }
};

/**
 * \brief A map that make corresponding an object and its name
 */
const std::map<Inventory::Object, std::string>  Inventory::objectsName = {
        {FOOD, "nourriture"},
        {LINEMATE, "linemate"},
        {DERAUMERE, "deraumere"},
        {SIBUR, "sibur"},
        {MENDIANE, "mendiane"},
        {PHIRAS, "phiras"},
        {THYSTAME, "thystame"},
};

/**
 * \brief Inventory constructor for the inventory initialisation
 * \param stuff The stuff to set to the inventory, by default it has 0 to each Object enumerated in class
 */
Inventory::Inventory(ZappyRequest *request, std::map<Object, size_t> const &stuff) :
  stuff(stuff), request(request)
{

}

/**
 * \brief Copy constructor the will copy the stuff
 * \param ref The object to copy
 */
Inventory::Inventory(Inventory const &ref) :
  Inventory(ref.request, ref.stuff)
{

}

/**
 * \brief Destructor that does nothing
 */
Inventory::~Inventory()
{

}

/**
 * \brief Copy operator for copying the stuff of an existing inventory
 * \param ref The object to copy
 * \return A reference on this pointer
 */
Inventory &Inventory::operator=(Inventory const &ref)
{
    stuff = ref.stuff;
    return *this;
}

/**
 * \brief Access operator for constant access to the capacity of an object
 * \param object The object type you want to get the capacity in the inventory
 * \return The capacity of 'object' in the inventory
 */
size_t Inventory::operator[](Inventory::Object object) const
{
    std::map<Object, size_t >::const_iterator   it = stuff.find(object);
    if (it == stuff.end())
        return 0;
    return it->second;
}

/**
 * \brief Access operator for 'object' capacity modification into the inventory
 * \param object The object type you want to access capacity
 * \return A reference on the capacity you want to access
 */
size_t &Inventory::operator[](Inventory::Object object)
{
    return stuff[object];
}

/**
 * \brief Will add an object inside the inventory
 * \param object The object you want to add in the inventory
 */
void Inventory::Add(Inventory::Object object)
{
    if (stuff[object] == ULONG_MAX)
        return;
    ++stuff[object];
}

/**
 * \brief Will remove an object inside the inventory
 * \param object The object you want to remove in the inventory
 */
void Inventory::Remove(Inventory::Object object)
{
    if (stuff[object] == 0)
        return;
    --stuff[object];
}

/**
 * \brief Getter for the stuff map inside the Inventory
 * \return The stuff object inside the inventory
 */
std::map<Inventory::Object, size_t> const &Inventory::getStuff(void) const
{
    if (request->CanMakeUnStackedRequest(ZappyRequest::STOCK))
        this->request->MakeRequest(ZappyRequest::STOCK);
    return stuff;
}

/**
 * \brief Will refresh the entire content of the inventory
 * \param content A vector of string vector in which there will be {{"nourriture", 4}, {... }
 */
void Inventory::Refresh(std::vector<std::vector<std::string> > const &content)
{
    std::map<Object, size_t >   save = stuff;

    Reset();
    try
    {
        for (std::vector<std::string> const &curr : content)
        {
            if (curr.size() != 2)
                throw std::runtime_error("Incorrect format");
            stuff[getObjectFromName(curr[0])] = strtoul(curr[1].c_str(), NULL, 10);
        }
    }
    catch (std::exception &exception)
    {
        stuff = save;
        throw(exception);
    }
}

/**
 * \brief Will reset the inventory stuff to 0 for each object in it
 */
void Inventory::Reset(void)
{
    std::for_each(stuff.begin(), stuff.end(), [&] (std::pair<const Object, size_t> &curr)
        {
            curr.second = 0;
        });
}

/**
 * \brief Will return the object from the name given in parameters
 * \param name The name of the object
 * \return The object code corresponding
 */
Inventory::Object Inventory::getObjectFromName(std::string const &name)
{
    Object toret = NONE;

    std::for_each(objectsName.begin(), objectsName.end(), [&toret, &name] (std::pair<Object, std::string> const &curr)
        {
            if (curr.second == name)
                toret = curr.first;
        });
    return toret;
}

/**
 * \brief Will return the name of the object given in parameters
 * \param object The object you want to get the name
 * \return The name of the object given in parameter
 */
std::string const &Inventory::getNameFromObject(Inventory::Object object)
{
    std::map<Object, std::string >::const_iterator it = objectsName.find(object);

    if (it == objectsName.end())
        throw std::logic_error("You give an object that has no name");
    return it->second;
}

int Inventory::GetNbOf(lua_State *state)
{
    Lua::LuaScript(state).PushVar(static_cast<int>(stuff[static_cast<Object >(Lua::LuaScript(state).GetInteger())]));
    return 1;
}
