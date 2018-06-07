#pragma once

#include "characters.h"
#include "map.h"

class Game
{
public:
    void start();
    void make_map();
    void make_turn();
    void draw();
    void shoot(std::shared_ptr<Projectile> projectile);
    std::shared_ptr<Map> map() { return map_; }

private:
    std::shared_ptr<Map> map_;

};