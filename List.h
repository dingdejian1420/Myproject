#ifndef LIST_H
#define LIST_H
#include "types.h"
typedef enum _enReturnValue{
	enErr_Ok=0,
	enErr_Empty,
	enErr_NoSpeciNode,
	
}tenRtnVal;

typedef struct _tNode{
	struct _tNode *pstPre;
	struct _tNode *pstNext;
}tstNode;

typedef struct _tlist{
	tstNode stHeadNode;
	uint8   u8NodeNum;
}tstList;

void List_vInit(tstList *pstList);

void List_vAddNodeToFirst(tstList *pstList,tstNode *pstNode);

void List_vAddNodetoLast(tstList *pstList, tstNode *pstNode);

tenRtnVal List_enRemoveFirstNode(tstList *pstList);

tenRtnVal List_enRemoveLastNode(tstList *pstList);

uint8 List_u8LookforSpeciNode(tstList *pstList, tstNode *pstNode);

tenRtnVal List_enRemoveSpeciNode(tstList *pstList, tstNode *pstNode);

tenRtnVal List_enRemoveAllNode(tstList *pstList);
#endif
