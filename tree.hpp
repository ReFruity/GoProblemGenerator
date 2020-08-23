#include <vector>
#include <iostream>

class GameTree {
private:
    int size;
    std::vector<std::vector<short>> adjacencyList;

public:
    explicit GameTree(int size);

    bool areConnected(int x, int y) const;

    void connect(int x, int y);


};

void insertInOrderedVector(std::vector<short>& orderedVector, short x);
