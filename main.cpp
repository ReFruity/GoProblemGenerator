#include <iostream>
#include <string>
#include "test.cpp"
#include <GoBoard.h>
#include <SgInit.h>
#include <GoInit.h>
#include <GoUctPlayer.h>
#include <SgTimeRecord.h>
#include <SpRandomPlayer.h>
#include <GoUctSearch.h>

class PerfectPlayer : GoUctPlayer<GoUctGlobalSearch<GoUctPlayoutPolicy<GoUctBoard>,
        GoUctPlayoutPolicyFactory<GoUctBoard> >,
        GoUctGlobalSearchState<GoUctPlayoutPolicy<GoUctBoard> > > {
public:
    explicit PerfectPlayer(const GoBoard& goBoard): GoUctPlayer<GoUctGlobalSearch<GoUctPlayoutPolicy<GoUctBoard>,
            GoUctPlayoutPolicyFactory<GoUctBoard> >,
            GoUctGlobalSearchState<GoUctPlayoutPolicy<GoUctBoard> > >(goBoard) {};

    SgPoint GenMove(const SgTimeRecord& time, SgBlackWhite toPlay) override {
        return 1;
    }

    std::string Name() const override {
        return "test";
    }

    void Ponder() override {

    }
};

int main(int argc, char *argv[]) {
    test();

    SgInit();
    GoInit();

    auto board = new GoBoard(9);

    auto perfectPlayer = new PerfectPlayer(*board);

    auto randomPlayer = new SpRandomPlayer(*board);

    auto time = SgTimeRecord(true, 1.);

    auto point = randomPlayer->GenMove(time, 1);

    std::cout << "Point: " << point << std::endl;

    board->Play(point, SG_BLACK);

    std::cout << "Hello world of Go!" << std::endl;

    return 0;
}


