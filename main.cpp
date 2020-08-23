#include <iostream>
#include "test.cpp"
#include "pachi/board.h"
#include "pachi/pachi.h"


int main(int argc, char *argv[]) {
    test();

    auto q = board();

    q.rules = RULES_JAPANESE;

//    pachi_main(argc, argv);

    init();

    std::cout << "Hello world of Go!" << std::endl;

    return 0;
}


