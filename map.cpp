#include "map.h"

bool const Map::is_on_map(Point pos) {
    return (pos.x() >= 0 && pos.x() < map().size() && pos.y() >= 0 && pos.y() < map()[0].size());
}
