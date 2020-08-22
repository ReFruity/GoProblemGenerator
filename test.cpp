#include <iostream>
#include "board.hpp"
#include "test.hpp"

void test() {
    auto goBoard = GoBoard(9);

    std::cout << goBoard << std::endl;

    assert(goBoard.get(0, 0) == Node::EMPTY);

    goBoard.set(0, 0, Node::BLACK);
    goBoard.set(1, 0, Node::BLACK);
    goBoard.set(0, 1, Node::WHITE);

    std::cout << goBoard << std::endl;

    assert(goBoard.get(0, 0) == Node::BLACK);
    assert(goBoard.get(1, 0) == Node::BLACK);
    assert(goBoard.get(0, 1) == Node::WHITE);
}
