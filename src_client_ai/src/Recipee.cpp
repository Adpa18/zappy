//
// Created by gaspar_q on 6/21/16.
//

#include "Recipee.hpp"

const Recipee   Recipee::recipeesPerLevel[7] = {
        Recipee({
                        {Inventory::LINEMATE, 1}
                }),
        Recipee({
                        {Inventory::LINEMATE, 1},
                        {Inventory::DERAUMERE, 1}
                }),
        Recipee({
                        {Inventory::LINEMATE, 2},
                        {Inventory::SIBUR, 1},
                        {Inventory::PHIRAS, 2}
                }),
        Recipee({
                        {Inventory::LINEMATE, 1},
                        {Inventory::DERAUMERE, 1},
                        {Inventory::SIBUR, 2},
                        {Inventory::PHIRAS, 1}
                }),
        Recipee({
                        {Inventory::LINEMATE, 1},
                        {Inventory::DERAUMERE, 2},
                        {Inventory::SIBUR, 1},
                        {Inventory::MENDIANE, 3}
                }),
        Recipee({
                        {Inventory::LINEMATE, 1},
                        {Inventory::DERAUMERE, 2},
                        {Inventory::SIBUR, 3},
                        {Inventory::PHIRAS, 1}
                }),
        Recipee({
                        {Inventory::LINEMATE, 2},
                        {Inventory::DERAUMERE, 2},
                        {Inventory::SIBUR, 2},
                        {Inventory::MENDIANE, 2},
                        {Inventory::PHIRAS, 2},
                        {Inventory::THYSTAME, 1}
                })
};

Recipee::Recipee(const std::map<Inventory::Object, size_t> &objs) :
    std::map<Inventory::Object, size_t>(objs)
{

}

Recipee::Recipee(Recipee const &ref) :
    Recipee(static_cast<std::map<Inventory::Object, size_t> >(ref))
{

}

Recipee::~Recipee()
{

}

size_t const &Recipee::operator[](Inventory::Object const &ref) const
{
    std::map<Inventory::Object, size_t >::const_iterator it = find(ref);

    if (it == end())
        throw std::logic_error("No object at this index");
    return it->second;
}

Recipee Recipee::operator-(Inventory const ref) const
{
    Recipee copy = *this;

    const std::map<Inventory::Object, size_t > &stuff = ref.getStuff();

    for (std::pair<Inventory::Object, size_t > const &curr : stuff)
    {
        try
        {
            if (copy[curr.first] > 0)
                copy[curr.first] -= curr.second;
        }
        catch (std::exception &){}
    }
    return copy;
}

bool Recipee::CanBeMade(Inventory const &bag) const
{
    Recipee copy = (*this - bag);

    for (std::pair<Inventory::Object, size_t> const &curr : copy)
    {
        if (curr.second > 0)
            return false;
    }
    return true;
}

double Recipee::GetMissingPercentage(Inventory const &ref) const
{
    Recipee copy = (*this - ref);
    double total = 0, got = 0;

    for (std::pair<Inventory::Object, size_t> const &curr : *this)
    {
        total += curr.second;
        try
        {
            got += (curr.second - copy[curr.first]);
        }
        catch (std::exception &){}
    }
    return (got / total);
}

bool Recipee::NeedRessource(Inventory::Object const &obj) const
{
    try
    {
        return (*this)[obj] > 0;
    }
    catch (std::exception &){}
    return false;
}