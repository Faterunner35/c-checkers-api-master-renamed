
#if !defined(__ENGINE_DEFINE_HEADER_)
#define __ENGINE_DEFINE_HEADER_

#include <iostream>
#include <string.h>
#include <list>
#include <iterator>

#include "CheckersGameApi.h"
#include "CheckersGame.h"

using namespace std;

typedef struct BoardStatus
{
    char status[8][8];
} BoardStatus;

typedef list<BoardStatus> list_board;

typedef struct GameTreeNode
{
    char status[8][8];
    list<GameTreeNode*> children;   // down level nodes
} GameTreeNode;

typedef list<MoveStep> list_move;

typedef struct MoveTreeNode
{
	struct MoveStep MoveStep;
	struct MoveTreeNode *parent;
	list<MoveTreeNode*> children;   // down level nodes
} MoveTreeNode;

#endif // __ENGINE_DEFINE_HEADER_