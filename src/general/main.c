/**
 *  main.c
 *
 *  Main file of the program.
 *
 *  Jeff Campbell
 *  1/31/18
 *
 */

/* Includes */
#include "typedefs.h"
#include "print.h"
#include "os_main.h"

/* Prototypes */
int16_t main(void);

/* Local Variables */

/**
 *  int16_t main(void)
 *
 *  Description:
 *      Entry point of the program.  Initializes hardware and such
 *      and enters scheduler.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      If this function returns, we're in trouble.
 *
 */
int16_t main(void)
{
    /* Print debug statement */
	gvPrint("Entering main.\n");

    /* Enter OS */
    gvOS_enter();
	
    gvPrint("Exiting now.\n");

	return 1;
}