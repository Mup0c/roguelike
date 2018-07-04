#include "game.h"
#include <fstream>
#include <ncurses.h>

Game::Game() {
    config_ = std::make_shared<Config>();
    const auto cfg = config()->json();
    bool end = false;
    bool error = false;
    int row = 0;
    int col = 0;
    int rows_cnt = cfg["rows_cnt"];
    int cols_cnt = cfg["cols_cnt"];
    std::vector<std::vector<std::shared_ptr<Character>>> map(rows_cnt, std::vector<std::shared_ptr<Character>>(cols_cnt));
    std::deque<std::shared_ptr<Character>> interactables;
    std::shared_ptr<Navalny> navalny;
    std::shared_ptr<Kremlin> kremlin;

    std::ifstream map_stream("../map.txt");
    while (!end) {
        char character = map_stream.get();
        std::string str_char;
        str_char.push_back(character);
        if (str_char == cfg["Character"]["symbol"]) {
            map[row][col] = std::make_shared<Character>(cfg["Character"]["hp"],
                                                        cfg["Character"]["damage"],
                                                        cfg["Character"]["symbol"],
                                                        Point(row, col));
            col++;
        } else
        if (str_char == cfg["Wall"]["symbol"]) {
            map[row][col] = std::make_shared<Wall>(cfg["Wall"]["symbol"],
                                                   Point(row, col));
            col++;
        } else
        if (str_char == cfg["Navalny"]["symbol"]) {
            navalny = std::make_shared<Navalny>(cfg["Navalny"]["hp"],
                                                cfg["Navalny"]["damage"],
                                                cfg["Navalny"]["symbol"],
                                                Point(row, col),
                                                cfg["Navalny"]["money"]);
            map[row][col] = navalny;
            interactables.push_back(navalny);
            col++;
        } else
        if (str_char == cfg["Kremlin"]["symbol"]) {
            kremlin = std::make_shared<Kremlin>(cfg["Kremlin"]["symbol"],
                                                Point(row, col));
            map[row][col] = kremlin;
            interactables.push_back(kremlin);
            col++;
        } else
        if (str_char == cfg["Meth"]["symbol"]) {
            map[row][col] = std::make_shared<Meth>(cfg["Meth"]["symbol"],
                                                   Point(row, col),
                                                   cfg["Meth"]["value"]);
            interactables.push_back(map[row][col]);
            col++;
        } else
        if (str_char == cfg["Cash"]["symbol"]) {
            map[row][col] = std::make_shared<Cash>(cfg["Cash"]["symbol"],
                                                   Point(row, col),
                                                   cfg["Cash"]["value"]);
            interactables.push_back(map[row][col]);
            col++;
        } else
        if (str_char == cfg["Omon"]["symbol"]) {
            map[row][col] = std::make_shared<Omon>(cfg["Omon"]["hp"],
                                                   cfg["Omon"]["damage"],
                                                   cfg["Omon"]["symbol"],
                                                   Point(row, col));
            interactables.push_back(map[row][col]);
            col++;
        } else
        if (str_char == cfg["Putan"]["symbol"]) {
            map[row][col] = std::make_shared<Putan>(cfg["Putan"]["hp"],
                                                    cfg["Putan"]["damage"],
                                                    cfg["Putan"]["symbol"],
                                                    Point(row, col));
            interactables.push_back(map[row][col]);
            col++;
        } else
        if (character == EOF) {
            end = true;
        } else
        if (character == '\n') {
            col = 0;
            row++;
        } else {
            error = true;
            end = true;
        }
        if (col > cols_cnt || row + 1 > rows_cnt) {
            error = true;
            end = true;
        }
    }
    if (error) {
        printf("\nWrong map!\n\n");
        exit(1);
    }

    map_= std::make_shared<Map>(map, interactables, navalny, kremlin);
}

