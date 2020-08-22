#include <iostream>
#include <string>
#include <vector>

#include "test.hpp"
#include "board.hpp"

int main(int argc, char *argv[]) {
    test();

    auto goBoard = GoBoard(9);

    std::cout << goBoard << std::endl;

    return 0;
}
