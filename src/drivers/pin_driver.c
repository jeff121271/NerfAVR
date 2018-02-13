/**
 *	pin_driver.c
 *
 *	Driver file for pins.
 *
 *	Jeff Campbell
 *	2/13/18
 *
 */

/* Includes */
#include <stdbool.h>
#include "null.h"
#include "pin_driver.h"

/* Prototypes */
void gvPin_init(pin_driver_t *pDriver);
static void vPin_setLogicState(pin_driver_desc_t *pDescription, pin_state_logic_t eState);
static void vPin_process(pin_driver_desc_t *pDescription);

/* Local Variables */
pin_driver_t pin_PA0;
pin_driver_t pin_PA1;

pin_driver_t pin_PB0;
pin_driver_t pin_PB1;
pin_driver_t pin_PB2;
pin_driver_t pin_PB3;
pin_driver_t pin_PB4;
pin_driver_t pin_PB5;
pin_driver_t pin_PB6;
pin_driver_t pin_PB7;

pin_driver_t pin_PD0;
pin_driver_t pin_PD1;
pin_driver_t pin_PD2;
pin_driver_t pin_PD3;
pin_driver_t pin_PD4;
pin_driver_t pin_PD5;

/**
 *	bool gfPin_init(pin_driver_t *pDriver)
 *
 *	Description:
 *		Initializes a pin driver object.
 *
 *	Parameters:
 *		pDriver = Pin driver object
 *
 *	Returns:
 *		N/A
 *
 */
bool gfPin_init(pin_driver_t *pDriver)
{
	bool fResult = false;

	/* Null pointer check */
	if ( NULL_PTR != pDriver )
	{
		/* Set function pointers */
		pDriver->Operations.pvSetState = &vPin_setLogicState;
		pDriver->Operations.pvProcess = &vPin_process;

		/* Set return status */
		fResult = true;
	}

	/* Return results */
	return fResult;
}

/**
 *	static void vPin_setLogicState(pin_driver_desc_t *pDescription, pin_state_logic_t eState)
 *
 *	Description:
 *		Sets the logic state of a pin object.
 *
 *	Parameters:
 *		pDescription = Pointer to driver description
 *		eState = Desired pin logic state
 *
 *	Returns:
 *		N/A
 *
 */
static void vPin_setLogicState(pin_driver_desc_t *pDescription, pin_state_logic_t eState)
{
	/* Null pointer check */
	if ( NULL_PTR != pDescription )
	{
		/* Check that pin is in output mode */
		if ( PIN_DIR_OUTPUT != pDescription->eDirection )
		{
			/* Set logic state */
			pDescription->eLogic = eState;
		}
	}
}

static void vPin_process(pin_driver_desc_t *pDescription)
{

}