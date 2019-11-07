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
