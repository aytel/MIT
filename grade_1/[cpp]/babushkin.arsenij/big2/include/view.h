#ifndef VIEW
#define VIEW

using namespace std;

#include "board.h"
#include <string>

class View {
public:
    View(Board &board, bool silent);

    void ShowBoard();
    void DoGameCycle();

private:
    Board *board;
    const bool silent;
    static const std::string chars;
};

#endif