/**
 *	timer.c
 *
 *	Used in timer logic.  This particular copy assumes we're
 *	just a Windows console program.  The real thing will use
 *	hardware registers.
 *
 *	Jeff Campbell
 *	1/31/18
 *
 */

/* Includes */ 
#include "typedefs.h"
#include <time.h>
#include "timer.h"

/* Prototypes */
void gvTimer_sleepMs(uint16_t uwTimeMs);

/* Local Variables */

/**
 *	void gvTimer_sleepMs(uint8_t ubTimeMs)
 *
 *	Description:
 *		Sleeps for the given amount of time.
 *
 *	Parameters:
 *		ubTimeMs = Time to sleep, in ms.
 *
 *	Returns:
 *		N/A
 *
 */
void gvTimer_sleepMs(uint16_t uwTimeMs)
{
	/* Get starting time */
	uint32_t ulStartTime = clock();
	uint32_t ulCurrentTime = ulStartTime;
	
	/* Loop until enough time has passed */
	while ( (ulCurrentTime - ulStartTime) < ((uint32_t)uwTimeMs) )
	{
		ulCurrentTime = clock();
	}
}