//
// Created by gaspar_q on 6/11/16.
//

#include <algorithm>
#include "ZappyMap.hpp"

ZappyMap::ZappyMap(Vector2 const &dimensions, std::map<Vector2, std::vector<Inventory::Object> > const &map) :
    dimmensions(dimensions),
    map(map)
{

}

ZappyMap::ZappyMap(ZappyMap const &ref) :
    ZappyMap(ref.dimmensions, ref.map)
{
}

ZappyMap::~ZappyMap()
{

}

ZappyMap &ZappyMap::operator=(ZappyMap const &ref)
{
    map = ref.map;
    return *this;
}

/**
 * Direction (0, 1):           decal ^< |   dir ^  |    0
 *      decal   = (-1, 1)          0    |   from   |    0
 *      line    = (1, 0)           0    |     0    |    0
 *                             >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> (line)
 *
 * Direction (0, -1):              0    |     0    |    0
 *      decal   = (1, -1)          0    |   from   |    0
 *      line    = (-1, 0)          0    |   dir v  |  decal v>
 *                             <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< (line)
 *
 * Direction (1, 0):               0    |     0    |  decal >^     v
 *      decal   = (1, 1)           0    |   from   |  dir >        v
 *      line    = (0, -1)          0    |     0    |    0          v
 *                                                               (line)
 *
 * Direction (-1, 0):              0    |     0    |    0          ^
 *      decal   = (-1, -1)       dir <  |   from   |    0          ^
 *      line    = (0, 1)       decal <v |     0    |    0          ^
 *                                                               (line)
 * ---------------------------------------------------------------------
 * decal    = (-direction.y + direction.x, direction.x + direction.y)
 * line     = (direction.y, -direction.x)
 *
 * range        += 1
 * lineLength   += 2
 * todo check if this works well
 */
void ZappyMap::Refresh(Vector2 const &from, Vector2 const &direction,
                       std::vector<std::vector<std::string> > const &objects)
{
    size_t  range = 0;
    Vector2 decalIterator = {direction.x - direction.y, direction.x + direction.y};
    size_t  lineLength = 1;
    size_t  currLine = 0;
    Vector2 lineIterator = {direction.y, -direction.x};

    for (std::vector<std::string> const &curr : objects)
    {
        if (currLine == lineLength)
        {
            ++range;
            lineLength += 2;
            currLine = 0;
        }
        Vector2 position = decalIterator * range + lineIterator * currLine + from;

        position.limit(Vector2::Zero, dimmensions);
        for (std::string const &string : curr)
        {
            map[position].push_back(Inventory::getObjectFromName(string));
        }
        ++currLine;
    }
}

std::vector<Inventory::Object> ZappyMap::getObjectsAt(Vector2 const &pos) const
{
    std::map<Vector2, std::vector<Inventory::Object> >::const_iterator  it;

    it = map.find(pos);
    if (it == map.end())
        return std::vector<Inventory::Object >();
    return it->second;
}

ZappyMap *ZappyMap::sharedMap(Vector2 const &dimmension)
{
    static ZappyMap *map = NULL;

    if (map && dimmension != Vector2::Zero)
        map = new ZappyMap(dimmension);
    return map;
}
