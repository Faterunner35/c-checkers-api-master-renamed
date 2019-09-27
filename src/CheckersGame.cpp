
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EngineDefine.h"
#include "CheckersGame.h"

MoveList createMoveList()
{
    list_move *list = new list_move;

    return (MoveList)list;
}

MoveTree createMoveTree()
{
    MoveTreeNode *node = new MoveTreeNode;

    memset(&node->MoveStep, 0, sizeof(MoveStep));

    return (MoveTree)node;
}

MoveStep* getRootNodeOfTree(MoveTree moveTree)
{
    if( moveTree == NULL )
        return NULL;

    MoveTreeNode *node = (MoveTreeNode *)moveTree;

    return &node->MoveStep;
}

int getLengthOfMoveList(MoveList moveList)
{
    list_move *list1 = (list_move *)moveList;
    if( list1 == NULL )
        return 0;

    return list1->size();
}

MoveStep* getFirstMoveOfList(MoveList moveList)
{
    list_move *list1 = (list_move *)moveList;
    if( list1 == NULL )
        return 0;

    return &list1->front();
}

void freeListMove(list_move *listMove)
{
	if (listMove == NULL)
		return;

	delete listMove;
}

void freeMoveList(MoveList moveList)
{
    list_move *list1 = (list_move *)moveList;
    if( list1 == NULL )
        return;
        
	freeListMove(list1);
}

int getChildCountOfMoveTree(MoveTree moveTree)
{
    MoveTreeNode *root = (MoveTreeNode *) moveTree;
    if( root == NULL )
        return 0;

    return root->children.size();
}

void freeMoveTree(MoveTree moveTree)
{
	MoveTreeNode *root = (MoveTreeNode *)moveTree;
	if (root == NULL)
		return;

	list<MoveTreeNode*> children = root->children;
	std::list<MoveTreeNode*> ::iterator currentItem;
	for (currentItem = children.begin(); currentItem != children.end(); ++currentItem)
	{
		MoveTreeNode *curNode = *currentItem;
		freeMoveTree((MoveTree *)curNode);
	}

	delete root;
}

//=========================================================================================//

void addToMoveTreeList(MoveTreeNode* &listMove1, MoveTreeNode* &listMove2)
{
	if (listMove2 == NULL)
		return;

	if (listMove1 == NULL)
		listMove1 = new MoveTreeNode;

	listMove1->children.push_back(listMove2);
}

//Function that check if a coordinate is in the rigth range and on a black field
bool checkCoordinate(const int position[2])
{
    //check if position in the right range
    if( position == NULL ||
        position[0] < 0 ||
        position[0] > 7 ||
        position[1] < 0 ||
        position[1] > 7 )
        return false;

    //check if position is a black field
    return (position[0] % 2 == position[1] % 2);
}

//check if checker is black
bool isBlackPiece(const char checker)
{
    return checker > '2';
};

//get checker status
static const char getFinalStatus(const char checker, int finalPos[2])
{
    if (isBlackPiece(checker))
    {
        if (checker == BLACK_KING || finalPos[0] == 0)
            return BLACK_KING;
        else
            return BLACK_CHECKER;
    }
    else
    {
        if (checker == WHITE_KING || finalPos[0] == 7)
            return WHITE_KING;
        else
            return WHITE_CHECKER;
    }
};

//set piece by type and position
static void setPieceByTypeAndPosition(char status[8][8], char type, const int position[2])
{
    status[position[0]][position[1]] = type;
}

//return piece by position
const char getPieceFromPos(const char status[8][8], const int position[2])
{
    return status[position[0]][position[1]];
}

//copy position
static void copyPosition(int destination[2], const int position[2])
{
    destination[0] = position[0];
    destination[1] = position[1];
}

//Function that copy status state to destination
void copyBoard(char destinationBoard[8][8], const char originalBoard[8][8])
{
    memcpy(destinationBoard, originalBoard, sizeof(char)*8*8);
}

//get offset
void getOffset(const int posStart[2], const int endPosition[2], int offset[2])
{
    offset[0] = endPosition[0] > posStart[0] ? 1 : -1;
    offset[1] = endPosition[1] > posStart[1] ? 1 : -1;
}

