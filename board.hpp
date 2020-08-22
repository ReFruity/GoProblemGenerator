#include <vector>
#include <iostream>

enum Node {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

class GoBoard {
private:
    int size;
    std::vector<Node> board;

public:
    explicit GoBoard(int size);

    Node get(int x, int y) const;

    int getSize() const;
};

std::ostream& operator<<(std::ostream& strm, const GoBoard& goBoard);
