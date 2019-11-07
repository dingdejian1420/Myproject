#include "list.h"
#include "types.h"

void List_vInit(tstList *pstList)
{
	pstList->stHeadNode.pstNext=&pstList->stHeadNode;
	pstList->stHeadNode.pstPre=&pstList->stHeadNode;
	pstList->u8NodeNum=0;
}
void List_vAddNodeToFirst(tstList *pstList,tstNode *pstNode)
{
	if((pstList->u8NodeNum==0)||(pstList->stHeadNode.pstNext==&pstList->stHeadNode))
	{
		pstList->stHeadNode.pstNext=pstNode;
		pstList->stHeadNode.pstPre=pstNode;
		
		pstNode->pstPre=&pstList->stHeadNode;
		pstNode->pstNext=&pstList->stHeadNode;
	}
	else
	{
		pstNode->pstPre=&pstList->stHeadNode;
		pstNode->pstNext=pstList->stHeadNode.pstNext;
		
		pstList->stHeadNode.pstNext->pstPre=pstNode;
		pstList->stHeadNode.pstNext=pstNode;
		
	}
	pstList->u8NodeNum++;
}

void List_vAddNodetoLast(tstList *pstList, tstNode *pstNode)
{
	if((pstList->u8NodeNum==0)||(pstList->stHeadNode.pstNext==&pstList->stHeadNode))
	{
		pstList->stHeadNode.pstNext=pstNode;
		pstList->stHeadNode.pstPre=pstNode;
		
		ps
