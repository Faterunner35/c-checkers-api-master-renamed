#define CATCH_CONFIG_MAIN
#include <CheckersGameApi.h>
#include <TreeBoard.h>
#include <gtest/gtest.h>
#include <string.h>

static bool compareBoards(const char board1[8][8], const char board2[8][8])
{
    int nRet = memcmp(board1, board2, 8*8*sizeof(const char));
    if( nRet == 0 )
        return true;
    else
        return false;
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
    initializeBoardStatus(secondBoard);
    ASSERT_EQ(true, compareBoards(secondBoard, patternBoard));
}

TEST(BUILD_BOARD, CHECK)
{
    char status[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

    char secondBoard[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'#', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '1', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

    int position[2] = {2, 0};
    BoardList *boardList = makePossibleMovesForPiece(status, position);

    ASSERT_EQ(true, boardList != NULL);
    BoardList *currentItem = NULL;
    int count = getLengthOfBoard(boardList);

    ASSERT_EQ(1, count);
    ASSERT_EQ(true, compareListBoardWithRaw(boardList, secondBoard));
    freeBoardList(boardList);
}

TEST(CHECK, MOVE)
{
    char status[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7
    {
        int posStart[2] = {5, 3};
        int finalPos[2] = {3, 5};
        bool ret = checkValidOfMoving(status, posStart, finalPos, makePossibleMovesForPiece);

        ASSERT_EQ(true, ret);
    }
    {
        int posStart[2] = {5, 3};
        int finalPos[2] = {3, 1};
        bool ret = checkValidOfMoving(status, posStart, finalPos, makePossibleMovesForPiece);

        ASSERT_EQ(false, ret);
    }
}

TEST(CHECK, BUILD_GAME)
{
    {
        char status[8][8] = {
            //0    1    2    3    4    5    6    7
            {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
            {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
            {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
            {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
            {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

        TreeBoard *treeBoard = buildGameTree(status, WHITE_PLAYER, makePossibleMovesForPiece, 1);

        ASSERT_EQ(true, treeBoard != NULL);

        int count = getChildCountOfGameTree(treeBoard);

        ASSERT_EQ(7, count);
        freeGameTree(treeBoard);
    }

    {
        char status[8][8] = {
            //0    1    2    3    4    5    6    7
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //0
            {' ', '1', ' ', '#', ' ', '#', ' ', '#'},  //1
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //2
            {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
            {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

        TreeBoard *treeBoard = buildGameTree(status, WHITE_PLAYER, makePossibleMovesForPiece, 2);
        ASSERT_EQ(true, treeBoard != NULL);

        int count = getChildCountOfGameTree(treeBoard);
        ASSERT_EQ(2, count);

        TreeBoard *firstChild = getFirstChildOfTreeBoard(treeBoard);
        
        //next move must have 7 moves
        int nextCount = getChildCountOfGameTree(firstChild);

        ASSERT_EQ(7, nextCount);
        freeGameTree(treeBoard);
    }
}

// Regression: simple moves of a white piece must be accepted
// (an empty target square used to be treated as a white piece).
TEST(CHECK, WHITE_SIMPLE_MOVE)
{
    char status[8][8];
    initializeBoardStatus(status);

    int posStart[2] = {2, 0};
    int finalPos[2] = {3, 1};
    ASSERT_EQ(true, checkValidOfMoving(status, posStart, finalPos, makePossibleMovesForPiece));

    int occupied[2] = {1, 1};
    ASSERT_EQ(false, checkValidOfMoving(status, posStart, occupied, makePossibleMovesForPiece));
}

// Regression: a white king making a simple move must stay a white king
// (it used to turn into a black king).
TEST(BUILD_BOARD, WHITE_KING_SIMPLE_MOVE)
{
    char status[8][8] = {
        //0    1    2    3    4    5    6    7
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //0
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //1
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //2
        {' ', '#', ' ', '2', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //5
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //6
        {' ', '#', ' ', '#', ' ', '#', ' ', '3'}}; //7

    char afterMove[8][8];
    memcpy(afterMove, status, sizeof(afterMove));
    afterMove[3][3] = '#';
    afterMove[4][4] = '2';

    int position[2] = {3, 3};
    BoardList *boardList = makePossibleMovesForPiece(status, position);
    ASSERT_EQ(true, boardList != NULL);
    ASSERT_EQ(12, getLengthOfBoard(boardList));
    ASSERT_EQ(true, compareListBoardWithRaw(boardList, afterMove));
    freeBoardList(boardList);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}