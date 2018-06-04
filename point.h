#pragma once

class Point
{
public:
    Point(int x, int y): x_(x), y_(y) {}
    Point() = default;
    int x() const { return x_; }
    int y() const { return y_; }
    void x(int new_x) { x_ = new_x; }
    void y(int new_y) { y_ = new_y; }

private:
    int x_, y_;

};