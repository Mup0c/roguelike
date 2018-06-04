#include <ncurses.h>
#include "game.h"

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
    navalny_ = std::make_shared<Navalny>(100, 5, 'N', Point(1, 1));
    map[1][1] = navalny_;
    map[3][3] = std::make_shared<Wall>(INT_MAX, 0, '#', Point(3, 3));
    map[4][4] = std::make_shared<Omon>(10, 5, 'O', Point(4, 4));
    map[5][5] = std::make_shared<Putan>(30, 10, 'P', Point(5, 5));
    map[7][7] = std::make_shared<Kremlin>(INT_MAX, 0, 'K', Point(7, 7));
    movables.push_back(map[1][1]);
    movables.push_back(map[3][3]);
    movables.push_back(map[4][4]);
    movables.push_back(map[5][5]);
    movables.push_back(map[7][7]);
    movables_ = movables;
    (*map_) = map;
}

void Game::make_turn() {
    for (auto movable : movables()){
        movable->move(map());
        auto debug_map = *map();         //debug info
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
        printw("\n");
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


//TODO: для снарядов определить коллайд который будет ставить их хп в минус