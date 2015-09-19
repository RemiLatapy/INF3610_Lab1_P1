/*
*********************************************************************************************************
*                                                 uC/OS-II
*                                          The Real-Time Kernel
*                                               PORT Windows
*
*
*            			Arnaud Desaulty, Ecole Polytechnique de Montreal, Qc, CANADA
*                                                  08/2015
*
* File : exo2.c
* 
*********************************************************************************************************
*/

// Main include of µC-II
#include "includes.h"
/*
*********************************************************************************************************
*                                              CONSTANTS
*********************************************************************************************************
*/

#define TASK_STK_SIZE       16384            // Size of each task's stacks (# of WORDs)

#define TASK1_PRIO   		4				 // Defining Priority of each task
#define TASK2_PRIO   		5
#define TASK3_PRIO   		6

#define TASK1_ID    		1                // Defining Id of each task
#define TASK2_ID    		2
#define TASK3_ID    		3

/*
*********************************************************************************************************
*                                             VARIABLES
*********************************************************************************************************
*/

OS_STK           Task1Stk[TASK_STK_SIZE];	//Stack of each task
OS_STK           Task2Stk[TASK_STK_SIZE];	
OS_STK           Task3Stk[TASK_STK_SIZE];

OS_EVENT *semaphoreA;

/*
*********************************************************************************************************
*                                           SHARED  VARIABLES
*********************************************************************************************************
*/

char printerBuffer[50] ;
int bufferPosition = -1;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void    Task1(void *data);
void    Task2(void *data);
void    Task3(void *data);

/*
*********************************************************************************************************
*                                                  MAIN
*********************************************************************************************************
*/

void main(void)
{
	// A compléter
	OSInit();

	INT8U err;
	semaphoreA = OSSemCreate(0);
	semaphoreB = OSSemCreate(0);

	if (OSTaskCreate(Task1, NULL, &Task1Stk[TASK_STK_SIZE - 1], TASK1_PRIO) != OS_ERR_NONE)
	{
		printf("error");
	}
	if(OSTaskCreate(Task2, NULL, &Task2Stk[TASK_STK_SIZE - 1], TASK2_PRIO) != OS_ERR_NONE)
	{
		printf("error");
	}
	if(OSTaskCreate(Task3, NULL, &Task3Stk[TASK_STK_SIZE - 1], TASK3_PRIO) != OS_ERR_NONE)
	{
		printf("error");
	}

	printf("End of task creation\n");
	OSStart();

}

/*
*********************************************************************************************************
*                                            TASK FUNCTIONS
*********************************************************************************************************
*/

void Task1(void* data)
{
	INT8U err = OS_ERR_NONE;
	char msg_to_send[] = "I am task 1";
	int startTime = 0;
	while (1)
	{
		printf("TACHE 1 @ %d : Debut tache 1.\n", OSTimeGet() - startTime);
		for (int i = 0; i < 11; i++)
		{
			printf("T1 : i = %d \n", i);
			++bufferPosition;
			printerBuffer[bufferPosition] = msg_to_send[i];
			OSTimeDly(3);
		}
		if (OSSemPost(semaphoreA) != OS_ERR_NONE)
		{
			printf("error while releasing semaphoreA");
		}
		printf("TACHE 1 @ %d : Suspension.\n", OSTimeGet() - startTime);
		OSTaskSuspend(TASK1_PRIO);
	}
}

void Task2(void* data)
{
	INT8U err = OS_ERR_NONE;
	char msg_to_send[] = " and i am task 2";
	int startTime = 0;
	while (1)
	{
		printf("TACHE 2 @ %d : Debut tache 2. \n", OSTimeGet() - startTime);
		OSSemPend(semaphoreA, 0, &err);
		if (err == OS_ERR_NONE)
		{
			for (int i = 0; i < 16; i++)
			{
				printf("T2 : i = %d \n", i);
				++bufferPosition;
				printerBuffer[bufferPosition] = msg_to_send[i];
				OSTimeDly(2);
			}
		}
		printf("TACHE 2 @ %d : Suspension. \n", OSTimeGet() - startTime);
		OSTaskSuspend(TASK2_PRIO);
	}
}

void Task3(void* data)
{
	int startTime = 0;
	while (1)
	{
		printf("TACHE 3 @ %d : Debut tache 3. \n", OSTimeGet() - startTime);
		OSTimeDly(70);
		printf("TACHE 3 @ %d : Fin du delay . \n", OSTimeGet() - startTime);
		++bufferPosition;
		printerBuffer[bufferPosition] = '\0';
		printf(printerBuffer);
		bufferPosition = -1;
		OSTaskSuspend(TASK3_PRIO);
	}
}


