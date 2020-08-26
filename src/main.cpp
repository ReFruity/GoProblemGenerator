#include <iostream>
#include <string>
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
#include <GoNodeUtil.h>

typedef GoUctPlayer<GoUctGlobalSearch<GoUctPlayoutPolicy<GoUctBoard>,
        GoUctPlayoutPolicyFactory<GoUctBoard> >,
        GoUctGlobalSearchState<GoUctPlayoutPolicy<GoUctBoard> > >
        PlayerType;

SgPoint convertStringToSgPoint(std::string move) {
    std::istringstream in(move);
    SgPoint p;
    in >> SgReadPoint(p);
    return p;
}

std::string convertSgPointToString(SgPoint sgPoint) {
    return SgPointUtil::PointToString(sgPoint);
}

SgNode* loadSGF(std::string inputPath) {
    std::ifstream in(inputPath.c_str());
    if (!in) {
        throw GtpFailure("could not open file");
    }
    SgGameReader reader(in);
    SgNode* root = reader.ReadGame();
    if (root == nullptr) {
        throw GtpFailure("no games in file");
    }
    return root;
}

GoBoard* convertSgNodeToGoBoard(SgNode *sgNode) {
    auto result = new GoBoard(9);

    return result;
}

GoSetup setupStones(SgNode *sgNode) {
    SgNode* current = sgNode;
    while (current->NumSons() > 0) {
        SgPropList& props = current->Props();
        auto p15 = props.Get(15);
        auto p106 = props.Get(106);
        auto p107 = props.Get(107);
        current = current->NextDepthFirst();
    }
    return GoSetup();
}

int main(int argc, char *argv[]) {
    SgInit();
    GoInit();

    // goBoard.Play(convertStringToSgPoint("B3"));
    // std::cout << goBoard << std::endl;

    SgNode *root = loadSGF("/Users/anton/SGF/test.sgf");
    // auto boardSize = GoNodeUtil::GetBoardSize(root);
    // std::cout << "LeftMostSon: " << root->LeftMostSon() << std::endl;
    // std::cout << "Father: " << root->Father() << std::endl;
    // std::cout << "boardSize: " << boardSize << std::endl;
    // std::cout << "IsTerminal: " << root->IsTerminal() << std::endl;
    // std::cout << "NumSons: " << root->NumSons() << std::endl;

    while (root->HasSon()) {
        root = root->NextDepthFirst();
    }

    GoGame goGame;
    goGame.Init(root);
    std::cout << goGame.Board() << std::endl;

    SgVector<SgPoint> blackVector;
    SgVector<SgPoint> whiteVector;

    for (GoBoard::Iterator it(goGame.Board()); it; ++it)
    {
        switch (goGame.Board().GetColor(*it)) {
            case SG_BLACK:
                blackVector.PushBack(*it);
                break;
            case SG_WHITE:
                whiteVector.PushBack(*it);
                break;
            case SG_EMPTY:
                break;
            default:
                throw;
        }
        if (goGame.Board().Occupied(*it)) {
            std::cout << *it << " " << convertSgPointToString(*it) << " " << std::endl;
        }
    }


    auto next = root->NextDepthFirst();
    auto nextNext = next->NextDepthFirst();

    auto move1 = SgPointUtil::PointToString(143);

    // whiteVector.PushBack(convertStringToSgPoint("C7"));
    // whiteVector.PushBack(convertStringToSgPoint("G7"));
    // whiteVector.PushBack(convertStringToSgPoint("G3"));
    // whiteVector.PushBack(convertStringToSgPoint("C3"));
    SgPointSet blackPointSet(blackVector);
    SgPointSet whitePointSet(whiteVector);
    SgBWSet sgBWSet(blackPointSet, whitePointSet);
    GoSetup goSetup = setupStones(root);
    goSetup.m_stones = sgBWSet;
    auto goBoardPtr = convertSgNodeToGoBoard(root);
    GoBoard goBoard(9, goSetup);

    GoUctGlobalSearch<GoUctPlayoutPolicy<GoUctBoard>,
            GoUctPlayoutPolicyFactory<GoUctBoard>> goUctGlobalSearch(
                    goBoard,
                    new GoUctPlayoutPolicyFactory<GoUctBoard>(GoUctPlayoutPolicyParam()),
                    GoUctPlayoutPolicyParam(),
                    GoUctDefaultMoveFilterParam(),
                    GoUctFeatureKnowledgeParam()
    );

    int maxGames = 1e5;
    double maxTime = 10;
    std::vector<SgMove> sequence;
    const std::vector<SgMove> rootFilter;
    SgUctTree *initTree = &goUctGlobalSearch.GetTempTree();
    // const auto initTree = new SgUctTree();
    // SgUctMoveInfo sgUctMoveInfo {
    //     1, 1, 1, 1, 1
    // };
    //
    // SgUctNode sgUctNode(sgUctMoveInfo);
    // std::vector<SgMove> moves;
    // initTree->SetChildren(9, sgUctNode, moves);
    auto param = new SgUctEarlyAbortParam {
        0.8, 5000, 3
    };
    goUctGlobalSearch.Search(maxGames, maxTime, sequence, rootFilter, initTree, param);

    for (int sgMove : sequence) {
        std::cout << convertSgPointToString(sgMove) << std::endl;
        std::cout << goBoard << std::endl;
        goBoard.Play(sgMove);
    }

    std::cout << goBoard << std::endl;

    // GoGame goGame;
    // goGame.Init(root);

    // GoGtpEngine engine(9, argv[0], false);
    // GoGtpAssertionHandler assertionHandler(engine);
    // engine.SetPlayer(new PlayerType(engine.Board()));

    // SgVector<SgPoint> blackVector;
    // blackVector.PushBack(convertStringToSgPoint("D5"));
    // SgVector<SgPoint> whiteVector;
    // SgPointSet blackPointSet(blackVector);
    // SgPointSet whitePointSet(whiteVector);
    // SgBWSet sgBWSet(blackPointSet, whitePointSet);
    // GoSetup goSetup;
    // goSetup.m_stones = sgBWSet;

    // engine.ExecuteCommand("loadsgf /Users/anton/SGF/test2.sgf");
    // engine.ExecuteCommand("genmove w");
    // engine.ExecuteCommand("showboard", std::cout);

    // std::cout << engine.Board() << std::endl;
    // engine.Player().Board().Init(9, goSetup);
    // std::ifstream fileIn("input.txt");
    // GtpInputStream in(fileIn);
    // GtpInputStream in(std::cin);
    // GtpOutputStream out(std::cout);

    // engine.MainLoop(in, out);

    return 0;
}

