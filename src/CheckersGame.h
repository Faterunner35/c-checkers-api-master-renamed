
#ifndef __CHECKERS_GAME_HEADER_
#define __CHECKERS_GAME_HEADER_

#include <stdbool.h>

#include "TreeBoard.h"
#include "Player.h"
#include "Checker.h"

typedef struct MoveStep
{
	bool    isJump;
	int     finalPos[2];
	int     posCurrent[2];
	char    finalStatus;
} MoveStep;

typedef void* MoveList;
typedef void* MoveTree;

#ifdef __cplusplus
extern "C"
{
#endif

    MoveList    createMoveList();
    void        freeMoveList(MoveList moveList);
    int         getLengthOfMoveList(MoveList list);
    MoveStep*   getFirstMoveOfList(MoveList list);

    MoveTree    createMoveTree();
    MoveStep*   getRootNodeOfTree(MoveTree moveTree);
    int         getChildCountOfMoveTree(MoveTree moveTree);
    void        freeMoveTree(MoveTree moveTreeList);

    //Function that check if a coordinate is in the rigth range and on a black field
    bool        checkCoordinate(const int position[2]);

    //check if checker is black
    bool        isBlackPiece(const char checker);

    //return piece by position
    const char  getPieceFromPos(const char status[8][8], const int position[2]);

    //The function that finds all possible moves from current position for a checker
    void        findPossibleMoving(const char status[8][8], const int posStart[2], MoveList list);

    //The function that builds MoveStep Tree List for current piece
    void        makeJumpMoveForPiece(const char status[8][8], MoveTree rootNode);

    //The function  that generates the move tree for a piece
    void        makeMoveTreeForPiece(const char initialBoardStatus[8][8],
                    const int posStart[2],
                    MoveTree rootNode);

    //We try to find piece-empty Pattern for kings
    bool        findEmptyPiecePattern(const char status[8][8],
                    const int offset[2],
                    const int posStart[2],
                    int startPointOfPattern[2]);

    //The function that can reset status state to inintial state
    void        initBoard(char status[8][8]);

    //build tree of possible simple moves for the piece without jumps
    void        makeNotJumpMoveForNotKing(const char status[8][8], MoveTree rootNode);

    //Function that copy status state to destination
    void        copyBoard(char destinationBoard[8][8], const char originalBoard[8][8]);

#ifdef __cplusplus
}
#endif

#endif // __CHECKERS_GAME_HEADER_