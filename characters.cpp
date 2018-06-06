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

void Character::collide(Enemy &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Character &other_char = other;
    this->collide(other_char, map);
}

void Character::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Character &other_char = other;
    this->collide(other_char, map);
}

void Character::collide(Navalny &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Character &other_char = other;
    this->collide(other_char, map);
}

//мув вызывает коллайд от клетки в выбранном направлении. Коллайд дамажит\свапает\двигает и вызывает обратный коллайд(нет)
//Коллайд - other произваодит действие над this

void Navalny::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Point other_pos(this->pos().x() + dir().x(), this->pos().y() + dir().y());
    if (!(this->pos() == other_pos)) {
        (*map)[other_pos.x()][other_pos.y()]->collide(*this, map);
    }
}

void Navalny::collide(Character &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->hp(-other.damage());
}

void Navalny::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->hp(-other.damage());
    other.destroy();
}

void Enemy::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Point dir;
    switch (rand() % 4) {
    case 0: {
        dir = Point(-1, 0);
        break;
    }
    case 1: {
        dir = Point(1, 0);
        break;
    }
    case 2: {
        dir = Point(0, 1);
        break;
    }
    case 3: {
        dir = Point(0, -1);
        break;
    }
    default: {
        break;
    }
    }
    Point other_pos(this->pos().x() + dir.x(), this->pos().y() + dir.y());
    (*map)[other_pos.x()][other_pos.y()]->collide(*this, map);
}

void Enemy::collide(Character &other,
                   std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->hp(-other.damage());
}

void Enemy::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->hp(-other.damage());
}

void Kremlin::collide(Character &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
//TODO: implement
}

void Kremlin::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    other.destroy();
}

void Projectile::collide(Character &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    other.hp(-this->damage());
    Character::collide(other, map);
    this->destroy();
}

void Projectile::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    Point other_pos(this->pos().x() + dir().x(), this->pos().y() + dir().y());
    (*map)[other_pos.x()][other_pos.y()]->collide(*this, map);
}

void Projectile::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    this->destroy();
    other.destroy();
}

void Wall::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    other.destroy();
}

void Pickups::collide(Projectile &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    other.destroy();
}

void Meth::collide(Navalny &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    other.hp(value());
    this->destroy();
    Character &other_char = other;
    Character::collide(other_char, map);
}


void Cash::collide(Navalny &other, std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
    other.money(value());
    this->destroy();
    Character &other_char = other;
    Character::collide(other_char, map);
}
