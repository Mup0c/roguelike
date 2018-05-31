#include <ncurses.h>
#include <math.h>
#include "main.h"

int main() {
	// Initialize ncurses
	initscr();
	noecho();
	raw();

	Game game;
	game.make_map();
	game.draw();
	game.navalny()->dir(std::make_shared<Point>(0, 0));

	bool escape = false;
	while (!escape) {
		int key = getch();
		switch (key) {
		case 119: {
			game.navalny()->dir(std::make_shared<Point>(-1, 0));
			break;
		}
		case 115: {
			game.navalny()->dir(std::make_shared<Point>(1, 0));
			break;
		}
		case 100: {
			game.navalny()->dir(std::make_shared<Point>(0, 1));
			break;
		}
		case 97: {
			game.navalny()->dir(std::make_shared<Point>(0, -1));
			break;
		}
		case 27: {
			escape = true;
		}
		default: {
			continue;
		}
		}
		game.make_turn();
		game.draw();
	}
	clear();
 	endwin();
 }

void Character::collide(const Character &other, const std::shared_ptr<Point> &this_pos,
						const std::shared_ptr<Point> &other_pos,
						std::vector<std::vector<std::shared_ptr<Character>>> &map)
{
	std::swap(map[this_pos->x()][this_pos->y()], map[other_pos->x()][other_pos->y()]);
}

Character::Character() {
	maked_turn_ = false;
	hp_ = INT_MAX;
	damage_ = 0;
	sign_ = '.';
}

void Character::move(std::vector<std::vector<std::shared_ptr<Character>>> &map, const std::shared_ptr<Point> &this_pos) {
	maked_turn(true);
}

//мув вызывает коллайд от клетки в выбранном направлении. Коллайд дамажит\свапает\двигает и вызывает обратный коллайд(нет)
	//std::swap(map[_position.x][_position.y], map[_position.x + _direction.x][_position.y + _direction.y])

void Navalny::move(std::vector<std::vector<std::shared_ptr<Character>>> &map, const std::shared_ptr<Point> &this_pos)
{
	auto other_pos = std::make_shared<Point> (this_pos->x() + dir()->x(), this_pos->y() + dir()->y());
	if (other_pos->x() >= 0 && other_pos->x() < map.size() && other_pos->y() >= 0 && other_pos->y() < map[0].size()) {
		map[other_pos->x()][other_pos->y()]->collide(*this, other_pos, this_pos, map);
	}
    maked_turn(true);
}

void Navalny::collide(const Character &other, const std::shared_ptr<Point> &this_pos,
					  const std::shared_ptr<Point> &other_pos,
					  std::vector<std::vector<std::shared_ptr<Character>>> &map)
{

}

Navalny::Navalny() {
	hp_ = 100;
	damage_ = 5;
	dir_ = std::make_shared<Point> (0, 0);
	sign_ = 'N';
}

void Game::make_map() {
	std::vector<std::vector<std::shared_ptr<Character>>> map (10, std::vector<std::shared_ptr<Character>>(20, std::make_shared<Character>()));
	navalny_ = std::make_shared<Navalny>();
	map[1][1] = navalny_;
	map[3][3] = std::make_shared<Wall>();
	map[4][4] = std::make_shared<Omon>();
	map[5][5] = std::make_shared<Putan>();
	map[7][7] = std::make_shared<Kremlin>();
	map_ = map;				//Не оч copy
}

void Game::make_turn() {

	for (int i = 0; i < (*map()).size(); ++i) {
		for (int j = 0; j < (*map())[i].size(); ++j) {
			if (!(*map())[i][j]->maked_turn()) {
				(*map())[i][j]->move((*map()), std::make_shared<Point>(i, j));
			}
		}
	}
	for (auto &i : *map()) {
		for (auto &j : i) {
			j->maked_turn(false);
		}
	}
}

void Game::draw() {
	clear();
	for (const auto &i : map_){
		for (const auto &j : i){
			char sign = (j->sign());
			addch(sign);
		}
		printw("\n");
	}
}


Wall::Wall() {
	maked_turn_ = false;
	hp_ = INT_MAX;
	damage_ = 0;
	sign_ = '#';
}

Omon::Omon() {
	maked_turn_ = false;
	hp_ = 10;
	damage_ = 5;
	sign_ = 'O';
}

void Omon::move(std::vector<std::vector<std::shared_ptr<Character>>> &map, const std::shared_ptr<Point> &this_pos) {
	auto other_pos = std::make_shared<Point> (this_pos->x() + (rand() % 3 - 1), this_pos->y() + (rand() % 3 - 1));
	if (other_pos->x() >= 0 && other_pos->x() < map.size() && other_pos->y() >= 0 && other_pos->y() < map[0].size()) {
		map[other_pos->x()][other_pos->y()]->collide(*this, other_pos, this_pos, map);
	}
	maked_turn(true);
}

void Omon::collide(const Character &other, const std::shared_ptr<Point> &this_pos,
				   const std::shared_ptr<Point> &other_pos,
				   std::vector<std::vector<std::shared_ptr<Character>>> &map)
{

}

Putan::Putan() {
	maked_turn_ = false;
	hp_ = 100;
	damage_ = 20;
	sign_ = 'P';
}

void Putan::move(std::vector<std::vector<std::shared_ptr<Character>>> &map, const std::shared_ptr<Point> &this_pos) {
	auto other_pos = std::make_shared<Point> (this_pos->x() + (rand() % 3 - 1), this_pos->y() + (rand() % 3 - 1));
	if (other_pos->x() >= 0 && other_pos->x() < map.size() && other_pos->y() >= 0 && other_pos->y() < map[0].size()) {
		map[other_pos->x()][other_pos->y()]->collide(*this, other_pos, this_pos, map);
	}
	maked_turn(true);
}

void Putan::collide(const Character &other, const std::shared_ptr<Point> &this_pos,
					const std::shared_ptr<Point> &other_pos,
			   		std::vector<std::vector<std::shared_ptr<Character>>> &map)
{

}

Kremlin::Kremlin() {
	maked_turn_ = false;
	hp_ = INT_MAX;
	damage_ = 0;
	sign_ = 'K';
}

void Kremlin::collide(const Character &other, const std::shared_ptr<Point> &this_pos,
					  const std::shared_ptr<Point> &other_pos,
					  std::vector<std::vector<std::shared_ptr<Character>>> &map)
{

}
