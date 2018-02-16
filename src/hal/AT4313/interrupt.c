/**
 *  interrupt.c
 *
 *  Contains definitions of all used interrupts.
 *
 *  Jeff Campbell
 *  2/15/18
 *
 */ 

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "flywheel_driver.h"
#include "interrupt.h"

/* Prototypes */
void gvINT_init(void);
void gvINT_enableFlywheel(void);
void gvINT_disableFlywheel(void);

/* Local Variables */

/**
 *  void gvINT_init(void)
 *
 *  Description:
 *      Configures anything we need to do for
 *      interrupts.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvINT_init(void)
{
    /* Configure INT0 (flywheel #1 feedback) as bidirectional (ISC0 1:0 = 01) */
    MCUCR |= 0u << ISC01;
    MCUCR |= 1u << ISC00;

    /* Configure INT1 (flywheel #2 feedback) as bidirectional (ISC1 1:0 = 01) */
    MCUCR |= 0u << ISC01;
    MCUCR |= 1u << ISC00;
}

/**
 *  void gvINT_enableFlywheel(void)
 *
 *  Description:
 *      Enables flywheel encoder interrupts.
 *
 *  Parameters:
 *      N/A
 * 
 *  Returns:
 *      N/A
 *
 */
void gvINT_enableFlywheel(void)
{
    /* Enable INT0 */
    GIMSK |= 1u << INT0;

    /* Enable INT1 */
    GIMSK |= 1u << INT1;
}

/**
 *  void gvINT_disableFlywheel(void)
 *
 *  Description:
 *      Disables flywheel encoder interrupts.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvINT_disableFlywheel(void)
{
    /* Disable INT0 */
    GIMSK &= (uint8_t)(~(1u << INT0));

    /* Disable INT1 */
    GIMSK &= (uint8_t)(~(1u << INT1));
}

/**
 *  ISR(INT0_vect)
 *
 *  Description:
 *      Interrupt handler for flywheel #1 encoder.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
ISR(INT0_vect)
{
    /* Report to flywheel driver */
    gvFlywheel_intHandler(FLYWHEEL_SELECT_1);
}

/**
 *  ISR(INT1_vect)
 *
 *  Description:
 *      Interrupt handler for flywheel #2 encoder.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
ISR(INT1_vect)
{
    /* Report to flywheel driver */
    gvFlywheel_intHandler(FLYWHEEL_SELECT_2);
}