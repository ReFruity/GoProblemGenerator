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
#include <GoUctFeatures.h>
#include <SgGameWriter.h>
#include <queue>

typedef GoUctPlayer<GoUctGlobalSearch<GoUctPlayoutPolicy<GoUctBoard>,
        GoUctPlayoutPolicyFactory<GoUctBoard> >,
        GoUctGlobalSearchState<GoUctPlayoutPolicy<GoUctBoard> > >
        PlayerType;

// TODO: Convert string to SgMove instead
SgPoint convertStringToSgPoint(std::string move) {
    std::istringstream in(move);
    SgPoint p;
    in >> SgReadPoint(p);
    return p;
}

std::string convertSgPointToString(SgPoint sgPoint) {
    return SgPointUtil::PointToString(sgPoint);
}

SgNode* importSGF(std::string inputPath) {
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

void exportSGF(SgNode *sgNode, const std::string &outputPath) {
    try
    {
        std::ofstream out(outputPath.c_str());
        SgGameWriter writer(out);
        writer.WriteGame(*(sgNode->Root()), true, 0, 1, 19);
    }
    catch (const SgException& e)
    {
        throw GtpFailure(e.what());
    }
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

GoEvalArray<float> evaluateFeatures(const GoBoard &goBoard) {
    FeFullBoardFeatures features(goBoard);
    GoUctPlayoutPolicyParam policyParam;
    GoUctPlayoutPolicy<GoBoard> policy(goBoard, policyParam);
    GoUctFeatures::FindAllFeatures(goBoard, policy, features);
    GoEvalArray<float> evalResult = features.EvaluateFeatures(FeFeatureWeights::ReadDefaultWeights());
    std::cout << "Min value: " << evalResult.MinValue() << std::endl;
    std::cout << "Max value: " << evalResult.MaxValue() << std::endl;
    return evalResult;
}

SgUctTree generateProblem(SgNode* sgNodePtr) {
    SgUctTree result;

    result.CreateAllocators(1);
    result.SetMaxNodes(5000000);

    std::vector<SgUctMoveInfo> moves {10, 20, 30};
    const SgUctNode& root = result.Root();
    result.CreateChildren(0, root, moves);

    return result;
}
GoGame* convertSgNodeToGoGame(SgNode *sgNode) {
    auto goGame = new GoGame();
    goGame->Init(sgNode);
    return goGame;
}

GoBoard* convertSgNodeToGoBoard(SgNode *sgNode) {
    auto goGamePtr = convertSgNodeToGoGame(sgNode);

    SgVector<SgPoint> blackVector;
    SgVector<SgPoint> whiteVector;

    for (GoBoard::Iterator it(goGamePtr->Board()); it; ++it)
    {
        switch (goGamePtr->Board().GetColor(*it)) {
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
        // if (goGame.Board().Occupied(*it)) {
        //     std::cout << *it << " " << convertSgPointToString(*it) << " " << std::endl;
        // }
    }

    SgPointSet blackPointSet(blackVector);
    SgPointSet whitePointSet(whiteVector);
    SgBWSet sgBWSet(blackPointSet, whitePointSet);
    // GoSetup goSetup = setupStones(sgNode);
    GoSetup goSetup;
    goSetup.m_stones = sgBWSet;
    goSetup.m_player = SG_BLACK;
    // auto goBoardPtr = convertSgNodeToGoBoard(sgNode);

    return new GoBoard(9, goSetup);
}

void generateGameTree(SgNode* root, const std::vector<std::string> &allowedMoves) {
    std::vector<SgMove> allowedSgMoves;

    allowedSgMoves.reserve(allowedMoves.size());

    for (const auto &move : allowedMoves) {
        allowedSgMoves.push_back(convertStringToSgPoint(move));
    }

    std::queue<SgNode*> queue;
    queue.push(root);
    SgBlackWhite currentPlayer = SG_BLACK;

    while (!queue.empty()) {
        std::set<SgMove> exploredMoves;
        SgNode *currentSgNode = queue.front();
        queue.pop();
        auto goBoard = convertSgNodeToGoBoard(currentSgNode);

        std::cout << *goBoard << std::endl;

        for (const auto &sgMove : allowedSgMoves) {
            if (exploredMoves.count(sgMove) > 0) {
                continue;
            }

            // goBoard->Play(sgMove);
            // bool isFirstStone = goBoard->IsFirst(sgMove);
            // bool isNewPosition = goBoard->IsNewPosition();
            // TODO: && !goBoard->CheckKo(currentPlayer)
            // if (!isFirstStone && !isNewPosition) {
            //     continue;
            // }

            exploredMoves.insert(sgMove);
            SgNode *son = currentSgNode->NewLeftMostSon();
            son->AddMoveProp(sgMove, currentPlayer);
            queue.push(son);
        }
    }
}

int main(int argc, char *argv[]) {
    SgInit();
    GoInit();

    // goBoard.Play(convertStringToSgPoint("B3"));
    // std::cout << goBoard << std::endl;

    std::string path1 = "/Users/anton/SGF/tsume-go-simple.sgf";
    std::string path2 = "/Users/anton/Projects/fuego/regression/sgf/games/pro-9x9/mz1.sgf";
    std::string path3 = "/Users/anton/SGF/test3.sgf";
    std::string path4 = "/Users/anton/SGF/classic.sgf";
    std::string outputPath = "/Users/anton/SGF/output.sgf";

    SgNode* sgNode = importSGF(path4);
    generateGameTree(sgNode, {"E5", "F5", "G5", "E4", "G4"});
    exportSGF(sgNode, outputPath);

    // auto boardSize = GoNodeUtil::GetBoardSize(sgNode);
    // std::cout << "LeftMostSon: " << sgNode->LeftMostSon() << std::endl;
    // std::cout << "Father: " << sgNode->Father() << std::endl;
    // std::cout << "boardSize: " << boardSize << std::endl;
    // std::cout << "IsTerminal: " << sgNode->IsTerminal() << std::endl;
    // std::cout << "NumSons: " << sgNode->NumSons() << std::endl;

    // while (sgNode->HasSon()) {
    //     sgNode = sgNode->NextDepthFirst();
    // }

    // SgNode* son = sgNode->NewLeftMostSon();
    // son->AddMoveProp(convertStringToSgPoint("A5"), SG_BLACK);
    // exportSGF(sgNode, outputPath);

    GoGame goGame;
    goGame.Init(sgNode);
    // std::cout << goGame.Board() << std::endl;

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
        // if (goGame.Board().Occupied(*it)) {
        //     std::cout << *it << " " << convertSgPointToString(*it) << " " << std::endl;
        // }
    }

    // auto next = sgNode->NextDepthFirst();
    // auto nextNext = next->NextDepthFirst();

    auto move1 = SgPointUtil::PointToString(184);

    // whiteVector.PushBack(convertStringToSgPoint("C7"));
    // whiteVector.PushBack(convertStringToSgPoint("G7"));
    // whiteVector.PushBack(convertStringToSgPoint("G3"));
    // whiteVector.PushBack(convertStringToSgPoint("C3"));
    SgPointSet blackPointSet(blackVector);
    SgPointSet whitePointSet(whiteVector);
    SgBWSet sgBWSet(blackPointSet, whitePointSet);
    // GoSetup goSetup = setupStones(sgNode);
    GoSetup goSetup;
    goSetup.m_stones = sgBWSet;
    goSetup.m_player = SG_BLACK;
    // auto goBoardPtr = convertSgNodeToGoBoard(sgNode);
    GoBoard goBoard(9, goSetup);

    SgUctTree problem = generateProblem(sgNode);
    auto problemRoot = problem.Root();
    auto child = problemRoot.FirstChild()->FirstChild();

    auto evaluationResult = GoBoardUtil::ScoreSimpleEndPosition(goBoard, 0.5);
    auto japaneseScore = GoBoardUtil::JapaneseScore(goBoard, 0);
    for (int i = 0; i < goBoard.CapturedStones().Length(); i++) {
        std::cout << goBoard.CapturedStones()[i] << " " << std::endl;
    }
    std::cout << "Evaluation result: " << japaneseScore << std::endl;

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

    std::cout << goBoard << std::endl;

    for (int sgMove : sequence) {
        std::cout << convertSgPointToString(sgMove) << std::endl;
        std::cout << goBoard << std::endl;
        goBoard.Play(sgMove);
    }

    std::cout << goBoard << std::endl;


    // GoGame goGame;
    // goGame.Init(sgNode);

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

