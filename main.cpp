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
#include <GoGtpEngine.h>

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

    auto engine = new GoGtpEngine(0, 0, false, false);

    const auto& game = engine->Game();

    std::cout << "Current move: " << game.CurrentMove() << std::endl;
    std::cout << "Game result: " << game.GetResult() << std::endl;

    auto board = new GoBoard(9);

    auto perfectPlayer = new PerfectPlayer(*board);

    auto time = SgTimeRecord(true, 1.);

    auto point = perfectPlayer->GenMove(time, 1);

    std::cout << "Point: " << point << std::endl;

    board->Play(point, SG_BLACK);

    std::cout << "Hello world of Go!" << std::endl;

    GoFini();
    SgFini();

    return 0;
}


