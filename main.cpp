#include <iostream>
#include <string>
#include "test.cpp"
#include <GoUtil.h>

int main(int argc, char *argv[]) {
    test();

    std::string qwe = GoUtil::ScoreToString(1.2);

    std::cout << qwe << std::endl;

    std::cout << "Hello world of Go!" << std::endl;

    return 0;
}