//We try to find piece-empty Pattern for kings
bool findEmptyPiecePattern(const char status[8][8],
    const int offset[2],
    const int posStart[2],
    int startPointOfPattern[2])
{
    int currentPosition[2] = {
        posStart[0] + offset[0] * 2,
        posStart[1] + offset[1] * 2};

    int posCapture[2] = {
        posStart[0] + offset[0],
        posStart[1] + offset[1]};

    while (checkCoordinate(currentPosition))
    {
        if (getPieceFromPos(status, posCapture) == BLACK_EMPTY_FIELD)
        {
            posCapture[0] += offset[0];
            posCapture[1] += offset[1];
            currentPosition[0] += offset[0];
            currentPosition[1] += offset[1];

            continue;
        }

        //check if captured position is cell with figure which hasen't the same color and second position is empty black field
        if (
            getPieceFromPos(status, currentPosition) == BLACK_EMPTY_FIELD &&
            getPieceFromPos(status, posCapture) != BLACK_EMPTY_FIELD &&
            (isBlackPiece(getPieceFromPos(status, posCapture)) !=
             isBlackPiece(getPieceFromPos(status, posStart))))
        {
            copyPosition(startPointOfPattern, posCapture);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

//we try to find all possible jumps for current position for a checker
void findPossibleMoving(const char status[8][8], const int posStart[2], MoveList moveList)
{
    list_move *list = (list_move*)moveList;
    //first is right-top
    {
        int finalPos[2] = {posStart[0] + 2,
                                posStart[1] + 2};
        int posCapture[2] = {posStart[0] + 1,
                                   posStart[1] + 1};

        if (checkCoordinate(finalPos) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD &&
            getPieceFromPos(status, posCapture) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceFromPos(status, posCapture)) != isBlackPiece(getPieceFromPos(status, posStart)))
        {
			MoveStep currentMove;
			
            copyPosition(currentMove.posCurrent, posCapture);
            copyPosition(currentMove.finalPos, finalPos);
            currentMove.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
            currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }

    //left-top
    {
        int finalPos[2] = {posStart[0] + 2,
                                posStart[1] - 2};
        int posCapture[2] = {posStart[0] + 1,
                                   posStart[1] - 1};
        if (checkCoordinate(finalPos) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD &&
            getPieceFromPos(status, posCapture) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceFromPos(status, posCapture)) != isBlackPiece(getPieceFromPos(status, posStart)))
        {
			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, posCapture);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }

    //left-bottom
    {
        int finalPos[2] = {posStart[0] - 2,
                                posStart[1] - 2};
        int posCapture[2] = {posStart[0] - 1,
                                   posStart[1] - 1};
        if (checkCoordinate(finalPos) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD &&
            getPieceFromPos(status, posCapture) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceFromPos(status, posCapture)) != isBlackPiece(getPieceFromPos(status, posStart)))
        {
			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, posCapture);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }

    //right-bottom
    {
        int finalPos[2] = {posStart[0] - 2,
                                posStart[1] + 2};
        int posCapture[2] = {posStart[0] - 1,
                                   posStart[1] + 1};
        if (checkCoordinate(finalPos) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD &&
            getPieceFromPos(status, posCapture) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceFromPos(status, posCapture)) != isBlackPiece(getPieceFromPos(status, posStart)))
        {
			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, posCapture);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }
}

// build the list of second possible king jumps
void findPossibleSecondKingJumps(const char status[8][8], const int posStart[2], const int offset[2], list_move *list)
{
    //iterate trought offset path
    int currentOffsetPosition[2];
    copyPosition(currentOffsetPosition, posStart);
    //left diagonal offset
    int leftDiagonalOffset[2] = {offset[0] * -1,
                                 offset[1]};
    //right diagonal offset
    int rightDiagonalOffset[2] = {offset[0],
                                  offset[1] * -1};
    //check all diagonal sides
    while (true)
    {
        int startPointOfPattern[2];
        //find left diagonal pattern
        if (findEmptyPiecePattern(status, leftDiagonalOffset, currentOffsetPosition, startPointOfPattern))
        {
            int finalPos[2] = {startPointOfPattern[0] + leftDiagonalOffset[0], startPointOfPattern[1] + leftDiagonalOffset[1]};
            
			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, startPointOfPattern);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getPieceFromPos(status, posStart);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }

        //find right diagonal pattern
        if (findEmptyPiecePattern(status, rightDiagonalOffset, currentOffsetPosition, startPointOfPattern))
        {
            int finalPos[2] = {startPointOfPattern[0] + rightDiagonalOffset[0], startPointOfPattern[1] + rightDiagonalOffset[1]};
            
			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, startPointOfPattern);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getPieceFromPos(status, posStart);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        if (!(checkCoordinate(currentOffsetPosition) && getPieceFromPos(status, currentOffsetPosition) == BLACK_EMPTY_FIELD))
        {
            currentOffsetPosition[0] -= offset[0];
            currentOffsetPosition[1] -= offset[1];
            break;
        }
    }

    //check last field in offset direction
    int finalPos[2] = {currentOffsetPosition[0] + offset[0], currentOffsetPosition[1] + offset[1]};

    if (checkCoordinate(finalPos) &&
        getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD &&
        getPieceFromPos(status, currentOffsetPosition) != BLACK_EMPTY_FIELD &&
        isBlackPiece(getPieceFromPos(status, currentOffsetPosition)) != isBlackPiece(getPieceFromPos(status, posStart)))
    {
		MoveStep currentMove;

		copyPosition(currentMove.posCurrent, currentOffsetPosition);
		copyPosition(currentMove.finalPos, finalPos);
		currentMove.finalStatus = getPieceFromPos(status, posStart);
		currentMove.isJump = true;

		list->push_back(currentMove);
    }
}

