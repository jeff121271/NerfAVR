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

/**
 *	void gvTasks_pinUpdate(uint16_t uwCallRateMs)
 *
 *	Description:
 *		Calls the pin update function.
 *
 *	Parameters:
 *		uwCallRateMs = Call rate of function, in ms
 *
 *	Returns:
 *		N/A
 *
 */
void gvTasks_pinUpdate(uint16_t uwCallRateMs)
{
	uint8_t ubPin = PIN_LOGIC_HIGH;

	/* Toggle test pin */
	ubPin = (PIN_LOGIC_LOW == ubPin) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
	gvPins_control(PIN_TEST_OUTPUT, ubPin);

	/* Call pin update function */
	gvPins_updateAll();
}