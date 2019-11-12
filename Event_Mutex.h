#ifndef EVENT_MUTEX_H
#define EVENT_MUTEX_H
#include "types.h"
#include "Event.h"
#include "Task.h"

typedef struct _EventMutex{
	tstEvent stEvent;
	bool boLocked;
}tstEventMutex;


void EventMutex_vInit(tstEventMutex *pstEvtMtx);

void EventMutex_vWaitEvent(tstEventMutex *pstEvtMtx,tstTaskBlock *pstTask, uint32 u32TimeOut);

void EventMutex_vSendEvent(tstEventMutex *pstEvtMtx);
#endif
