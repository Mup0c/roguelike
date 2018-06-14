#pragma once

#include "characters.h"
#include <vector>
#include <deque>

class Character;
class Navalny;

class Map
{
public:
    Map(std::vector<std::vector<std::shared_ptr<Character>>> map,
        std::deque<std::shared_ptr<Character>> interactables,
        std::shared_ptr<Navalny> navalny) : map_(map), interactables_(interactables), navalny_(navalny) {};
    std::vector<std::vector<std::shared_ptr<Character>>> &map() { return map_; }
    std::deque<std::shared_ptr<Character>> &interactables() { return interactables_; }
    std::shared_ptr<Navalny> navalny() { return navalny_; }
    bool const is_on_map(Point pos);

private:
    std::vector<std::vector<std::shared_ptr<Character>>> map_;
    std::deque<std::shared_ptr<Character>> interactables_;
    std::shared_ptr<Navalny> navalny_;
};

