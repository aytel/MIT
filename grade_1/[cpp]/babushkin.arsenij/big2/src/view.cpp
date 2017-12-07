#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "view.h"

const std::string View::chars = "XO.";

View::View(Board &board, bool silent): board(&board), silent(silent) {}

void View::ShowBoard() {
    for (size_t x = 0; x < board->BoardSize; x++) {
        for (size_t y = 0; y < board->BoardSize; y++) {
            std::cout << chars[(int)board->type(x, y)];
        }
        std::cout << '\n';
    }
}

void View::DoGameCycle() {
    if (!silent) {
        ShowBoard();
    }
    int x, y;
    std::string buff;
    std::string line;
    while (1) {
        std::cout << (board->status() == ZeroesMove ? 'O' : 'X') << " move: ";
        getline(std::cin, line);
        std::stringstream sin(line);
        if (!(sin >> x >> y) || (sin >> buff) || (board->type(x, y) != Empty && (x != -1 || y != -1))) {
            std::cout << "Bad move!\n";
            continue;
        }
        board->move(x, y);
        return;
    }
}