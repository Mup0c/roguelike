#pragma once

#include <vector>
#include "point.h"

class Character
{
public:
    Character(int hp, int damage, char symbol, Point pos) : hp_(hp), damage_(damage), symbol_(symbol), pos_(pos) {};
    int hp() const { return hp_; }
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
    Navalny(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    Point dir() const { return dir_; }
    void dir(Point new_dir) { dir_ = new_dir; }
    void move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;

private:
    Point dir_ = Point(0, 0);  //че делать с памятью, как передавать, нет же утечек без использования new? Почему не нужен шаред птр

};

class Omon: public Character
{
public:
    Omon(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;

};

class Putan: public Character
{
public:
    Putan(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;
    void collide(Character &other,
                 std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) override;

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
