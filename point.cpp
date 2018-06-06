#include "point.h"

bool operator == (const Point& first, const Point& second) {
    return (first.x() == second.x() && first.y() == second.y());
}