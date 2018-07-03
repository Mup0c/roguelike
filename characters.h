#pragma once

#include "point.h"
#include "map.h"
#include <vector>

class Map;
class Enemy;
class Projectile;
class Pickups;
class Navalny;

class Character
{
public:
    Character(int hp, int damage, char symbol, Point pos) : hp_(hp), damage_(damage), symbol_(symbol), pos_(pos) {}
    virtual ~Character() = default;
    int hp() const { return hp_; }
    void hp(int delta) { hp_ += delta; }
    int damage() const { return damage_; }
    char symbol() const { return symbol_; }
    Point pos() const { return pos_; }
    void pos(Point new_pos) { pos_ = new_pos; }
    void destroy() { hp(-hp()); };
    virtual void move(std::shared_ptr<Map> map) {}
    virtual void collide(Character &other, std::shared_ptr<Map> map);
    virtual void collide(Enemy &other, std::shared_ptr<Map> map);
    virtual void collide(Projectile &other, std::shared_ptr<Map> map);
    virtual void collide(Navalny &other, std::shared_ptr<Map> map);

private:
    int hp_;
    int damage_;
    char symbol_;
    Point pos_;

};

class Navalny: public Character
{
public:
    Navalny(int hp, int damage, char symbol, Point pos, int money) : Character(hp, damage, symbol, pos), money_(money) {}
    ~Navalny() override = default;
    Point dir() const { return dir_; }
    int money() const { return money_; }
    void money(int delta) { money_ += delta; }
    void dir(Point new_dir) { dir_ = new_dir; }
    void move(std::shared_ptr<Map> map) override;
    void collide(Character &other, std::shared_ptr<Map> map) override;
    void collide(Projectile &other, std::shared_ptr<Map> map) override;

private:
    Point dir_ = Point(0, 0);
    int money_;

};

class Kremlin: public Character
{
public:
    Kremlin(char symbol, Point pos) : Character(INT_MAX, 0, symbol, pos) {};
    ~Kremlin() override = default;
    void collide(Character &other, std::shared_ptr<Map> map) override {}
    void collide(Navalny &other, std::shared_ptr<Map> map) override;
    void collide(Projectile &other, std::shared_ptr<Map> map) override;

};


class Wall: public Character
{
public:
    Wall(char symbol, Point pos) : Character(INT_MAX, 0, symbol, pos) {}
    ~Wall() override = default;
    void collide(Character &other, std::shared_ptr<Map> map) override {}
    void collide(Projectile &other, std::shared_ptr<Map> map) override;

};

class Pickups: public Character
{
public:
    ~Pickups() override = default;
    int value() const { return value_; }
    void collide(Character &other, std::shared_ptr<Map> map) override {}
    void collide(Projectile &other, std::shared_ptr<Map> map) override;

protected:
    Pickups(int hp, int damage, char symbol, Point pos, int value) : Character(hp, damage, symbol, pos), value_(value) {}

private:
    int value_;
};

class Meth: public Pickups
{
public:
    Meth(char symbol, Point pos, int value) : Pickups(INT_MAX, 0, symbol, pos, value) {}
    ~Meth() override = default;
    void collide(Navalny &other, std::shared_ptr<Map> map) override;
};

class Cash: public Pickups
{
public:
    Cash(char symbol, Point pos, int value) : Pickups(INT_MAX, 0, symbol, pos, value) {}
    ~Cash() override = default;
    void collide(Navalny &other, std::shared_ptr<Map> map) override;
};

class Projectile: public Character
{
public:
    ~Projectile() override = default;
    int cost() const { return cost_; }
    Point dir() const { return dir_; }
    void move(std::shared_ptr<Map> map) override;
    void collide(Character &other, std::shared_ptr<Map> map) override;
    void collide(Projectile &other, std::shared_ptr<Map> map) override;

protected:
    Projectile(int damage, char symbol, Point pos, int cost, Point dir) : Character(INT_MAX, damage, symbol, pos),
                                                                                  cost_(cost), dir_(dir) {}

private:
    int cost_;
    Point dir_;

};

class PaperPlane: public Projectile
{
public:
    PaperPlane(int damage, char symbol, Point pos, int cost, Point dir) : Projectile(damage, symbol, pos, cost, dir) {}
    ~PaperPlane() override = default;

};

class Enemy: public Character
{
public:
    ~Enemy() override = default;
    void move(std::shared_ptr<Map> map) override;
    void collide(Character &other, std::shared_ptr<Map> map) override;
    void collide(Enemy &other, std::shared_ptr<Map> map) override {}
    void collide(Projectile &other, std::shared_ptr<Map> map) override;


protected:
    Enemy(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {}

};

class Omon: public Enemy
{
public:
    Omon(int hp, int damage, char symbol, Point pos) : Enemy(hp, damage, symbol, pos) {}
    ~Omon() override = default;

};

class Putan: public Enemy
{
public:
    Putan(int hp, int damage, char symbol, Point pos) : Enemy(hp, damage, symbol, pos) {}
    ~Putan() override = default;

};