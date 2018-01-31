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
#include "print.h"
#include "tasks.h"

/* Prototypes */
void gvPrinter_Body(uint16_t uwCallRateMs);

/* Local Variables */

/**
 *	void gvPrinter_Body(uint16_t uwCallRateMs)
 *
 *	Description:
 *		Body of printer task.  Prints stuff.
 *		This is a pointless demo function.
 *
 *	Parameters:
 *		ulCallRateMs = Call rate, in ms
 *
 *	Returns:
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
		
		gvPrint("Task 1.\n");
	}
}