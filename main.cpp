#include <iostream>
#include <string>
#include "test.cpp"
#include <GoBoard.h>
#include <SgInit.h>
#include <GoInit.h>

int main(int argc, char *argv[]) {
    test();

    SgInit();
    GoInit();

    auto board = new GoBoard(9);

    board->Play({1, 1});

    std::cout << "Hello world of Go!" << std::endl;

    return 0;
}
