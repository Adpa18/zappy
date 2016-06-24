//
// Created by gaspar_q on 6/21/16.
//

#ifndef PSU_2015_ZAPPY_RECIPEE_HPP
#define PSU_2015_ZAPPY_RECIPEE_HPP

#include "Inventory.hpp"

class Recipee : public std::map<Inventory::Object, size_t>
{
public:
    static const Recipee   recipeesPerLevel[7];

public:
    Recipee(std::map<Inventory::Object, size_t> const &objs = {});

    Recipee(Recipee const &ref);

    ~Recipee();

    using std::map<Inventory::Object, size_t>::operator=;

public:
    size_t operator[](Inventory::Object const &ref) const;

    using std::map<Inventory::Object, size_t >::operator[];

    Recipee operator-(Inventory const ref) const;

public:
    bool CanBeMade(Inventory const &bag) const;

    double GetMissingPercentage(Inventory const &ref) const;

    bool NeedRessource(Inventory::Object const &obj) const;

    static int GetNbOfNeededPlayers(int lvl);
};

#endif //PSU_2015_ZAPPY_RECIPEE_HPP
