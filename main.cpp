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

	bool escape = false;
	while (!escape) {
		int key = getch();
		switch (key) {
		case 119: {
			game.navalny()->dir(Point(-1, 0));
			break;
		}
		case 115: {
			game.navalny()->dir(Point(1, 0));
			break;
		}
		case 100: {
			game.navalny()->dir(Point(0, 1));
			break;
		}
		case 97: {
			game.navalny()->dir(Point(0, -1));
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

void Character::collide(const std::shared_ptr<Character> other,
						std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
	std::swap((*map)[this->pos().x()][this->pos().y()], (*map)[other->pos().x()][other->pos().y()]);
}

//мув вызывает коллайд от клетки в выбранном направлении. Коллайд дамажит\свапает\двигает и вызывает обратный коллайд(нет)

void Navalny::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{
	Point other_pos(this->pos().x() + dir().x(), this->pos().y() + dir().y());
	(*map)[other_pos.x()][other_pos.y()]->collide(std::make_shared<Character>(*this), map);
}

void Navalny::collide(const std::shared_ptr<Character> other,
					  std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{

}


void Game::make_map() { //вынести константы
	std::vector<std::vector<std::shared_ptr<Character>>> map;
	int row_size = 20;
	int col_size = 10;
	map.resize(col_size);
	for (int i = 0; i < col_size; ++i) {
		map[i].resize(row_size);
		for (int j = 0; j < row_size; ++j) {
			if (i == 0 || j == 0 || i == col_size - 1 || j == row_size - 1) {
				map[i][j] = std::make_shared<Wall>(INT_MAX, 0, '#', Point(i, j));
			} else {
				map[i][j] = std::make_shared<Character>(INT_MAX, 0, '.', Point(i, j));
			}
		}
	}
	navalny_ = std::make_shared<Navalny>(100, 5, 'N', Point(1, 1));
	map[1][1] = navalny_;
	map[3][3] = std::make_shared<Wall>(INT_MAX, 0, '#', Point(3, 3));
	map[4][4] = std::make_shared<Omon>(10, 5, 'O', Point(4, 4));
	map[5][5] = std::make_shared<Putan>(30, 10, 'P', Point(5, 5));
	map[7][7] = std::make_shared<Kremlin>(INT_MAX, 0, 'K', Point(7, 7));
	map_ = std::make_shared<std::vector<std::vector<std::shared_ptr<Character>>>>(map);
}

void Game::make_turn() {
// бежать по моваблес

}

void Game::draw() {
	clear();
	for (const auto &i : (*map())){
		for (const auto &j : i){
			char symbol = (j->symbol());
			addch(symbol);
		}
		printw("\n");
	}
}

void Omon::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map) {
	Point other_pos(this->pos().x() + (rand() % 3 - 1), this->pos().y() + (rand() % 3 - 1));
	(*map)[other_pos.x()][other_pos.y()]->collide(std::make_shared<Character>(*this), map);
		            // проверку убрать, мап не передавать, вынести двигующихся в отедльный массив
		//можно возвращать дельту перемещения предполагаемого
		//валидатор смотрит клетку координаты которой хранятся в моваблес, если там пол, то добавляем к координатам дельту
}

void Omon::collide(const std::shared_ptr<Character> other,
				   std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{

}

void Putan::move(std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>>  map) {
	Point other_pos(this->pos().x() + (rand() % 3 - 1), this->pos().y() + (rand() % 3 - 1));
	(*map)[other_pos.x()][other_pos.y()]->collide(std::make_shared<Character>(*this), map);
}

void Putan::collide(const std::shared_ptr<Character> other,
					std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{

}

void Kremlin::collide(const std::shared_ptr<Character> other,
					   std::shared_ptr<std::vector<std::vector<std::shared_ptr<Character>>>> map)
{

}
