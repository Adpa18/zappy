//
// Created by gaspar_q on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYMAP_HPP
#define PSU_2015_ZAPPY_ZAPPYMAP_HPP

#include <map>
#include "Inventory.hpp"
#include "Vector2.hpp"

class ZappyMap
{
public:
    static ZappyMap *sharedMap(Vector2 const &dimmension = Vector2::Zero);

public:
    explicit ZappyMap(Vector2 const &dimensions, std::map<Vector2, std::vector<Inventory::Object> > const &map = {});
    ZappyMap(ZappyMap const &ref);
    ~ZappyMap();
    ZappyMap    &operator=(ZappyMap const &ref);

public:
    void Refresh(Vector2 const &from, Vector2 const &direction, std::vector<std::vector<std::string> > const &objects);
    std::vector<Inventory::Object > getObjectsAt(Vector2 const &pos) const;

private:
    const Vector2 dimmensions;
    std::map<Vector2, std::vector<Inventory::Object> >  map;
};

#endif //PSU_2015_ZAPPY_ZAPPYMAP_HPP
