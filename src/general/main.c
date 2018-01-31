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
#include <stdio.h>
#include "os_main.h"

/* Prototypes */
int32_t main(void);

/* Local Variables */

/**
 *  int32_t main(void)
 *
 *  Description:
 *      Entry point of the program.  Initializes hardware and such
 *      and enters scheduler.
 *
 *  Parameters:
 *      N/A
 *
 *  Return:
 *      If this function returns, we're in trouble.
 *
 */
int32_t main(void)
{
	printf("Entering main.\n");
	
    /* Enter OS */
    gvOS_enter();
	
	printf("Exiting now.\n");
}