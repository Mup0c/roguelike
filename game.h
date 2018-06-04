#pragma once

#include "characters.h"

class Game
{
public:
    void start();
    void make_map();
    void make_turn();
    void draw();
    std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map() { return map_; }
    std::vector<std::shared_ptr<Character>> &movables() { return movables_; }
    std::shared_ptr<Navalny> navalny() { return navalny_; }

private:
    std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map_;
    std::vector<std::shared_ptr<Character>> movables_;
    std::shared_ptr<Navalny> navalny_;

};