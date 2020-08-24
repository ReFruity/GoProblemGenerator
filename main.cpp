#include <iostream>
#include <string>
#include "test.cpp"
#include <SgSystem.h>
#include <GoBoard.h>
#include <SgInit.h>
#include <GoInit.h>
#include <GoUctPlayer.h>
#include <SgTimeRecord.h>
#include <SpRandomPlayer.h>
#include <GoUctSearch.h>
#include <GoGtpEngine.h>
#include <SgPlatform.h>
#include <GoUctCommands.h>
#include <GoUctBookBuilderCommands.h>
#include <GoSafetyCommands.h>
#include <GoUctFeatureCommands.h>
#include <GoGtpCommandUtil.h>
#include <SgStringUtil.h>

int main(int argc, char *argv[]) {
    test();

    SgInit();
    GoInit();

    GoGtpEngine engine(0, argv[0], false);
    SgRandom::SetSeed(0);
    GtpInputStream in(std::cin);
    GtpOutputStream out(std::cout);
    engine.SetMaxClearBoard(10);
    engine.MainLoop(in, out);

    return 0;
}


