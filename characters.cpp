#include "characters.h"
#include <cmath>

void Character::collide(Character &other,
                        std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    std::swap((*map)[this->pos().x()][this->pos().y()], (*map)[other.pos().x()][other.pos().y()]);
    Point temp = this->pos();
    this->pos(other.pos());
    other.pos(temp);
    auto debug_map = *map;         //debug info
}

//мув вызывает коллайд от клетки в выбранном направлении. Коллайд дамажит\свапает\двигает и вызывает обратный коллайд(нет)

void Navalny::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Point other_pos(this->pos().x() + dir().x(), this->pos().y() + dir().y());
    (*map)[other_pos.x()][other_pos.y()]->collide(*this, map);
}

void Navalny::collide(Character &other,
                      std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->hp(-other.damage());
}

void Enemy::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Point other_pos(this->pos().x() + (rand() % 3 - 1), this->pos().y() + (rand() % 3 - 1));
    (*map)[other_pos.x()][other_pos.y()]->collide(*this, map);
}

void Enemy::collide(Character &other,
                   std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->hp(-other.damage());
}

void Kremlin::collide(Character &other,
                      std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{

}
