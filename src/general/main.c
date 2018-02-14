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
#include <stdint.h>
#include "clock.h"
#include "pins.h"
#include "os_main.h"

/* Prototypes */
int16_t main(void);
static void vInitHardware(void);

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
    /* Initialize hardware */
    vInitHardware();

    /* Enter OS */
    gvOS_enter();

	/* Should never reach this return value */
	return 1;
}

/**
 *  static void vInitHardware(void)
 *
 *  Description:
 *      Initializes the hardware.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
static void vInitHardware(void)
{
    /* Initialize clock */
    gvClock_init();

	/* Initialize pins */
	gvPins_init();
}