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
* File : exo3.c
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

#define TANK_A_PRIO   		6				 // Defining Priority of each task
#define TANK_B_PRIO   		5
#define CONTROLLER_PRIO     4
#define MIXER_PRIO			7

#define TANK_A_ID    		1                // Defining Id of each task
#define TANK_B_ID    		2
#define CONTROLLER_ID    	3
#define MIXER_ID    		4

/*
*********************************************************************************************************
*                                             VARIABLES
*********************************************************************************************************
*/

OS_STK           tankAStk[TASK_STK_SIZE];	//Stack of each task
OS_STK           tankBStk[TASK_STK_SIZE];	
OS_STK           mixerStk[TASK_STK_SIZE];
OS_STK           controllerStk[TASK_STK_SIZE];

/*
*********************************************************************************************************
*                                           SHARED  VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void    tank_A(void *data);
void    tank_B(void *data);
void    mixer(void *data);
void    controller(void *data);
void    errMsg(INT8U err, char* errMSg);

/*
*********************************************************************************************************
*                                             STRUCTURES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                  MAIN
*********************************************************************************************************
*/

void main(void)
{
	UBYTE err;

	// à compléter
	
    return;
}

/*
*********************************************************************************************************
*                                            TASK FUNCTIONS
*********************************************************************************************************
*/


void tank_A(void* data)
{
	INT8U err;
	int startTime = 0;
	int orderNumber = 1;
	int *quantity;
	printf("TACHE TANK A @ %d : DEBUT.\n", OSTimeGet() - startTime);
	while (1)
	{

		printf("TACHE TANK A COMMANDE #%d @ %d : Déversage composant A.\n", orderNumber, OSTimeGet() - startTime);
		OSTimeDly(*quantity);
		printf("TACHE TANK A COMMANDE #%d @ %d : fin déversage composant A.\n", orderNumber, OSTimeGet() - startTime);

		orderNumber++;
	}

}

void tank_B(void* data)
{
	INT8U err;
	int startTime = 0;
	int orderNumber = 1;
	int *quantity;
	printf("TACHE TANK B @ %d : DEBUT. \n", OSTimeGet() - startTime);
	while (1)
	{

		printf("TACHE TANK B COMMANDE #%d @ %d : Déversage composant B.\n", orderNumber, OSTimeGet() - startTime);
		OSTimeDly(*quantity);
		printf("TACHE TANK B COMMANDE #%d @ %d : Fin déversage composant B.\n", orderNumber, OSTimeGet() - startTime);

		orderNumber++;
	}
}
void mixer(void* data)
{
	INT8U err;
	int startTime = 0;
	int orderNumber = 1;
	int *time;
	printf("TACHE MIXER @ %d : DEBUT. \n", OSTimeGet() - startTime);
	while (1)
	{

		printf("TACHE MIXER COMMANDE #%d @ %d : Début malaxage.\n", orderNumber, OSTimeGet() - startTime);
		OSTimeDly(*time);
		printf("TACHE MIXER COMMANDE #%d @ %d : Fin malaxage et déversage.\n", orderNumber, OSTimeGet() - startTime);

		orderNumber++;

	}
}
void controller(void* data)
{
	INT8U err;
	int startTime = 0;
	int randomTime = 0;
	int *a_quantity;
	int *b_quantity;
	int *mixer_time;
	printf("TACHE CONTROLLER @ %d : DEBUT. \n", OSTimeGet() - startTime);
	for(int i = 1 ; i < 11; i++)
	{	
		//Création d'une commande
		a_quantity = malloc(sizeof(int));
		b_quantity = malloc(sizeof(int));
		mixer_time = malloc(sizeof(int));

		*a_quantity = (rand() % 10 + 2)*100;
		*b_quantity = (rand() % 13 + 5)*100;
		*mixer_time = (rand() % 10 + 7)*100;

		printf("TACHE CONTROLLER @ %d : COMMANDE #%d. \n A = %d, B = %d, MixTime = %d\n", OSTimeGet() - startTime, i, *a_quantity, *b_quantity, *mixer_time);

		// à compléter
		
		// Délai aléatoire avant nouvelle commande
		randomTime = (rand() % 10 + 5)*100;
		OSTimeDly(randomTime);

		

	}
}
void errMsg(INT8U err, char* errMsg)
{
	if (err != OS_ERR_NONE)
	{
		printf(errMsg);
		exit(1);
	}
}


