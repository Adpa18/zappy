//
// Created by gaspar_q on 6/21/16.
//

#ifndef PSU_2015_ZAPPY_RECIPEE_HPP
#define PSU_2015_ZAPPY_RECIPEE_HPP

#include "Inventory.hpp"

class Recipee : public std::map<Inventory::Object, size_t>
{
public:
    Recipee(std::map<Inventory::Object, size_t> const &objs = {});
    Recipee(Recipee const &ref);
    ~Recipee();
    using std::map<Inventory::Object, size_t >::operator=;

public:
    size_t const &operator[](Inventory::Object const &ref) const;
    bool CanBeMade(Inventory const &bag) const;
};

#endif //PSU_2015_ZAPPY_RECIPEE_HPP
