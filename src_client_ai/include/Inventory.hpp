//
// Created by gaspar_q on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_INVENTORY_HPP
#define PSU_2015_ZAPPY_INVENTORY_HPP

#include <stddef.h>
#include <map>
#include <vector>

class Inventory
{
public:
    enum    Object
    {
        NONE,
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

public:
    Inventory(std::map<Object, size_t> const &stuff = {
            {FOOD, 0},
            {LINEMATE, 0},
            {DERAUMERE, 0},
            {SIBUR, 0},
            {MENDIANE, 0},
            {PHIRAS, 0},
            {THYSTAME, 0}
    });
    Inventory(Inventory const &ref);
    ~Inventory();
    Inventory   &operator=(Inventory const &ref);

private:
    static const std::map<Object, std::string>  objectsName;

public:
    static Object getObjectFromName(std::string const &name);
    static std::string const &getNameFromObject(Object object);

public:
    void Add(Object object);
    void Remove(Object object);
    std::map<Object, size_t> const &getStuff(void) const;
    void Refresh(std::vector<std::vector<std::string>> const &content);
    void Reset(void);

public:
    size_t operator[](Object object) const;
    size_t &operator[](Object object);

private:
    std::map<Object, size_t> stuff;
};

#endif //PSU_2015_ZAPPY_INVENTORY_HPP
