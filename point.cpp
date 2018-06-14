#include "point.h"
#include <algorithm>

bool operator == (const Point& first, const Point& second) {
    return (first.x() == second.x() && first.y() == second.y());
}

Point abs(Point point) {
    return Point(abs(point.x()), abs(point.y()));
}

Point Point::operator-() {
    return Point(-x_, -y_);
}

Point Point::operator+(Point other) {
    return Point(x_ + other.x(), y_ + other.y());
}
