#include <cstring>
#include <vector>
#include "dsu.h"
#include "board.h"

using namespace std;

const std::vector<std::vector<std::pair<int,int>>> Board::neighbors = {
    { { 0, 1 }, { 0, -1 } },
    { { 1, 0 }, { -1, 0 } },
    { { 1, -1 }, { -1, 1 } },
    { { 1, 1 }, { -1, -1 } }
};

void Board::move(int x, int y) {
    if (x == -1 && y == -1) {
        Status = Draw;
        return;
    }

    CellType Type = (status() == CrossesMove ? Cross : Zero);
    fields[x][y] = Type;
    for (int dir = 0; dir < 4; dir++) {
        for (std::pair<int,int> mv : neighbors[dir]) {
            int nx = x + mv.first, ny = y + mv.second;
            if (Type == type(nx, ny)) {
                directs[dir].merge( std::make_pair(x, y), std::make_pair(nx, ny));
            }
        }
        if (directs[dir].get_size( std::make_pair(x, y)) >= (int)WinLen) {
            Status = (Type == Cross ? CrossesWin : ZeroesWin);
        }
    }
    if (status() == ZeroesMove) {
        Status = CrossesMove;
        return;
    }
    if (status() == CrossesMove) {
        Status = ZeroesMove;
        return;
    }
}

GameStatus Board::status() {
    return Status;
}

Board::Board(size_t BoardSize, size_t WinLen): BoardSize(BoardSize), WinLen(WinLen), 
fields(std::vector<std::vector<CellType>>(BoardSize, std::vector<CellType>(BoardSize, Empty))),
directs(4), Status(ZeroesMove) {
    for (size_t dir = 0; dir < 4; dir++) {
        for (size_t x = 0; x < BoardSize; x++) {
            for (size_t y = 0; y < BoardSize; y++) {
                directs[dir].push( std::make_pair(x, y));
            }
        }
    }
}

CellType Board::type(int x, int y) {
    if (x < 0 || y < 0 || x >= (int)BoardSize || y >= (int)BoardSize) {
        return Invalid;
    }
    return fields[x][y];
}

