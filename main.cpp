#include <iostream>
#include "test.cpp"
#include "pachi/board.h"


int main(int argc, char *argv[]) {
    test();

    auto q = board();

    q.rules = RULES_JAPANESE;

    std::cout << "Hello world of Go!" << std::endl;

    return 0;
}


