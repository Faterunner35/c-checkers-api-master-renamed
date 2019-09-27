
#include "EngineDefine.h"
#include "CheckersGame.h"
#include "CheckersGameApi.h"

void freeBoardList(BoardList *boardList)
{
    if( boardList == NULL )
        return;

    list_board *listItems = (list_board *)boardList->content;
    if( listItems == NULL )
        return;
    
    delete listItems;
    delete boardList;
}

int getLengthOfBoard(BoardList *boardList)
{
    if( boardList == NULL )
        return 0;

    list_board *listItems = (list_board *)boardList->content;
    if( listItems == NULL )
        return 0;

    return listItems->size();
}

bool compareListBoardWithRaw(BoardList *boardList, const char rawBoard[8][8])
{
    if( boardList == NULL )
        return false;

    list_board *listItems = (list_board *)boardList->content;
    if( listItems == NULL )
        return false;

    BoardStatus boardItem = listItems->front();

    int nRet = memcmp(boardItem.status, rawBoard, 8*8*sizeof(const char));
    if( nRet == 0 )
        return true;
    else
        return false;
}

void concatBoardList(BoardList *&boardList1, BoardList *&boardList2)
{
    if( boardList2 == NULL )
        return;

	list_board *list2 = (list_board *)boardList2->content;
	if (list2 == NULL)
		return;

	if (boardList1 == NULL)
	{
		boardList1 = new BoardList();
		boardList1->content = new list_board;
	}

	list_board *list1 = (list_board *)boardList1->content;
	if (list1 == NULL)
		return;

    list1->splice(std::end(*list1), *list2);
}

void initializeBoardStatus(char status[8][8])
{
    initBoard(status);
}

static void buildBoardList(const char currentBoard[8][8], list_board *pBoardList, MoveTreeNode *parentNode)
{
    //if we dont have children we just add currentBoard to list
    if ( parentNode->children.size() == 0 )
    {
        BoardStatus newItem;
        copyBoard(newItem.status, currentBoard);
        pBoardList->push_back(newItem);
        return;
    }

    //we have to make changes on status using children nodes and recursively call current function
	list <MoveTreeNode*> listContent = parentNode->children;
	list <MoveTreeNode*> ::iterator currentItem;
	for (currentItem = listContent.begin(); currentItem != listContent.end(); ++currentItem)
	{
        char newBoard[8][8];

		MoveTreeNode *currentNode = *currentItem;

        copyBoard(newBoard, currentBoard);
        newBoard[parentNode->MoveStep.finalPos[0]][parentNode->MoveStep.finalPos[1]] = BLACK_EMPTY_FIELD;
        newBoard[currentNode->MoveStep.finalPos[0]][currentNode->MoveStep.finalPos[1]] = currentNode->MoveStep.finalStatus;
        if (currentNode->MoveStep.isJump)
        {
            newBoard[currentNode->MoveStep.posCurrent[0]][currentNode->MoveStep.posCurrent[1]] = BLACK_EMPTY_FIELD;
        }

        buildBoardList(newBoard, pBoardList, currentNode);
    }

}

BoardList* makePossibleMovesForPiece(const char initialBoardStatus[8][8], const int posStart[2])
{
	MoveTreeNode *moveTree = new MoveTreeNode;
    makeMoveTreeForPiece(initialBoardStatus, posStart, moveTree);

    if (moveTree->children.size() == 0)
    {
		freeMoveTree(moveTree);
        return NULL;
    }

    BoardList* boardList = new BoardList;
    list_board *boardListContent = new list_board();
    boardList->content = boardListContent;

    //build moveTree
    buildBoardList(initialBoardStatus, boardListContent, moveTree);

    //free allocated memory
    freeMoveTree(moveTree);

    return boardList;
}

bool checkValidOfMoving(const char initialBoardStatus[8][8],
               const int posStart[2],
               const int finalPos[2],
               const MakePossibleMovesFunc makePossibleMovesFuncPointer)
{
    //we have to check that coordinates is valid,
    //start coordinate is a piece,
    //end coordinate don't have the same color,
    if (!checkCoordinate(posStart) ||
        !checkCoordinate(finalPos) ||
        getPieceFromPos(initialBoardStatus, posStart) == BLACK_EMPTY_FIELD ||
        isBlackPiece(getPieceFromPos(initialBoardStatus, posStart)) ==
            isBlackPiece(getPieceFromPos(initialBoardStatus, finalPos)))
    {
        return false;
    }
    //second check we have to build possible moves
    //and if final position has the same color as start position then
    //we can say that move exists
    BoardList *boardList = makePossibleMovesFuncPointer(initialBoardStatus, posStart);
    if (!boardList)
    {
        return false;
    }

    bool isFound = false;

    list <BoardStatus>* listContent = (list_board *)(boardList->content);
    list <BoardStatus> :: iterator currentItem; 
    for(currentItem = listContent->begin(); currentItem != listContent->end(); ++currentItem)
    {
        if (!isFound &&
            getPieceFromPos(currentItem->status, finalPos) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceFromPos(initialBoardStatus, posStart)) ==
                isBlackPiece(getPieceFromPos(currentItem->status, finalPos)))
        {
            isFound = true;
        }
        //free allocated memory
        //free(currentItem);
    }

    return isFound;
}

