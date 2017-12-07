#ifndef BOARD 
#define BOARD

#include <cstring>
#include <vector>
#include "dsu.h"

using namespace std;

enum CellType { Cross = 0, Zero = 1, Empty = 2, Invalid };
enum GameStatus { CrossesWin = 2, ZeroesWin = 3, Draw = 4, CrossesMove = 0, ZeroesMove = 1 };

class Board {
public:
    const size_t BoardSize, WinLen;

    void move(int x, int y);
    GameStatus status();
    Board(size_t BoardSize, size_t WinLen);
    CellType type(int x, int y);

private:
    std::vector<std::vector<CellType>> fields;
    std::vector<dsu<std::pair<int,int>>> directs;
    static const std::vector<std::vector<std::pair<int,int>>> neighbors;
    GameStatus Status;
};

#endif