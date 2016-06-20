//
// Created by gaspar_q on 6/20/16.
//

#ifndef PSU_2015_ZAPPY_UNSORTMAP_HPP
#define PSU_2015_ZAPPY_UNSORTMAP_HPP

#include <vector>
#include <algorithm>

template <typename key, typename value>
class UnsortMap
{
public:
    UnsortMap()
    {

    }
    UnsortMap(UnsortMap const &ref) :
            objects(ref.objects)
    {

    }
    ~UnsortMap()
    {

    }
    UnsortMap   &operator=(UnsortMap const &ref)
    {
        objects = ref.objects;
        return *this;
    }

public:
    value   &operator[](key const &index)
    {
        for (std::pair<key, value> &curr : objects)
        {
            if (curr.first == index)
                return curr.second;
        }
        objects.push_back(std::make_pair(index, value()));
        return objects.back().second;
    }
    value const &operator[](key const &index) const throw(std::out_of_range)
    {
        for (std::pair<key, value> const &curr : objects)
        {
            if (curr.first == index)
                return curr.second;
        }
        throw std::out_of_range("No such index in map");
    }

private:
    std::vector<std::pair<key, value> > objects;
};

#endif //PSU_2015_ZAPPY_UNSORTMAP_HPP
