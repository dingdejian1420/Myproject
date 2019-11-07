#include "Task.h"

uint8 const First1MapTbl[256]={
    0,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
};
uint32 Task_u32RdyTable;//


tstList Task_apstTaskList[RTOS_TASK_MAX_PRIO];//

void Task_vSetRdyTable(uint8 u8Prio)
{
	if(u8Prio>=RTOS_TASK_MAX_PRIO) return;
	Task_u32RdyTable|=(1<<u8Prio);
}

void Task_vClrRdyTable(uint8 u8Prio)
{
	if(u8Prio>=RTOS_TASK_MAX_PRIO) return;
	Task_u32RdyTable&=!(1<<u8Prio);
}

uint8 Task_GetHighestPrioIndex(void)
{
	uint8 u8First1Index;
	if(Task_u32RdyTable&0xFF)
	{
		u8First1Index=First1MapTbl[Task_u32RdyTable&0xFF];
	}
	else if(Task_u32RdyTable&0xFF00)
	{
		u8First1Index=First1MapTbl[(Task_u32RdyTable&0xFF00)>>8]+7;
	}
	else if(Task_u32RdyTable&0xFF0000)
	{
		u8First1Index=First1MapTbl[(Task_u32RdyTable&0xFF0000)>>16]+7+8;
	}
	else if(Task_u32RdyTable&0xFF000000)
	{
		u8First1Index=First1MapTbl[(Task_u32RdyTable&0xFF000000)>>24]+7+8+8;
	}
	else
	{
		return 0xFF;//error
	}
		
	return u8First1Index;
}

void Task_vInit(tstTaskBlock *pstTask, void *pvStackPointer, tfEnteryFun fEnterFun, uint8 u8Prio)
{
	pstTask->fEnterFun=fEnterFun;
	pstTask->pStackPointer=pvStackPointer;
	pstTask->u32TaskTick=0;
	pstTask->u8Prio=u8Prio;
	
	pstTask->stTaskDelayLink.pstNext=&pstTask->stTaskDelayLink;
	pstTask->stTaskDelayLink.pstPre=&pstTask->stTaskDelayLink;
	pstTask->stTaskRdyLink.pstNext=&pstTask->stTaskRdyLink;
	pstTask->stTaskRdyLink.pstPre=&pstTask->stTaskRdyLink;
	
	Task_vSetRdyTable(pstTask->u8Prio);
	List_vAddNodeToFirst(&Task_apstTaskList[pstTask->u8Prio],&pstTask->stTaskRdyLink);
	
}

void Task_vInitTaskRdyList(void)
{
	uint8 u8i;
	for(u8i=0;u8i<RTOS_TASK_MAX_PRIO;u8i++)
	{
		Task_apstTaskList[u8i].u8NodeNum=0;
		Task_apstTaskList[u8i].stHeadNode.pstNext=&Task_apstTaskList[u8i].stHeadNode;
		Task_apstTaskList[u8i].stHeadNode.pstPre=&Task_apstTaskList[u8i].stHeadNode;
	}
}