//calculate checkers count
static int calculateCheckersCount(const char status[8][8], const int playerColor)
{
    int curCoord[2];
    int nCheckers = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curCoord[0] = i;
            curCoord[1] = j * 2 + i % 2;
            char currentFigure = status[curCoord[0]][curCoord[1]];
            if( (playerColor == BLACK_PLAYER && (currentFigure == BLACK_CHECKER || currentFigure == BLACK_KING)) ||
                (playerColor == WHITE_PLAYER && (currentFigure == WHITE_CHECKER || currentFigure == WHITE_KING))

            )
            {
                nCheckers++;
            }
        }
    }
    return nCheckers;
}

//calculate kings count
static int calculateKingsCount(const char status[8][8], const int playerColor)
{
    int curCoord[2];
    int kingsCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curCoord[0] = i;
            curCoord[1] = j * 2 + i % 2;
            char currentFigure = status[curCoord[0]][curCoord[1]];
            if( (playerColor == BLACK_PLAYER && (currentFigure == BLACK_KING)) ||
                (playerColor == WHITE_PLAYER && (currentFigure == WHITE_KING)))
            {
                kingsCount++;
            }
        }
    }
    return kingsCount;
}

//build game tree node, this function calls recursively
static void buildGameTreeNode(const int currentdepthOfMuves,
                               const int moveRemains,
                               const int playerColor,
                               const MakePossibleMovesFunc makePossibleMovesFuncPointer,
                               GameTreeNode *parentNode)
{
    //check current depth
    if (currentdepthOfMuves == 0)
        return;

    int nCheckers = calculateCheckersCount(parentNode->status, playerColor);

    //check loose condition
    if (nCheckers == 0)
        return;

    int enemyColor = playerColor == WHITE_PLAYER ? BLACK_PLAYER : WHITE_PLAYER;
    int enemyCheckersCount = calculateCheckersCount(parentNode->status, enemyColor);

    //check loose condition with kings
    if (moveRemains == 0 && nCheckers == 3 && enemyCheckersCount == 1)
    {
        if (calculateKingsCount(parentNode->status, playerColor) == 3 ||
            calculateKingsCount(parentNode->status, enemyColor) == 1)
        {
            return;
        }
    }

    //iterate over all pieces and try to find possible moves
    //we have to create two lists - captureBoardList, and notCaptureBoardList
    //becase we can't move if we can capture
    char currentFigure;
    int curCoord[2];
    BoardList *captureBoardList = NULL;
    BoardList *notCaptureBoardList = NULL;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            curCoord[0] = i;
            curCoord[1] = j * 2 + i % 2;
            currentFigure = parentNode->status[curCoord[0]][curCoord[1]];

            if( (playerColor == BLACK_PLAYER && (currentFigure == BLACK_CHECKER || currentFigure == BLACK_KING)) ||
                (playerColor == WHITE_PLAYER && (currentFigure == WHITE_CHECKER || currentFigure == WHITE_KING)) )
            {
                
                //get possible moves for current piece
                BoardList *currentBoardList = makePossibleMovesFuncPointer(parentNode->status, curCoord);
                if (!currentBoardList)
                    continue;

                list_board *itemList = (list_board *)currentBoardList->content;
                if( itemList == NULL || itemList->size() <= 0 )
                    continue;

                if (calculateCheckersCount(itemList->front().status, enemyColor) < enemyCheckersCount)
                {
                    concatBoardList(captureBoardList, currentBoardList);
                }
                else
                {
                    concatBoardList(notCaptureBoardList, currentBoardList);
                }

				freeBoardList(currentBoardList);
            }
        }
    }

    BoardList *boardList = NULL;
    int secondepthOfMuves = currentdepthOfMuves - 1;
    int secondMoveRemains = moveRemains;

    if (captureBoardList)
    {
        //free not captured boardlist
        freeBoardList(notCaptureBoardList);
        boardList = captureBoardList;
        secondMoveRemains = 15;
    }
    else
    {
        boardList = notCaptureBoardList;

        //check loose condition with kings
        if (nCheckers == 3 && enemyCheckersCount == 1)
        {
            if (calculateKingsCount(parentNode->status, playerColor) == 3 &&
                calculateKingsCount(parentNode->status, enemyColor) == 1)
            {
                secondMoveRemains--;
            }
        }
    }

    if( boardList != NULL )
    {
        list <BoardStatus>* listContent = (list_board *)(boardList->content);
        list <BoardStatus> :: iterator currentItem;

        if( listContent != NULL )
        {
            for(currentItem = listContent->begin(); currentItem != listContent->end(); ++currentItem)
            {
                GameTreeNode *newTreeNode = new GameTreeNode;
                copyBoard(newTreeNode->status, currentItem->status);

                parentNode->children.push_back(newTreeNode);
        
                //build game Tree
                buildGameTreeNode(secondepthOfMuves,
                                secondMoveRemains,
                                enemyColor,
                                makePossibleMovesFuncPointer,
                                newTreeNode);
            }
        }
    }
}

TreeBoard *buildGameTree(const char initialBoardStatus[8][8],
                             const int playerColor,
                             const MakePossibleMovesFunc makePossibleMovesFuncPointer,
                             const int maximumDepthOfMuves)
{
    GameTreeNode *root = new GameTreeNode;
    copyBoard(root->status, initialBoardStatus);

    // set move remains count for 3x1 king lose condition
    int moveRemains = 15;

    //build game Tree
    buildGameTreeNode(maximumDepthOfMuves,
                       moveRemains,
                       playerColor,
                       makePossibleMovesFuncPointer,
                       root);

    if (root->children.size() > 1)
    {
        return (TreeBoard *)root;
    }
    else
    {
        freeGameTree((TreeBoard*)root);
        return NULL;
    }
}