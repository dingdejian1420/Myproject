#include "Event_Mutex.h"

void EventMutex_vInit(tstEventMutex *pstEvtMtx)
{
	pstEvtMtx->boLocked=True;
	Event_vInit(&pstEvtMtx->stEvent,enEventMutex);
}

void EventMutex_vWaitEvent(tstEventMutex *pstEvtMtx,tstTaskBlock *pstTask, uint32 u32TimeOut)
{
		pstTask->pstEvent=&pstEvtMtx->stEvent;
		pstTask->pvEvtPara=(void*)0;
		pstTask->u32EvtResult=enErr_Evt_NoError;
		pstTask->u32TaskState|=Task_nState_Event_Murex;
	
	if(pstEvtMtx->boLocked==False)
	{
		pstEvtMtx->boLocked=True;
		return;
	}
	else
	{	
		Event_vWaitEvent(&pstEvtMtx->stEvent,pstTask,(void*)0,Task_nState_Event_Murex,u32TimeOut);
		Task_vSched();
	}
	
}


void EventMutex_vSendEvent(tstEventMutex *pstEvtMtx)
{
	tstTaskBlock *pstTask;
	tstNode *pstNode;
	
	if(pstEvtMtx->stEvent.stTaskList.u8NodeNum>0)
	{
	  pstNode=pstEvtMtx->stEvent.stTaskList.stHeadNode.pstNext;
		pstTask=GetTaskPtrByLinkNode(pstNode,stTaskRdyLink,tstTaskBlock);
		
		pstTask->pstEvent=NULL;
		pstTask->pvEvtPara=0;
		pstTask->u32EvtResult=enErr_Evt_NoError;
		pstTask->u32TaskState&=~(Task_nState_Event_Murex);
		
		Event_vSendEvent(&pstEvtMtx->stEvent,0,enErr_Evt_NoError);
    Task_vSched();		
	}
	else
	{
		pstEvtMtx->boLocked=False;
	}
}
