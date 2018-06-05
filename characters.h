#pragma once

#include "point.h"
#include <vector>

class Character
{
public:
    Character(int hp, int damage, char symbol, Point pos) : hp_(hp), damage_(damage), symbol_(symbol), pos_(pos) {};
    int hp() const { return hp_; }
    void hp(int delta) { hp_ += delta; }
    int damage() const { return damage_; }
    char symbol() const { return symbol_; }
    Point pos() const { return pos_; }
    void pos(Point new_pos) { pos_ = new_pos; }
    virtual void move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) {};
    virtual void collide(Character &other,
                         std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map);

private:
    int hp_;
    int damage_;
    char symbol_;
    Point pos_;

};

class Navalny: public Character
{
public:
    Navalny(int hp, int damage, char symbol, Point pos, int mana) : Character(hp, damage, symbol, pos), mana_(mana) {};
    Point dir() const { return dir_; }
    int mana() const { return mana_; }
    void mana(int delta) { mana_ += delta; }
    void dir(Point new_dir) { dir_ = new_dir; }
    void move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;

private:
    Point dir_ = Point(0, 0);  //че делать с памятью, как передавать, нет же утечек без использования new? Почему не нужен шаред птр
    int mana_;

};

class Enemy: public Character
{
public:
    void move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;

protected:
    Enemy(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};

};

class Omon: public Enemy
{
public:
    Omon(int hp, int damage, char symbol, Point pos) : Enemy(hp, damage, symbol, pos) {};

};

class Putan: public Enemy
{
public:
    Putan(int hp, int damage, char symbol, Point pos) : Enemy(hp, damage, symbol, pos) {};

};

class Kremlin: public Character
{
public:
    Kremlin(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;

};


class Wall: public Character
{
public:
    Wall(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override {};

};
//TODO: class mosnter и пустой коллайд между ними