//
// Created by gaspar_q on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYMAP_HPP
#define PSU_2015_ZAPPY_ZAPPYMAP_HPP

#include <map>
#include "Inventory.hpp"
#include "Vector2.hpp"
#include "ZappyRequest.hpp"

class ZappyMap
{
public:
    explicit ZappyMap(Vector2 const &dimensions, ZappyRequest *request, std::map<Vector2, std::vector<Inventory::Object> > const &map = {});
    ZappyMap(ZappyMap const &ref);
    ~ZappyMap();
    ZappyMap    &operator=(ZappyMap const &ref);

public:
    void Refresh(Vector2 const &from, Vector2 const &direction, std::vector<std::vector<std::string> > const &objects);
    std::vector<Inventory::Object > getObjectsAt(Vector2 const &pos) const;
    std::vector<std::vector<Inventory::Object >> getIaSight(Vector2 const &from, Vector2 const &direction, int lvl) const;

private:
    const Vector2 dimmensions;
    std::map<Vector2, std::vector<Inventory::Object> >  map;
    ZappyRequest    *request;
};

#endif //PSU_2015_ZAPPY_ZAPPYMAP_HPP
