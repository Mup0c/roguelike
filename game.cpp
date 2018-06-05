#include "game.h"
#include <ncurses.h>
#include <string>

//TODO: Game over, game win
void Game::make_map()
{ //TODO: вынести константы, сделать загрузку карты и параметров героев с файла
    map_ = std::make_shared<std::vector<std::vector<std::shared_ptr<Character>>>>();
    std::vector<std::vector<std::shared_ptr<Character>>> map;
    std::vector<std::shared_ptr<Character>> movables;
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
    navalny_ = std::make_shared<Navalny>(100, 5, 'N', Point(1, 1), 50);
    map[1][1] = navalny_;
    map[3][3] = std::make_shared<Wall>(INT_MAX, 0, '#', Point(3, 3));
    map[4][4] = std::make_shared<Omon>(11, 2, 'O', Point(4, 4));
    map[5][5] = std::make_shared<Putan>(30, 9, 'P', Point(5, 5));
    map[7][7] = std::make_shared<Kremlin>(INT_MAX, 0, 'K', Point(7, 7));
    movables.push_back(map[1][1]);
    movables.push_back(map[4][4]);
    movables.push_back(map[5][5]);
    movables_ = movables;
    (*map_) = map;
}

void Game::make_turn() {
    for (auto movable : movables()){
        movable->move(map());
        auto debug_map = *map();         //debug info
    }
    for (int i = 0; i < movables().size(); ++i){
        if (movables()[i]->hp() <= 0) {
            Point pos = movables()[i]->pos();
            (*map())[pos.x()][pos.y()] = std::make_shared<Character>(INT_MAX, 0, '.', Point(pos.x(), pos.y()));
            movables().erase(movables().begin() + i);
        }
    }
}

void Game::draw() {
    clear();
    auto temp_map = *map();
    for (const auto &i : temp_map){
        for (const auto &j : i){
            char symbol = (j->symbol());
            addch(symbol);
        }
        addch('\n');
    }
    addstr((" HP: " + std::to_string(navalny()->hp()) + "\n MP: " + std::to_string(navalny()->mana()) + "\n").c_str());

    for (auto movable : movables()){
        addch(movable->symbol());
        addstr((" HP: " + std::to_string(movable->hp()) + "\n").c_str());  //debug info
    }

}

void Game::start() {
    make_map();

    initscr();	noecho();	raw(); draw();

    bool escape = false;
    while (!escape) {
        int key = getch();
        switch (key) {
        case 119: {
            navalny()->dir(Point(-1, 0));
            break;
        }
        case 115: {
            navalny()->dir(Point(1, 0));
            break;
        }
        case 100: {
            navalny()->dir(Point(0, 1));
            break;
        }
        case 97: {
            navalny()->dir(Point(0, -1));
            break;
        }
        case 27: {
            escape = true;
        }
        default: {
            continue;
        }
        }
        make_turn();
        draw();
    }
    clear();
    endwin();
}


//TODO: для снарядов определить коллайд который будет ставить их хп в минус, вызывать коллайд обратно от всех персов
//коллайд со снарядом принимает дамаг от него и вызывает его дестрой