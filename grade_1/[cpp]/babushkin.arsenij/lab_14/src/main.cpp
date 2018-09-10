#include "matrix.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::vector<Matrix> v(10, Matrix());

    while (true) {
        std::string s;
        std::cin >> s;
        if (s == "exit") {
            break;
        }
        if (s == "load") {
            char c;
            std::cin >> c;
            int reg;
            std::cin >> reg;
            std::string fname;
            std::cin >> fname;
            std::ifstream is(fname, std::ifstream::in);
            is >> v[reg];
        }
        if (s == "print") {
            char c;
            std::cin >> c;
            int reg;
            std::cin >> reg;
            std::cout << v[reg];
        }
        if (s == "add") {
            char c;
            std::cin >> c;
            int reg1, reg2;
            std::cin >> reg1 >> c >> reg2;
            try {
                v[reg1] += v[reg2];
            }
            catch (MatrixException& e) {
                std::cout << e.what();
            }
        }
        if (s == "mul") {
            char c;
            std::cin >> c;
            int reg1, reg2;
            std::cin >> reg1 >> c >> reg2;
            try {
                v[reg1] *= v[reg2];
            }
            catch (MatrixException& e) {
                std::cout << e.what();
            }
        }
        if (s == "elem") {
            char c;
            std::cin >> c;
            int reg, x, y;
            std::cin >> reg >> x >> y;
            try {
                std::cout << v[reg][x][y] << '\n';
            }
            catch (MatrixException& e) {
                std::cout << e.what();
            }
        }
    }

    return 0;
}