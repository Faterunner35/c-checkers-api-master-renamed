#if !defined(INCLUDED_GAMETHREE_H)
#define INCLUDED_GAMETHREE_H

typedef void* TreeBoard;

typedef struct GameTreeBoard
{
	char status[8][8];
} GameTreeBoard;

#ifdef __cplusplus
extern "C"
{
#endif

	void freeGameTree(TreeBoard *treeBoard);
    TreeBoard* getFirstChildOfTreeBoard(TreeBoard *treeBoard);

	GameTreeBoard* getTreeBoard(TreeBoard *treeBoard);
    int getChildCountOfGameTree(TreeBoard *treeBoard);
	void iterateAllNodes(TreeBoard *root, long *currentNodesCount);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_GAMETHREE_H