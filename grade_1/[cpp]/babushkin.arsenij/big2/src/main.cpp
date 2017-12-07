#include <cstring>
#include <iostream>
#include "view.h"
#include "board.h"

using namespace std;

int main(int argc, char **argv) {

    Board board(10, 5);
    View view(board, (argc > 1 && !strcmp("silent", argv[1])));

    while ((int)board.status() < 2) {
        view.DoGameCycle();
    }

    view.ShowBoard();

    if (board.status() == ZeroesWin) {
        std::cout << "O wins!\n";
    }

    if (board.status() == CrossesWin) {
        std::cout << "X wins!\n";
    }

    if (board.status() == Draw) {
        std::cout << "Draw.\n";
    }

    return 0;
}