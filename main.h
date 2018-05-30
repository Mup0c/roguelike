//
// Created by Admin on 25.04.2018.
//
#pragma once
#include <vector>


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
    Character();
    int hp() const { return hp_; }
    int damage() const { return damage_; }
    bool maked_turn() const { return maked_turn_; }
    void maked_turn(bool new_flag) { maked_turn_ = new_flag; }
    virtual char sign() const { return sign_; }
    virtual void move(std::vector<std::vector<std::shared_ptr<Character>>> &map,
                      const std::shared_ptr<Point> &this_pos);
    virtual void collide(const Character &other, const std::shared_ptr<Point> &this_pos,
                         const std::shared_ptr<Point> &other_pos,
                         std::vector<std::vector<std::shared_ptr<Character>>> &map);

protected:
    bool maked_turn_;
    int hp_;
    int damage_;
    char sign_;
};


class Navalny: public Character
{
public:
    Navalny();
    std::shared_ptr<Point> dir() { return dir_; }
    char sign() const override { return sign_; }
    void dir(std::shared_ptr<Point> new_dir) { dir_ = new_dir; }
    void move(std::vector<std::vector<std::shared_ptr<Character>>> &map,
              const std::shared_ptr<Point> &this_pos) override;
    void collide(const Character &other, const std::shared_ptr<Point> &this_pos,   //По идее не нужны же ссылки для шаред птр
                 const std::shared_ptr<Point> &other_pos,
                 std::vector<std::vector<std::shared_ptr<Character>>> &map) override;

private:
    std::shared_ptr<Point> dir_{ std::make_shared<Point> (0, 0) };   //Конструирование шаред понтера ???

};

class Game
{
public:
    void make_map();
    void make_turn();
    void draw();
    std::vector<std::vector<std::shared_ptr<Character>>>* map() { return &map_; }
    std::shared_ptr<Navalny> navalny() { return navalny_; }
private:
    std::vector<std::vector<std::shared_ptr<Character>>> map_;
    std::shared_ptr<Navalny> navalny_;
};