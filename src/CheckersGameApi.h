#if !defined(INCLUDED_CHECKERSGAMEAPI)
#define INCLUDED_CHECKERSGAMEAPI

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "TreeBoard.h"
#include "Player.h"
#include "Checker.h"

#ifdef __cplusplus
extern "C"
{
#endif

    //status list structure
    typedef struct BoardList
    {
        void *content;
    } BoardList;

    typedef BoardList *(*MakePossibleMovesFunc)(const char initialBoardStatus[8][8],
                                                                   const int posStart[2]);

    typedef bool (*CheckMoveFunction)(const char initialBoardStatus[8][8],
        const int posStart[2],
        const int finalPos[2],
        const MakePossibleMovesFunc *makePossibleMovesFuncPointer);

    void    freeBoardList(BoardList *boardList);
    int     getLengthOfBoard(BoardList *boardList);
    bool    compareListBoardWithRaw(BoardList *boardList, const char board2[8][8]);

    //The function that can determine if a move is valid
    bool    checkValidOfMoving(const char initialBoardStatus[8][8],
                const int posStart[2],
                const int finalPos[2],
                const MakePossibleMovesFunc makePossibleMovesFuncPointer);

    //The function that  generates the possible moves for a piece
    BoardList* makePossibleMovesForPiece(const char initialBoardStatus[8][8],
                                                const int posStart[2]);

    //The function that generates all the possible moves that can be
    //played up to a specified number of moves.
    TreeBoard* buildGameTree(const char initialBoardStatus[8][8],
                const int playerColor,
                const MakePossibleMovesFunc makePossibleMovesFuncPointer,
                const int maximumDepthOfMuves);

    //The function that reset status to initial state
    void        initializeBoardStatus(char status[8][8]);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_CHECKERSGAMEAPI
