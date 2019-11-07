#ifndef TASK_H
#include "types.h"
#include "List.h"

typedef void (*tfEnteryFun)(void *para);

typedef struct _TaskBlock{
	void *pStackPointer;
	uint8 u8Prio;//0-31
	tfEnteryFun fEnterFun;
	tstNode stTaskDelayLink;
	tstNode stTaskRdyLink;
	
	uint32 u32TaskTick;
}tstTaskBlock;

#define RTOS_TASK_MAX_PRIO 32


void Task_vSetRdyTable(uint8 u8Prio);
void Task_vClrRdyTable(uint8 u8Prio);
uint8 Task_GetHighestPrioIndex(void);
void Task_vInit(tstTaskBlock *pstTask, void *pvStackPointer, tfEnteryFun fEnterFun, uint8 u8Prio);
void Task_vInitTaskRdyList(void);
#define TASK_H
#endif
