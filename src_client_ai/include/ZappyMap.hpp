//
// Created by gaspar_q on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYMAP_HPP
#define PSU_2015_ZAPPY_ZAPPYMAP_HPP

#include <map>
#include "Inventory.hpp"
#include "Vector2.hpp"
#include "ZappyRequest.hpp"
#include "ObjectArray.hpp"

class ZappyMap
{
public:
    explicit ZappyMap(Vector2 const &dimensions, ZappyRequest *request, std::map<Vector2, ObjectArray> const &map = {});
    ZappyMap(ZappyMap const &ref);
    ~ZappyMap();
    ZappyMap    &operator=(ZappyMap const &ref);

public:
    void Refresh(Vector2 const &from, Vector2 const &direction, std::vector<std::vector<std::string> > const &objects);
    ObjectArray getObjectsAt(Vector2 const &pos) const;
    std::vector<ObjectArray> getIaSight(Vector2 const &from, Vector2 const &direction, int lvl) const;

private:
    const Vector2 dimmensions;
    std::map<Vector2, ObjectArray>  map;
    ZappyRequest    *request;
    mutable bool    updated;
};

#endif //PSU_2015_ZAPPY_ZAPPYMAP_HPP
