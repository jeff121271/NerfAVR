/**
 *  tasks.c
 *
 *  Contains definitions of all tasks that will be performed.
 *
 *  Jeff Campbell
 *  1/31/18
 */

/* Includes */
#include <stdint.h>
#include "pins.h"
#include "tasks.h"

/* Prototypes */
void gvTasks_pinUpdate(uint16_t uwCallRateMs);

/* Local Variables */


void gvTasks_pinUpdate(uint16_t uwCallRateMs)
{
	/* Call pin update function */
	gvPins_updateAll();
}