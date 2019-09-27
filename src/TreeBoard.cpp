
#include "EngineDefine.h"

void freeGameTree(TreeBoard *treeBoard)
{
    GameTreeNode *root = (GameTreeNode *)treeBoard;
    if( root == NULL )
        return;

    list<GameTreeNode*> children = root->children;
    std::list<GameTreeNode*> :: iterator currentItem; 
    for(currentItem = children.begin(); currentItem != children.end(); ++currentItem)
    {
        freeGameTree((TreeBoard *)(*currentItem));
    }
    
    delete root;
}

GameTreeBoard* getTreeBoard(TreeBoard *treeBoard)
{
	return (GameTreeBoard*)treeBoard;
}

int getChildCountOfGameTree(TreeBoard *treeBoard)
{
    if( treeBoard == NULL )
        return 0;

    GameTreeNode *root = (GameTreeNode *)treeBoard;
    list<GameTreeNode*> children = root->children;
    
    return children.size();
}

void iterateAllNodes(TreeBoard *root, long *currentNodesCount)
{
	GameTreeNode *treeNode = (GameTreeNode*)root;
	if (root == NULL)
		return;

	list<GameTreeNode*> children = treeNode->children;
	std::list<GameTreeNode*> ::iterator currentItem;
	for (currentItem = children.begin(); currentItem != children.end(); ++currentItem)
	{
		*currentNodesCount += 1;

		iterateAllNodes((TreeBoard *)(*currentItem), currentNodesCount);
	}
}

TreeBoard* getFirstChildOfTreeBoard(TreeBoard *treeBoard)
{
    if( treeBoard == NULL )
        return NULL;

    GameTreeNode *root = (GameTreeNode *)treeBoard;
    list<GameTreeNode*> children = root->children;
    if( children.size() <= 0 )
        return NULL;
    
    return (TreeBoard *)children.front();
}