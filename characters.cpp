#include "characters.h"
#include <cmath>

const Point directions[] = {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)};

void Character::collide(Character &other, std::shared_ptr<Map> map)
{
    if (map->is_on_map(other.pos())) {
        std::swap(map->map()[this->pos().x()][this->pos().y()], map->map()[other.pos().x()][other.pos().y()]);
    } else {
        map->map()[this->pos().x()][this->pos().y()] = map->interactables().front();
    }
    Point temp = this->pos();
    this->pos(other.pos());
    other.pos(temp);
}

void Character::collide(Enemy &other, std::shared_ptr<Map> map)
{
    Character &other_char = other;
    this->collide(other_char, map);
}

void Character::collide(Projectile &other, std::shared_ptr<Map> map)
{
    Character &other_char = other;
    this->collide(other_char, map);
}

void Character::collide(Navalny &other, std::shared_ptr<Map> map)
{
    Character &other_char = other;
    this->collide(other_char, map);
}

//мув вызывает коллайд от клетки в выбранном направлении. Коллайд дамажит\свапает\двигает и вызывает обратный коллайд(нет)
//Коллайд - other произваодит действие над this

void Navalny::move(std::shared_ptr<Map> map)
{
    Point other_pos(this->pos().x() + dir().x(), this->pos().y() + dir().y());
    if (!(this->pos() == other_pos)) {
        map->map()[other_pos.x()][other_pos.y()]->collide(*this, map);
    }
}

void Navalny::collide(Character &other, std::shared_ptr<Map> map)
{
    this->hp(-other.damage());
}

void Navalny::collide(Projectile &other, std::shared_ptr<Map> map)
{
    this->hp(-other.damage());
    other.destroy();
}

void Enemy::move(std::shared_ptr<Map> map) //DONE: Вынесены направления
{
    Point dir = directions[rand() % 4];
    Point other_pos(this->pos().x() + dir.x(), this->pos().y() + dir.y());
    map->map()[other_pos.x()][other_pos.y()]->collide(*this, map);
}

void Enemy::collide(Character &other, std::shared_ptr<Map> map)
{
    this->hp(-other.damage());
}

void Enemy::collide(Projectile &other, std::shared_ptr<Map> map)
{
    this->hp(-other.damage());
    other.destroy();
}

void Kremlin::collide(Projectile &other, std::shared_ptr<Map> map)
{
    other.destroy();
}

void Kremlin::collide(Navalny &other, std::shared_ptr<Map> map)
{
    Character::collide(other, map);
    this->destroy();
}

void Projectile::collide(Character &other, std::shared_ptr<Map> map)
{
    other.hp(-this->damage());
    Character::collide(other, map);
    this->destroy();
}

void Projectile::move(std::shared_ptr<Map> map)
{
    Point other_pos = abs(this->pos()) + dir();
    map->map()[other_pos.x()][other_pos.y()]->collide(*this, map);
}

void Projectile::collide(Projectile &other, std::shared_ptr<Map> map)
{
    this->destroy();
    other.destroy();
}

void Wall::collide(Projectile &other, std::shared_ptr<Map> map)
{
    other.destroy();
}

void Pickups::collide(Projectile &other, std::shared_ptr<Map> map)
{
    other.destroy();
}

void Meth::collide(Navalny &other, std::shared_ptr<Map> map)
{
    other.hp(value());
    this->destroy();
    Character &other_char = other;
    Character::collide(other_char, map);
}

void Cash::collide(Navalny &other, std::shared_ptr<Map> map)
{
    other.money(value());
    this->destroy();
    Character &other_char = other;
    Character::collide(other_char, map);
}
