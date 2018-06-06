#pragma once

#include "characters.h"

class Game
{
public:
    void start();
    void make_map();
    void make_turn();
    void draw();
    void shoot(std::shared_ptr<Projectile> projectile);
    std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map() { return map_; }
    std::vector<std::shared_ptr<Character>> &interactables() { return interactables_; }
    std::shared_ptr<Navalny> navalny() { return navalny_; }

private:
    std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map_;
    std::vector<std::shared_ptr<Character>> interactables_;
    std::shared_ptr<Navalny> navalny_;

};