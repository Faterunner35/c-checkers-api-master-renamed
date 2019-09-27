#define CATCH_CONFIG_MAIN
#include <CheckersGame.h>
#include <sglib.h>
#include <gtest/gtest.h>

static bool compareBoards(const char board1[8][8], const char board2[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board1[i][j] != board2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

TEST(RESET_BOARD, EQUAL_PATTERN)
{
    char patternBoard[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    char secondBoard[8][8];
    initBoard(secondBoard);

    ASSERT_EQ(true, compareBoards(secondBoard, patternBoard));
}

static bool compareCoordinates(int c1[2], int c2[2])
{
    return (c1[0] == c2[0] && c1[1] == c2[1]);
}

TEST(CHECK, MOVE)
{
    char status[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},
        {'3', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    {
        int posStart[2] = {5, 3};

        MoveList moveList = createMoveList();

        findPossibleMoving(status, posStart, moveList);
        int count = getLengthOfMoveList(moveList);       

        ASSERT_EQ(1, count);

        int recuiredFinalPosition[2] = {3, 5};
        int requiredCapturedPosition[2] = {4, 4};

        MoveStep *fistMove = getFirstMoveOfList(moveList);

        ASSERT_EQ(true, compareCoordinates(fistMove->posCurrent, requiredCapturedPosition));
        ASSERT_EQ(true, compareCoordinates(fistMove->finalPos, recuiredFinalPosition));

        freeMoveList(moveList);
    }

    {
        int posStart[2] = {4, 4};

        MoveList moveList = createMoveList();
        
        findPossibleMoving(status, posStart, moveList);
        int count = getLengthOfMoveList(moveList);        

        ASSERT_EQ(count, 2);

        freeMoveList(moveList);
    }

    {
        int posStart[2] = {5, 1};

        MoveList moveList = createMoveList();

        findPossibleMoving(status, posStart, moveList);

        int count = getLengthOfMoveList(moveList);        

        ASSERT_EQ(count, 0);

        freeMoveList(moveList);
    }
}

TEST(CHECK_JUMPS, TREE_LIST_BUILDING)
{
    char status[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},
        {'3', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    {
        int posStart[2] = {4, 4};

        MoveTree jumpTree = createMoveTree();
        MoveStep* rootItem = getRootNodeOfTree(jumpTree);
        rootItem->finalPos[0] = posStart[0];
        rootItem->finalPos[1] = posStart[1];

        makeJumpMoveForPiece(status, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        ASSERT_EQ(count, 2);
        freeMoveTree(jumpTree);
    }

    {
        int posStart[2] = {5, 3};

        MoveTree jumpTree = createMoveTree();
        MoveStep* rootItem = getRootNodeOfTree(jumpTree);
        rootItem->finalPos[0] = posStart[0];
        rootItem->finalPos[1] = posStart[1];

        makeJumpMoveForPiece(status, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        freeMoveTree(jumpTree);

        ASSERT_EQ(count, 1);
    }
}

TEST(CHECK_SIMPLE_MOVE, TREE_LIST_BUILDING)
{
    char status[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},
        {' ', '3', ' ', '#', ' ', '#', ' ', '3'},
        {'3', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    {
        int posStart[2] = {0, 0};

        MoveTree jumpTree = createMoveTree();
        MoveStep* rootItem = getRootNodeOfTree(jumpTree);
        rootItem->finalPos[0] = posStart[0];
        rootItem->finalPos[1] = posStart[1];

        makeNotJumpMoveForNotKing(status, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        ASSERT_EQ(0, count);

        freeMoveTree(jumpTree);
    }

    {
        int posStart[2] = {2, 0};

        MoveTree jumpTree = createMoveTree();
        MoveStep* rootItem = getRootNodeOfTree(jumpTree);
        rootItem->finalPos[0] = posStart[0];
        rootItem->finalPos[1] = posStart[1];

        makeNotJumpMoveForNotKing(status, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        ASSERT_EQ(1, count);

        freeMoveTree(jumpTree);        
    }

    {
        int posStart[2] = {4, 4};

        MoveTree jumpTree = createMoveTree();
        MoveStep* rootItem = getRootNodeOfTree(jumpTree);
        rootItem->finalPos[0] = posStart[0];
        rootItem->finalPos[1] = posStart[1];

        makeNotJumpMoveForNotKing(status, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        ASSERT_EQ(2, count);

        freeMoveTree(jumpTree);
    }
}

TEST(FIND_PIECE, EMPTY_DIAGONAL_PATTERN)
{
    char status[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '3', ' ', '1', ' ', '#', ' ', '1'},  //1
        {'#', ' ', '1', ' ', '3', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},  //4
        {' ', '#', ' ', '#', ' ', '#', ' ', '3'},  //5
        {'2', ' ', '#', ' ', '2', ' ', '#', ' '},  //6
        {' ', '#', ' ', '3', ' ', '4', ' ', '3'}}; //7
    {
        int posStart[2] = {6, 0};
        int offset[2] = {-1, 1};
        int startPointOfPattern[2];
        bool ret = findEmptyPiecePattern(status,
                                                 offset,
                                                 posStart,
                                                 startPointOfPattern);

        ASSERT_EQ(true, ret);
        ASSERT_EQ(2, startPointOfPattern[0]);
        ASSERT_EQ(4, startPointOfPattern[1]);
    }

    {
        int posStart[2] = {7, 5};
        int offset[2] = {-1, -1};
        int startPointOfPattern[2];
        bool ret = findEmptyPiecePattern(status,
                                                 offset,
                                                 posStart,
                                                 startPointOfPattern);

        ASSERT_EQ(true, ret);
        ASSERT_EQ(6, startPointOfPattern[0]);
        ASSERT_EQ(4, startPointOfPattern[1]);
    }
}

TEST(GENERATE_POSSIBLE_MOVES, KINGS_WITHOUT_JUMPS)
{
    char status[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '3', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'#', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '4', ' ', '#', ' '},  //4
        {' ', '#', ' ', '#', ' ', '#', ' ', '3'},  //5
        {'2', ' ', '#', ' ', '3', ' ', '#', ' '},  //6
        {' ', '#', ' ', '3', ' ', '4', ' ', '3'}}; //7
    {
        int posStart[2] = {6, 0};

        MoveTree jumpTree = createMoveTree();
        MoveStep* rootItem = getRootNodeOfTree(jumpTree);
        rootItem->finalPos[0] = posStart[0];
        rootItem->finalPos[1] = posStart[1];

        makeMoveTreeForPiece(status, posStart, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        ASSERT_EQ(count, 4);

        freeMoveTree(jumpTree);
    }

    {
        int posStart[2] = {7, 5};

        MoveTree jumpTree = createMoveTree();

        makeMoveTreeForPiece(status, posStart, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        ASSERT_EQ(1, count);

        freeMoveTree(jumpTree);        
    }

    {
        int posStart[2] = {4, 4};

        MoveTree jumpTree = createMoveTree();

        makeMoveTreeForPiece(status, posStart, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        freeMoveTree(jumpTree);

        ASSERT_EQ(7, count);
    }
}

TEST(GENERATE_POSSIBLE_MOVES, JUMPS)
{
    char status[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '#', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '#', ' ', '1', ' ', '1'},  //1
        {'3', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '4', ' ', '1', ' '},  //4
        {' ', '#', ' ', '1', ' ', '#', ' ', '3'},  //5
        {'2', ' ', '#', ' ', '4', ' ', '#', ' '},  //6
        {' ', '#', ' ', '3', ' ', '4', ' ', '3'}}; //7
    {
        int posStart[2] = {2, 0};


        MoveTree jumpTree = createMoveTree();

        makeMoveTreeForPiece(status, posStart, jumpTree);

        int count = getChildCountOfMoveTree(jumpTree);

        freeMoveTree(jumpTree);

        ASSERT_EQ(1, count);
    }

    {
        int posStart[2] = {6, 4};

        MoveTree moveTree = createMoveTree();

        makeMoveTreeForPiece(status, posStart, moveTree);

        int count = getChildCountOfMoveTree(moveTree);

        freeMoveTree(moveTree);

        ASSERT_EQ(count, 2);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}