#ifndef EVENT_SEM_H
#define EVENT_SEM_H
#include "types.h"
#include "Event.h"
#include "Task.h"
#include "List.h"

typedef struct _EventSem{
	tstEvent stEvent;
	uint8 u8Semaphone;
}tstEventSem;


void EventSem_vInit(tstEventSem *pstEvtSem);

void EventSem_vWaitSem(tstEventSem *pstEvtSem,tstTaskBlock *pstTask, uint32 u32TimeOut);

void EventSem_vSendSem(tstEventSem *pstEvtSem, uint8 Num);
#endif
