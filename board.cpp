#include "board.hpp"

GoBoard::GoBoard(int size) {
    this->size = size;
    this->board = std::vector<Node>(size * size, EMPTY);
}

int GoBoard::getSize() const {
    return this->size;
}

Node GoBoard::get(int x, int y) const {
    return board[x * size + y];
}

void GoBoard::set(int x, int y, Node node) {
    this->board[x * this->size + y] = node;
}

std::ostream& operator<<(std::ostream& strm, const GoBoard& goBoard) {
    for(int i = 0; i < goBoard.getSize(); i++) {
        for(int j = 0; j < goBoard.getSize(); j++) {
            strm << goBoard.get(i, j) << " ";
        }

        strm << std::endl;
    }

    return strm;
}