void Game::make_turn() {
    for (const auto &interactable : map()->interactables()) {
        interactable->move(map());
    }
    for (int i = map()->interactables().size() - 1; i >= 0; --i) {
        if (map()->interactables()[i]->hp() <= 0) {
            Point pos = map()->interactables()[i]->pos();
            if (map()->is_on_map(pos)) {
                const auto cfg = config()->json();
                map()->map()[pos.x()][pos.y()] = std::make_shared<Character>(cfg["Character"]["hp"],
                                                                             cfg["Character"]["damage"],
                                                                             cfg["Character"]["symbol"],
                                                                             Point(pos.x(), pos.y()));
            }
            map()->interactables().erase(map()->interactables().begin() + i);
        }
    }
}

void Game::draw() {
    clear();
    auto temp_map = map()->map();
    for (const auto &i : temp_map) {
        for (const auto &j : i) {
            char symbol = (j->symbol());
            addch(symbol);
        }
        addch('\n');
    }
    addstr((" HP: " + std::to_string(map()->navalny()->hp()) + "\n MP: " + std::to_string(map()->navalny()->money()) + "\n").c_str());

    for (const auto &interactable : map()->interactables()) {
        addch(interactable->symbol());
        addstr((" HP: " + std::to_string(interactable->hp()) + "\n").c_str());  //debug info
    }
}

void Game::start() {
    initscr();	noecho();   raw();  timeout(100);
    const auto cfg = config()->json();
    bool win = false;
    bool loose = false;
    bool escape = false;
    while (!escape) {
        int key = getch();
        if (key == cfg["move_up"]) {
            map()->navalny()->dir(Point(-1, 0));
        } else
        if (key == cfg["move_down"]) {
            map()->navalny()->dir(Point(1, 0));
        } else
        if (key == cfg["move_right"]) {
            map()->navalny()->dir(Point(0, 1));
        } else
        if (key == cfg["move_left"]) {
            map()->navalny()->dir(Point(0, -1));
        } else
        if (key == cfg["shoot_up"]) {
            shoot(std::make_shared<PaperPlane>(cfg["PaperPlane"]["damage"],
                                               cfg["PaperPlane"]["symbol_up"],
                                               -map()->navalny()->pos(),
                                               cfg["PaperPlane"]["cost"],
                                               Point(-1, 0)));
            map()->navalny()->dir(Point(0, 0));
        } else
        if (key == cfg["shoot_down"]) {
            shoot(std::make_shared<PaperPlane>(cfg["PaperPlane"]["damage"],
                                               cfg["PaperPlane"]["symbol_down"],
                                               -map()->navalny()->pos(),
                                               cfg["PaperPlane"]["cost"],
                                               Point(1, 0)));
            map()->navalny()->dir(Point(0, 0));
        } else
        if (key == cfg["shoot_right"]) {
            shoot(std::make_shared<PaperPlane>(cfg["PaperPlane"]["damage"],
                                               cfg["PaperPlane"]["symbol_right"],
                                               -map()->navalny()->pos(),
                                               cfg["PaperPlane"]["cost"],
                                               Point(0, 1)));
            map()->navalny()->dir(Point(0, 0));
        } else
        if (key == cfg["shoot_left"]) {
            shoot(std::make_shared<PaperPlane>(cfg["PaperPlane"]["damage"],
                                               cfg["PaperPlane"]["symbol_left"],
                                               -map()->navalny()->pos(),
                                               cfg["PaperPlane"]["cost"],
                                               Point(0, -1)));
            map()->navalny()->dir(Point(0, 0));
        } else
        if (key == cfg["escape"]) {
            escape = true;
            continue;
        } else {
            map()->navalny()->dir(Point(0, 0));
        }
        make_turn();
        draw();
        win = map()->kremlin()->hp() <= 0;
        loose = map()->navalny()->hp() <= 0;
        if (win || loose) {
            nodelay(stdscr, FALSE);
            break;
        }
    }
    clear();
    if (win) {
        addstr("Congratulations! You win!");
        getch();
    }
    if (loose) {
        addstr("YOU DIED");
        getch();
    }
    endwin();
}

void Game::shoot(std::shared_ptr<Projectile> projectile) {
    if (map()->navalny()->money() < projectile->cost()) { return; }
    map()->navalny()->money(-projectile->cost());
    map()->interactables().push_front(projectile);
}
//при спавне позиция меньше нуля, в муве коллайдимся с позиция шутера+дир
//валидатор в класс map
//стрелять на стрелочки
//все таки инсерт снаряда в начало моваблес