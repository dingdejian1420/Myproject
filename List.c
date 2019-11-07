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
		
		pstNode->pstNext=&pstList->stHeadNode;
		pstNode->pstPre=&pstList->stHeadNode;
	}
	else
  {
		pstNode->pstNext=&pstList->stHeadNode;
		pstNode->pstPre= pstList->stHeadNode.pstPre;
		
		pstList->stHeadNode.pstPre->pstNext=pstNode;
		pstList->stHeadNode.pstPre=pstNode;
	}
	pstList->u8NodeNum++;
}

tenRtnVal List_enRemoveFirstNode(tstList *pstList)
{
	tstNode *pstTemp;
	
	pstTemp=pstList->stHeadNode.pstNext;
	if((pstList->u8NodeNum==0)||(pstList->stHeadNode.pstNext==&pstList->stHeadNode))
	{
		return enErr_Empty; 
	}
	else
	{
		pstList->stHeadNode.pstNext->pstNext->pstPre=&pstList->stHeadNode;
		pstList->stHeadNode.pstNext=pstList->stHeadNode.pstNext->pstNext;		
		pstTemp->pstNext=pstTemp;
		pstTemp->pstPre=pstTemp;
		
		pstList->u8NodeNum--;
		
		return enErr_Ok;
	}
	
}

tenRtnVal List_enRemoveLastNode(tstList *pstList)
{
	tstNode *pstTemp;
	
	if((pstList->u8NodeNum==0)||(pstList->stHeadNode.pstNext==&pstList->stHeadNode))
	{
		return enErr_Empty;
	}
	else
	{
		pstList->stHeadNode.pstPre->pstPre->pstNext=&pstList->stHeadNode;
		pstList->stHeadNode.pstPre=pstList->stHeadNode.pstPre->pstPre;
		
		pstTemp->pstNext=pstTemp;
		pstTemp->pstPre=pstTemp;
		
		pstList->u8NodeNum--;
		
		return enErr_Ok;
	}
	
}

uint8 List_u8LookforSpeciNode(tstList *pstList, tstNode *pstNode)
{
	tstNode *pstTemp;
	uint8 u8Index;
	
	pstTemp=pstList->stHeadNode.pstNext;
	u8Index=1;
	if(pstList->u8NodeNum>0)
	{
		while(pstTemp!=&pstList->stHeadNode)
		{
			if(pstTemp==pstNode)
			{
				return u8Index; 
			}
			pstTemp=pstTemp->pstNext;
			u8Index++;
		}
	}
	return 0xFF;
}

tenRtnVal List_enRemoveSpeciNode(tstList *pstList, tstNode *pstNode)
{
	if(List_u8LookforSpeciNode(pstList,pstNode)==0xFF) return enErr_NoSpeciNode;
	
	pstNode->pstPre->pstNext=pstNode->pstNext;
	pstNode->pstNext->pstPre=pstNode->pstPre;
	
	pstNode->pstNext=pstNode;
	pstNode->pstPre=pstNode;
	
	return enErr_Ok;
}

tenRtnVal List_enRemoveAllNode(tstList *pstList)
{
	tstNode *pstTemp;
	
	pstTemp=&pstList->stHeadNode;
	if((pstList->u8NodeNum==0)||(pstList->stHeadNode.pstNext==&pstList->stHeadNode))
	{
		return enErr_Empty;
	}
	else
	{
		while(pstTemp->pstNext!=pstTemp)
		{
			pstTemp=pstTemp->pstNext;
			pstTemp->pstPre->pstPre=pstTemp->pstPre;
			pstTemp->pstPre->pstNext=pstTemp->pstPre;
		}
		return enErr_Ok;
	}
}

