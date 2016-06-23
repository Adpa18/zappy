//
// Created by gaspar_q on 6/20/16.
//

#ifndef PSU_2015_ZAPPY_UNSORTMAP_HPP
#define PSU_2015_ZAPPY_UNSORTMAP_HPP

#include <vector>
#include <algorithm>

template <typename key, typename value>
class UnsortMap : public std::vector<std::pair<key, value> >
{
public:
    UnsortMap()
    {

    }
    UnsortMap(UnsortMap const &ref) :
            std::vector<std::pair<key, value> >(ref)
    {

    }
    using std::vector<std::pair<key, value> >::operator=;

public:
    value   &operator[](key const &index)
    {
        for (std::pair<key, value> &curr : *this)
        {
            if (curr.first == index)
                return curr.second;
        }
        this->push_back(std::make_pair(index, value()));
        return this->back().second;
    }
    value const &operator[](key const &index) const throw(std::out_of_range)
    {
        for (std::pair<key, value> const &curr : *this)
        {
            if (curr.first == index)
                return curr.second;
        }
        throw std::out_of_range("No such index in map");
    }
};

#endif //PSU_2015_ZAPPY_UNSORTMAP_HPP
