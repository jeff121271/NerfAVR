/**
 *	pins.c
 *
 *	Handles logic for interacting with digital I/O pins.
 *
 *	Jeff Campbell
 *	2/13/18
 *
 */

/* Includes */
#include <stdbool.h>
#include <avr/io.h>
#include "pins.h"

/* Prototypes */
void gvPins_init(void);
static void vPins_configAll(void);
void gvPins_updateAll(void);

/* Local Variables */

/* Array of pin descriptions */
static pin_desc_t digitalPins[PIN_NUMBER];

/**
 *	void gvPins_init(void)
 *
 *	Description:
 *		Initializes digital pin configurations.
 *
 *	Parameters:
 *		N/A
 *
 *	Returns:
 *		N/A
 *
 */
void gvPins_init(void)
{
	/* Configure Test output pin */
	digitalPins[PIN_TEST_OUTPUT].logicLevel = PIN_LOGIC_LOW;
	digitalPins[PIN_TEST_OUTPUT].direction = PIN_DIRECTION_OUTPUT;
	digitalPins[PIN_TEST_OUTPUT].portSel = PIN_SELECT_PORTA;
	digitalPins[PIN_TEST_OUTPUT].pullupEnable = PIN_PULLUP_DISABLE;
	digitalPins[PIN_TEST_OUTPUT].pinNum = 0u;

	/* Configure pins */
	vPins_configAll();

	/* Update pins */
	gvPins_updateAll();
}

/**
 *	static void vPins_configAll(void)
 *
 *	Description:
 *		Configures all the pins' registers.
 *
 *	Parameters:
 *		N/A
 *
 *	Returns:
 *		N/A
 *
 */
static void vPins_configAll(void)
{
	pin_index_t ePinIdx;

	/* Loop over all pins */
	for ( ePinIdx = (pin_index_t)0u; ePinIdx < PIN_NUMBER; ePinIdx++ )
	{
		/* Process output pins */
		if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
		{
			/* Select port */
			switch (digitalPins[ePinIdx].portSel)
			{
				case PIN_SELECT_PORTA:
					DDRA |= (1u << digitalPins[ePinIdx].pinNum);
					break;

				case PIN_SELECT_PORTB:
					DDRB |= (1u << digitalPins[ePinIdx].pinNum);
					break;

				case PIN_SELECT_PORTD:
					DDRD |= (1u << digitalPins[ePinIdx].pinNum);
					break;

				default:
					/* Do nothing */
					break;
			}
		}
		/* Process input pins */
		else
		{
			/* Select port */
			switch (digitalPins[ePinIdx].portSel)
			{
				case PIN_SELECT_PORTA:
					DDRA &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
					break;

				case PIN_SELECT_PORTB:
					DDRB &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
					break;

				case PIN_SELECT_PORTD:
					DDRD &= (uint8_t)(~(1u << digitalPins[ePinIdx].pinNum));
					break;

				default:
					/* Do nothing */
					break;
			}
		}
	}
}

/**
 *	void gvPins_updateAll(void)
 *
 *	Description:
 *		Updates the status of the pins.  Pushes all output pins to the Port
 *		registers and reads all input pins from the ports.
 *
 *	Parameters:
 *		N/A
 *
 *	Returns:
 *		N/A
 *
 */
void gvPins_updateAll(void)
{
	pin_index_t ePinIdx;

	/* Loop over each pin object */
	for ( ePinIdx = (pin_index_t)0u; ePinIdx < PIN_NUMBER; ePinIdx++ )
	{
		/* Process output pin */
		if ( PIN_DIRECTION_OUTPUT == digitalPins[ePinIdx].direction )
		{
			/* Select the appropriate port */
			switch (digitalPins[ePinIdx].portSel)
			{
				case PIN_SELECT_PORTA:
					PORTA |= (digitalPins[ePinIdx].logicLevel << digitalPins[ePinIdx].pinNum);
					break;

				case PIN_SELECT_PORTB:
					PORTB |= (digitalPins[ePinIdx].logicLevel << digitalPins[ePinIdx].pinNum);
					break;

				case PIN_SELECT_PORTD:
					PORTD |= (digitalPins[ePinIdx].logicLevel << digitalPins[ePinIdx].pinNum);
					break;

				default:
					/* Do nothing */
					break;
			}
		}
		/* Process input pin */
		else
		{
			/* Select appropriate port */
			switch (digitalPins[ePinIdx].portSel)
			{
				case PIN_SELECT_PORTA:
					digitalPins[ePinIdx].logicLevel = ((PORTA & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
					break;

				case PIN_SELECT_PORTB:
					digitalPins[ePinIdx].logicLevel = ((PORTB & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
					break;

				case PIN_SELECT_PORTD:
					digitalPins[ePinIdx].logicLevel = ((PORTD & (1u << digitalPins[ePinIdx].pinNum)) > 0) ? PIN_LOGIC_HIGH : PIN_LOGIC_LOW;
					break;

				default:
					/* Do nothing */
					break;
			}
		}
	}
}