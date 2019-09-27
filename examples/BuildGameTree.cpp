#include "CheckersGameApi.h"
#include <stdio.h>
#include <stdlib.h>

static void printBoardStatus(char status[8][8])
{
	printf(" |A|B|C|D|E|F|G|H|\n");

	for (int i = 7; i >= 0; i--)
	{
		printf("%d", 8 - i);
		for (int j = 0; j < 8; j++)
		{
			printf("|%c", status[i][j]);
		}
		printf("|\n");
	}
}

int main(int argc, char *argv[])
{
	char status[8][8];

	initializeBoardStatus(status);

	int maximumDepthofMoves = 7;
	printf("maximum depth of moves: %d\n", maximumDepthofMoves);

	TreeBoard *treeBoard = buildGameTree(status, BLACK_PLAYER, makePossibleMovesForPiece, maximumDepthofMoves);

	if (!treeBoard)
	{
		printf("I can't build treeBoard\n");
		return 0;
	}

	//print some branch
	int currentStep = 1;
	TreeBoard *curTreeBoard = treeBoard;
	printf("initial state:\n");
	
	while (true)
	{
		printBoardStatus(getTreeBoard(curTreeBoard)->status);
		curTreeBoard = getFirstChildOfTreeBoard(curTreeBoard);
		if (!curTreeBoard )
		{
			break;
		}

		printf("Step: %d\n", currentStep);
		currentStep++;
	}

	long nodesCount = 1;
	iterateAllNodes(treeBoard, &nodesCount);

	printf("Total nodes in game three: %ld\n", nodesCount);

	freeGameTree(treeBoard);

}