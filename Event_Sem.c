#include "Event_Sem.h"

void EventSem_vInit(tstEventSem *pstEvtSem)
{
	Event_vInit(&pstEvtSem->stEvent,enEventSem);
	pstEvtSem->u8Semaphone=0;
	
}

void EventSem_vWaitSem(tstEventSem *pstEvtSem,tstTaskBlock *pstTask, uint32 u32TimeOut)
{
	if(pstEvtSem->u8Semaphone>0) 
	{
		pstEvtSem->u8Semaphone--;
	}
	else
	{
		
		Event_vWaitEvent(&pstEvtSem->stEvent,pstTask,0,Task_nState_Event_Sem,u32TimeOut);
		Task_vSched();
		
	}
}

void EventSem_vSendSem(tstEventSem *pstEvtSem,uint8 u8Num)
{
  tstNode *pstTempNode;
	tstTaskBlock *pstTask;
	
	if((pstEvtSem->u8Semaphone+=u8Num)<u8Num) return;
	//Event_vSendEvent(&pstEvtSem->stEvent);
	if(u8Num>0)
	{
		if(pstEvtSem->stEvent.stTaskList.u8NodeNum>0)
		{
		   pstTempNode=pstEvtSem->stEvent.stTaskList.stHeadNode.pstNext;
		   pstTask=GetTaskPtrByLinkNode(pstTempNode,stTaskRdyLink,tstTaskBlock);
		
		   pstTask->u32TaskState&=~(Task_nState_Event_Mask);
		   pstTask->pstEvent=NULL;
		   pstTask->pvEvtPara=(void*)0;
		   pstTask->u32EvtResult=enErr_Evt_NoError;
			
			 Event_vSendEvent(&pstEvtSem->stEvent,(void*)0, enErr_Evt_NoError);
			 pstEvtSem->u8Semaphone--;
       Task_vSched();			
		}
		else
    {
			  pstEvtSem->u8Semaphone+=u8Num;
		}
	}
	
}

