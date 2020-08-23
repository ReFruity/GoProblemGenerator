#include "tree.hpp"

GameTree::GameTree(int size) {
    this->size = size;
    this->adjacencyList = std::vector<std::vector<short>>(size, std::vector<short>());
}

bool GameTree::areConnected(int x, int y) const {
    auto list = this->adjacencyList[x];
    return std::binary_search(list.begin(), list.end(), y);
}

void insertInOrderedVector(std::vector<short>& orderedVector, int x) {
    auto iterator = std::lower_bound(orderedVector.begin(), orderedVector.end(), x);
    orderedVector.insert(iterator, x);
}

void GameTree::connect(int x, int y) {
    auto orderedVector = this->adjacencyList[x];
    insertInOrderedVector(orderedVector, y);
}


