#include <ncurses.h>
#include "main.h"

int main() {
	// Initialize ncurses

	Game game;
	game.make_map();
	initscr();
	clear();
	game.draw();

	game.navalny()->dir(std::make_shared<Point>(0, 0));

	noecho();
	//raw();
	while (true){
		int ch = getch();
		if ((ch == 119) || (ch == 115) || (ch == 100) || (ch == 97)) {
			switch (ch)
			{
				case 119:
					game.navalny()->dir(std::make_shared<Point>(-1, 0));
					break;
				case 115:
					game.navalny()->dir(std::make_shared<Point>(1, 0));
					break;
				case 100:
					game.navalny()->dir(std::make_shared<Point>(0, 1));
					break;
				case 97:
					game.navalny()->dir(std::make_shared<Point>(0, -1));
					break;
			}
			game.make_turn();
			game.draw();
		}
		if (ch == 27) {
			break;
		}
	}
	clear;
	//Print a string on screen
	printw("Seems that you can use ncurses ...\nPress any key to exit!");

 	// Wait until the user press a key
 	getch();

 	// Clear ncurses data structures
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
    map[other_pos->x()][other_pos->y()]->collide(*this, other_pos, this_pos, map);
    maked_turn(true);


   // swap(map[_position.x][_position.y], map[_position.x + _direction.x][_position.y + _direction.y])
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
	map[1][1] =navalny_;
	map_ = map;
}

void Game::make_turn() {

	for (int i = 0; i < map_.size(); ++i) {
		for (int j = 0; j < map_[i].size(); ++j) {
			if (!map_[i][j]->maked_turn()) {
				map_[i][j]->move(map_, std::make_shared<Point>(i, j));
			}
		}
	}
	for (auto &i : map_) {
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
	refresh();
}
