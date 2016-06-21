//
// Created by gaspar_q on 6/21/16.
//

#include "Recipee.hpp"

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

bool Recipee::CanBeMade(Inventory const &bag) const
{
    Recipee copy = *this;
    const std::map<Inventory::Object, size_t > &stuff = bag.getStuff();

    for (std::pair<Inventory::Object, size_t > const &curr : stuff)
    {
        if (copy[curr.first] > 0)
            --copy[curr.first];
    }
    for (std::pair<Inventory::Object, size_t> const &curr : copy)
    {
        if (curr.second > 0)
            return false;
    }
    return true;
}