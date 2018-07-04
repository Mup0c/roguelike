#pragma once

#include "characters.h"
#include "config.h"
#include "map.h"

class Game
{
public:
    Game();
    void start();
    void make_turn();
    void draw();
    void shoot(std::shared_ptr<Projectile> projectile);
    std::shared_ptr<Map> map() { return map_; }
    std::shared_ptr<Config> config() const { return config_; }


private:
    std::shared_ptr<Map> map_;
    std::shared_ptr<Config> config_;

};