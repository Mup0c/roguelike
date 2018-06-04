//
// Created by Admin on 25.04.2018.
//
#pragma once
#include <vector>

//Убрать main.h, разнести по файлам

class Point
{
public:
    Point(int x, int y): x_(x), y_(y) {}
    Point() = default;
    int x() const { return x_; }
    int y() const { return y_; }
    void x(int new_x) { x_ = new_x; }
    void y(int new_y) { y_ = new_y; }

private:
    int x_, y_;

};

class Character
{
public:
    Character(int hp, int damage, char symbol, Point pos) : hp_(hp), damage_(damage), symbol_(symbol), pos_(pos) {};
    int hp() const { return hp_; }
    int damage() const { return damage_; }
    char symbol() const { return symbol_; }
    Point pos() const { return pos_; }
    void pos(Point new_pos) { pos_ = new_pos; }
    virtual void move(std::vector<std::vector<std::shared_ptr<Character>>> &map) {};
    virtual void collide(Character &other,
                         std::vector<std::vector<std::shared_ptr<Character>>> &map);

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
    void move(std::vector<std::vector<std::shared_ptr<Character>>> &map) override;
    void collide(Character &other,
                 std::vector<std::vector<std::shared_ptr<Character>>> &map) override;

private:
    Point dir_ = Point(0, 0);

};

class Omon: public Character
{
public:
    Omon(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void move(std::vector<std::vector<std::shared_ptr<Character>>> &map) override;
    void collide(Character &other,
                 std::vector<std::vector<std::shared_ptr<Character>>> &map) override;


};

class Putan: public Character
{
public:
    Putan(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void move(std::vector<std::vector<std::shared_ptr<Character>>> &map) override;
    void collide(Character &other,
                 std::vector<std::vector<std::shared_ptr<Character>>> &map) override;

};

class Kremlin: public Character
{
public:
    Kremlin(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void collide(Character &other,
                 std::vector<std::vector<std::shared_ptr<Character>>> &map) override;
};


class Wall: public Character
{
public:
    Wall(int hp, int damage, char symbol, Point pos) : Character(hp, damage, symbol, pos) {};
    void collide(Character &other,
                 std::vector<std::vector<std::shared_ptr<Character>>> &map) override {};

};

class Game
{
public:
    void make_map();
    void make_turn();
    void draw();
    std::vector<std::vector<std::shared_ptr<Character>>> &map() { return map_; }
    std::vector<std::shared_ptr<Character>> &movables() { return movables_; }
    std::shared_ptr<Navalny> navalny() { return navalny_; }
private:
    std::vector<std::vector<std::shared_ptr<Character>>> map_;
    std::vector<std::shared_ptr<Character>> movables_;
    std::shared_ptr<Navalny> navalny_;
};