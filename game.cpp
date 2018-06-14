#include "game.h"
#include <ncurses.h>
#include <string>

//TODO: Game over, game win (возвращать с мейк терн)
void Game::make_map()
{ //TODO: вынести константы, сделать загрузку карты и параметров героев с файла
    std::vector<std::vector<std::shared_ptr<Character>>> map;
    std::deque<std::shared_ptr<Character>> interactables;
    int row_size = 20;
    int col_size = 20;
    map.resize(col_size);
    for (int i = 0; i < col_size; ++i) {
        map[i].resize(row_size);
        for (int j = 0; j < row_size; ++j) {
            if (i == 0 || j == 0 || i == col_size - 1 || j == row_size - 1) {
                map[i][j] = std::make_shared<Wall>('#', Point(i, j));
            } else {
                map[i][j] = std::make_shared<Character>(INT_MAX, 0, '.', Point(i, j));
            }
        }
    }
    auto navalny = std::make_shared<Navalny>(100, 5, 'N', Point(1, 1), 50);
    map[1][1] = navalny;
    map[3][3] = std::make_shared<Wall>('#', Point(3, 3));
    map[4][4] = std::make_shared<Omon>(11, 2, 'O', Point(4, 4));
    map[5][5] = std::make_shared<Putan>(30, 9, 'P', Point(5, 5));
    map[7][7] = std::make_shared<Meth>('+', Point(7, 7), 10000);
    map[8][8] = std::make_shared<Cash>('$', Point(8, 8), 10000);
    interactables.push_back(map[1][1]);
    interactables.push_back(map[4][4]);
    interactables.push_back(map[5][5]);
    interactables.push_back(map[7][7]);
    interactables.push_back(map[8][8]);

    map_= std::make_shared<Map>(map, interactables, navalny);
}

void Game::make_turn() {
    for (const auto &interactable : map()->interactables()){
        interactable->move(map());
        auto debug_map = *map();         //debug info
    }
    for (int i = map()->interactables().size() - 1; i >= 0; --i){
        if (map()->interactables()[i]->hp() <= 0) {
            Point pos = map()->interactables()[i]->pos();
            map()->map()[pos.x()][pos.y()] = std::make_shared<Character>(INT_MAX, 0, '.', Point(pos.x(), pos.y()));
            map()->interactables().erase(map()->interactables().begin() + i);
        }
    }
}

void Game::draw() {
    clear();
    auto temp_map = map()->map();
    for (const auto &i : temp_map){
        for (const auto &j : i){
            char symbol = (j->symbol());
            addch(symbol);
        }
        addch('\n');
    }
    addstr((" HP: " + std::to_string(map()->navalny()->hp()) + "\n MP: " + std::to_string(map()->navalny()->money()) + "\n").c_str());

    for (const auto &interactable : map()->interactables()){
        addch(interactable->symbol());
        addstr((" HP: " + std::to_string(interactable->hp()) + "\n").c_str());  //debug info
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
            map()->navalny()->dir(Point(-1, 0));
            break;
        }
        case 115: {
            map()->navalny()->dir(Point(1, 0));
            break;
        }
        case 100: {
            map()->navalny()->dir(Point(0, 1));
            break;
        }
        case 97: {
            map()->navalny()->dir(Point(0, -1));
            break;
        }
        case 101: {
            //shoot(std::make_shared<PaperPlane>(2, '>', Point(0, 0), 4, map()->navalny()->dir()));
            map()->navalny()->dir(Point(0, 0));
            break;
        }
        case 27: {
            escape = true;
        }
        default: {
            map()->navalny()->dir(Point(0, 0));
            continue;
        }
        }
        make_turn();
        draw();
    }
    clear();
    endwin();
}

void Game::shoot(std::shared_ptr<Projectile> projectile) {
   /* if (map()->navalny()->money() < projectile->cost()) { return; }
    map()->navalny()->money(-projectile->cost());
    map()->map()[0][0] = projectile;
    map()->interactables().push_back(projectile);
    Point shooter_pos = map()->navalny()->pos();
    map()->map()[shooter_pos.x() + projectile->dir().x()][shooter_pos.y() + projectile->dir().y()]->collide(*projectile, map());
    draw();*/

}
//при спавне позиция меньше нуля, в муве коллайдимся с позиция шутера+дир
//валидатор в класс map
//стрелять на стрелочки
//все таки инсерт снаряда в начало моваблес