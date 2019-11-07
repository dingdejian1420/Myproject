#include "Task.h"
#include "List.h"
#include "types.h"

tstTaskBlock Task1;
tstTaskBlock Task2;
tstTaskBlock Task3;
tstTaskBlock Task4;
uint8 Task1_Stack[1024];
uint8 Task2_Stack[512];
uint8 Task3_Stack[256];
uint8 Task4_Stack[128];

void TaskFunction1(void)
{
}
void TaskFunction2(void)
{
}
void TaskFunction3(void)
{
}
void TaskFunction4(void)
{
}
int main()
{
	Task_vInitTaskRdyList();
	
	Task_vInit(&Task1,&Task1_Stack[1024],(void*)TaskFunction1,0);
	Task_vInit(&Task2,&Task2_Stack[512],(void*)TaskFunction2,0);
	Task_vInit(&Task3,&Task3_Stack[256],(void*)TaskFunction3,2);
	Task_vInit(&Task4,&Task4_Stack[128],(void*)TaskFunction4,0);
}
