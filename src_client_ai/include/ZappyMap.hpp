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
#include "UnsortMap.hpp"

class ZappyMap
{
public:
    typedef UnsortMap<Vector2, ObjectArray >  ObjectMap;

public:
    explicit ZappyMap(Vector2 const &dimensions, ZappyRequest *request);
    ZappyMap(ZappyMap const &ref);
    ~ZappyMap();
    ZappyMap    &operator=(ZappyMap const &ref);

public:
    void Refresh(Vector2 const &from, Vector2 const &direction, std::vector<std::vector<std::string> > const &objects);
    ObjectArray getObjectsAt(Vector2 const &pos) const;
    std::vector<ObjectArray> getIaSight(Vector2 const &from, Vector2 const &direction, int lvl, bool canUpdate = true) const;
    void TakeObjAt(Vector2 const &pos, Inventory::Object obj);
    void DropObjAt(Vector2 const &pos, Inventory::Object obj);
    bool IsUpdated(void) const;
    Vector2 const &Dimmensions(void) const;

private:
    const Vector2   dimmensions;
    ObjectMap       map;
    ZappyRequest    *request;
    mutable bool    updated;
};

#endif //PSU_2015_ZAPPY_ZAPPYMAP_HPP