// build the list of first possible king jumps
void findPossibleKingFirstJumps(const char status[8][8], const int posStart[2], list_move *list)
{
    {
        //first is right-top
        int offset[2] = {1, 1};
        int startPointOfPattern[2];
        if (findEmptyPiecePattern(status, offset, posStart, startPointOfPattern))
        {
            int finalPos[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};

			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, startPointOfPattern);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getPieceFromPos(status, posStart);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }
    {
        //left-top
        int offset[2] = {1, -1};
        int startPointOfPattern[2];
        if (findEmptyPiecePattern(status, offset, posStart, startPointOfPattern))
        {
            int finalPos[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};

			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, startPointOfPattern);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getPieceFromPos(status, posStart);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }
    {
        //left-bottom
        int offset[2] = {-1, -1};
        int startPointOfPattern[2];
        if (findEmptyPiecePattern(status, offset, posStart, startPointOfPattern))
        {
            int finalPos[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};

			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, startPointOfPattern);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getPieceFromPos(status, posStart);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }
    {
        //right-bottom
        int offset[2] = {-1, 1};
        int startPointOfPattern[2];
        if (findEmptyPiecePattern(status, offset, posStart, startPointOfPattern))
        {
            int finalPos[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};

			MoveStep currentMove;

			copyPosition(currentMove.posCurrent, startPointOfPattern);
			copyPosition(currentMove.finalPos, finalPos);
			currentMove.finalStatus = getPieceFromPos(status, posStart);
			currentMove.isJump = true;

			list->push_back(currentMove);
        }
    }
}

void addToParentMoveTree(const char status[8][8], MoveTreeNode *rootNode, list_move *currentlist_move, int *posStart)
{
	if (currentlist_move == NULL)
		return;

	//recursively call buildCheckerMoveTreeList for all finded MoveStep
	list_move::iterator currentItem;
	for (currentItem = currentlist_move->begin(); currentItem != currentlist_move->end(); ++currentItem)
	{
		//MAP_ON_ELEMENT(struct list_move, currentlist_move, currentMove, next, {
		MoveStep *currentMove = &(*currentItem);

		//alloc memory for new node and set current MoveStep
		MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
		copyPosition(currentMoveTreeList->MoveStep.posCurrent, currentMove->posCurrent);
		copyPosition(currentMoveTreeList->MoveStep.finalPos, currentMove->finalPos);
		currentMoveTreeList->MoveStep.finalStatus = currentMove->finalStatus;
		currentMoveTreeList->MoveStep.isJump = true;
		currentMoveTreeList->parent = rootNode;

		//make copy of status
		char currentBoard[8][8];
		copyBoard(currentBoard, status);

		//make swap
		setPieceByTypeAndPosition(currentBoard, currentMoveTreeList->MoveStep.finalStatus, currentMoveTreeList->MoveStep.finalPos);
		setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, posStart);
		setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, currentMoveTreeList->MoveStep.posCurrent);

		//call recursively to fill children nodes;
		makeJumpMoveForPiece(currentBoard, currentMoveTreeList);

		//add currentMoveTreeList to parent MoveStep tree list
		addToMoveTreeList(rootNode, currentMoveTreeList);
	}
}

