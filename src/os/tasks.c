/**
 *	tasks.c
 *
 *	Contains definitions of all tasks that will be performed.
 *
 *	Jeff Campbell
 *	1/31/18
 */

/* Includes */ 
#include "typedefs.h"
#include <stdio.h>
#include "tasks.h"

/* Prototypes */
void gvPrinter_Body(uint16_t uwCallRateMs);

/* Local Variables */

/**
 *	void gvPrinter_Body(uint8_t ubCallRateMs)
 *
 *	Description:
 *		Body of printer task.  Prints stuff.
 *
 *	Parameters:
 *		ulCallRateMs = Call rate, in ms
 *
 *	Return:
 *		N/A
 *
 */
void gvPrinter_Body(uint16_t uwCallRateMs)
{
	static uint16_t suwTimerMs = 0u;
	
	suwTimerMs += uwCallRateMs;
	
	if ( 1000u <= suwTimerMs )
	{
		suwTimerMs = 0u;
		
		printf("Task 1.\n");
	}
}