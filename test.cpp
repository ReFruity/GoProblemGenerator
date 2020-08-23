#include <iostream>
#include "board.hpp"
#include "test.hpp"
#include "tree.hpp"

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

    std::vector<short> orderedVector = { 1, 1, 2, 3, 5 };

    insertInOrderedVector(orderedVector, 1);

    assert(orderedVector == std::vector<short>({1, 1, 1, 2, 3, 5}));

    insertInOrderedVector(orderedVector, 4);

    assert(orderedVector == std::vector<short>({1, 1, 1, 2, 3, 4, 5}));

    insertInOrderedVector(orderedVector, 7);

    assert(orderedVector == std::vector<short>({1, 1, 1, 2, 3, 4, 5, 7}));

    insertInOrderedVector(orderedVector, 0);

    assert(orderedVector == std::vector<short>({0, 1, 1, 1, 2, 3, 4, 5, 7}));
}