//build tree of possible jumps for the checker
void makeJumpMoveForPiece(const char status[8][8], MoveTree moveTree)
{
    MoveTreeNode *rootNode = (MoveTreeNode *)moveTree;
    int *posStart = rootNode->MoveStep.finalPos;
    //check if current piece is not king
    if (getPieceFromPos(status, posStart) == BLACK_CHECKER ||
        getPieceFromPos(status, posStart) == WHITE_CHECKER)
    {
		list_move *currentlist_move = new list_move;

		findPossibleMoving(status, posStart, currentlist_move);

		addToParentMoveTree(status, rootNode, currentlist_move, posStart);
		freeListMove(currentlist_move);
    }    //check if current piece is not king
    else //for Kings
    {
        //the rule is next:
        //if it is first jump
        //we have to check all diagonals to make jump
        //if we can we recursively call this method for next jump

        //else we have to
        //find offset direction (direct path)
        //find last empty field using offset direction
        //then we should find figure-black diagonal pattern for each pieces in (direct path)
        //if we find this pattern we have to recursively call current method
        //until second field of (direct path) isn't empty
        //then we have to check if last field is figure and second is empty
        //if yes, we recursively call current method for last field
        //after all we should check if we have jump series we only add jump series to moveTreeList
        //if not we modify last node moveTreeList

        //check if it first Jump
        if (!rootNode->parent)
        {
			list_move *currentlist_move = new list_move;
            findPossibleKingFirstJumps(status, posStart, currentlist_move);

			addToParentMoveTree(status, rootNode, currentlist_move, posStart);
			freeListMove(currentlist_move);
        } //check if it first Jump
        else
        {
            int offset[2];
            getOffset(rootNode->parent->MoveStep.finalPos, rootNode->MoveStep.finalPos, offset);
            //second jump
			list_move *currentlist_move = new list_move;
            findPossibleSecondKingJumps(status, posStart, offset, currentlist_move);

            //recursively call buildCheckerMoveTreeList for all finded MoveStep
			addToParentMoveTree(status, rootNode, currentlist_move, posStart);
			freeListMove(currentlist_move);

            //if we don't have jumps build just move forvard possibilities
            if (!currentlist_move)
            {
                //iterate trought offset path
                int currentOffsetPosition[2];
                copyPosition(currentOffsetPosition, posStart);
                currentOffsetPosition[0] += offset[0];
                currentOffsetPosition[1] += offset[1];
                while (checkCoordinate(currentOffsetPosition) && getPieceFromPos(status, currentOffsetPosition) == BLACK_EMPTY_FIELD)
                {
                    //alloc memory for new node and set current MoveStep
                    MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
                
                    copyPosition(currentMoveTreeList->MoveStep.finalPos, currentOffsetPosition);
                    currentMoveTreeList->MoveStep.finalStatus = rootNode->MoveStep.finalStatus;
                    currentMoveTreeList->MoveStep.isJump = false;
                    currentMoveTreeList->parent = rootNode->parent;

                    //add currentMoveTreeList to MoveStep tree list
					addToMoveTreeList(rootNode->parent, currentMoveTreeList);

                    //find offset
                    currentOffsetPosition[0] += offset[0];
                    currentOffsetPosition[1] += offset[1];
                }
            }
        }
    }
}

//build tree of possible simple moves for the piece without jumps
void makeNotJumpMoveForNotKing(const char status[8][8], MoveTree moveTree)
{
    MoveTreeNode *rootNode = (MoveTreeNode *)moveTree;
    int *posStart = rootNode->MoveStep.finalPos;

    //first is right-top it is only for white piece
    {
        int finalPos[2] = {posStart[0] + 1,
                                posStart[1] + 1};

        if (checkCoordinate(finalPos) &&
            !isBlackPiece(getPieceFromPos(status, posStart)) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD)
        {
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, finalPos);
            currentMoveTreeList->MoveStep.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;

			addToMoveTreeList(rootNode, currentMoveTreeList);
        }
    }

    //left-top it is only for white piece
    {
        int finalPos[2] = {posStart[0] + 1,
                                posStart[1] - 1};

        if (checkCoordinate(finalPos) &&
            !isBlackPiece(getPieceFromPos(status, posStart)) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD)
        {
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, finalPos);
            currentMoveTreeList->MoveStep.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;

			addToMoveTreeList(rootNode, currentMoveTreeList);
        }
    }

    //left-bottom it is only for black piece
    {
        int finalPos[2] = {posStart[0] - 1,
                                posStart[1] - 1};

        if (checkCoordinate(finalPos) &&
            isBlackPiece(getPieceFromPos(status, posStart)) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD)
        {
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, finalPos);
            currentMoveTreeList->MoveStep.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;

			addToMoveTreeList(rootNode, currentMoveTreeList);
        }
    }

    //right-bottom  it is only for black piece
    {
        int finalPos[2] = {posStart[0] - 1,
                                posStart[1] + 1};

        if (checkCoordinate(finalPos) &&
            isBlackPiece(getPieceFromPos(status, posStart)) &&
            getPieceFromPos(status, finalPos) == BLACK_EMPTY_FIELD)
        {
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, finalPos);
            currentMoveTreeList->MoveStep.finalStatus = getFinalStatus(getPieceFromPos(status, posStart), finalPos);
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;
            
			addToMoveTreeList(rootNode, currentMoveTreeList);
        }
    }
}

//build tree of possible simple moves for the Kings without jumps
void buildNotJumpTreeForKingPiece(const char status[8][8], MoveTreeNode *rootNode)
{
    int *posStart = rootNode->MoveStep.finalPos;

    //first is right-top it is only for white piece
    {
        int offset[2] = {1, 1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, posStart);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceFromPos(status, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, currentOffsetPosition);
            currentMoveTreeList->MoveStep.finalStatus = BLACK_KING;
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;
            
			addToMoveTreeList(rootNode, currentMoveTreeList);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }

    //left-top it is only for white piece
    {
        int offset[2] = {1, -1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, posStart);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceFromPos(status, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, currentOffsetPosition);
            currentMoveTreeList->MoveStep.finalStatus = BLACK_KING;
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;
            
			addToMoveTreeList(rootNode, currentMoveTreeList);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }

    //left-bottom it is only for black piece
    {
        int offset[2] = {-1, -1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, posStart);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceFromPos(status, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, currentOffsetPosition);
            currentMoveTreeList->MoveStep.finalStatus = BLACK_KING;
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;
            
			addToMoveTreeList(rootNode, currentMoveTreeList);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }
    //right-bottom  it is only for black piece
    {
        int offset[2] = {-1, 1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, posStart);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceFromPos(status, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeNode *currentMoveTreeList = new MoveTreeNode;
            copyPosition(currentMoveTreeList->MoveStep.finalPos, currentOffsetPosition);
            currentMoveTreeList->MoveStep.finalStatus = BLACK_KING;
            currentMoveTreeList->MoveStep.isJump = false;
			currentMoveTreeList->parent = NULL;
            
			addToMoveTreeList(rootNode, currentMoveTreeList);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }
}

void makeMoveTreeForPiece(const char initialBoardStatus[8][8],
                               const int posStart[2],
                               MoveTree moveTree)
{
    MoveTreeNode *rootNode = (MoveTreeNode *)moveTree;
    //set first node of tree
    copyPosition(rootNode->MoveStep.finalPos, posStart);
    rootNode->MoveStep.finalStatus = getPieceFromPos(initialBoardStatus, posStart);
    rootNode->MoveStep.isJump = false;
    rootNode->parent = NULL;
    //first try to build jump tree list
    makeJumpMoveForPiece(initialBoardStatus, rootNode);

    // second try to build move list if we don't have jumps
    if (rootNode->children.size() == 0)
    {
        //check if current piece is checker
        if (getPieceFromPos(initialBoardStatus, posStart) == BLACK_CHECKER ||
            getPieceFromPos(initialBoardStatus, posStart) == WHITE_CHECKER)
        {
            makeNotJumpMoveForNotKing(initialBoardStatus, rootNode);
        }
        else
        {
            //if current piece is king;
            buildNotJumpTreeForKingPiece(initialBoardStatus, rootNode);
        }
    }
}

void initBoard(char status[8][8])
{

	int i = 0, j = 0;

    //fill status with white fields
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 4; j++)
        {
            status[i][j * 2 + 1 - i % 2] = WHITE_FIELD;
        }
    }

    //fill status with white chekers
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            status[i][j * 2 + i % 2] = WHITE_CHECKER;
        }
    }

    //fill status with Black Fields
    for (i = 3; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            status[i][j * 2 + i % 2] = BLACK_EMPTY_FIELD;
        }
    }

    //fill status with black chekers
    for (i = 5; i < 8; i++)
    {
        for (j = 0; j < 4; j++)
        {
            status[i][j * 2 + i % 2] = BLACK_CHECKER;
        }
    }
}
