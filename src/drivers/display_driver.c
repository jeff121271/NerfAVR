/**
 *  display_driver.c
 *
 *  Driver for the 7 segment display.
 *
 *  Jeff Campbell
 *  2/6/18
 *
 */
 
/* Includes */
#include <math.h>
#include "typedefs.h"
#include "display_driver.h"

/* Prototypes */
void gvDisplay_process(uint16_t uwCallRateMs);

/* Local Variables */

/**
 *  void gvDisplay_process(uint16_t uwCallRateMs)
 *
 *  Description:
 *      Processes 7 segment display state machine.
 *
 *  Parameters:
 *      uwCallRateMs = Call rate of function, in ms
 *
 *  Returns:
 *      N/A
 *
 */
void gvDisplay_process(uint16_t uwCallRateMs)
{
    static uint8_t subTimerMs = 0u;
    static uint8_t subNumDigits = 0u;
    static display_driver_state_t seState = DISPLAY_STATE_INIT;
    uint16_t uwTxData = 0u;
    
    /* Increment timer */
    subTimerMs += (uint8_t)uwCallRateMs;
    
    /* Process state actions */
    switch (seState)
    {
        /* Init state: Set up driver, if necessary */
        case DISPLAY_STATE_INIT:
            break;
        
        /* Wait state: Do nothing */
        case DISPLAY_STATE_WAIT:
            break;
            
        /* Put state: Put digits out to the display */
        case DISPLAY_STATE_PUT:
            /* Get data to send */
            
            /* Select the appropriate digit */
            uwTxData = (uint16_t)((uwTxData / ((uint16_t)pow(10u, subNumDigits))) % 10u);
            
            /* Send digit to display */
            
            /* Decrement digit counter */
            subNumDigits--;
            break;
			
		/* Default case: Do nothing */
		default:
			break;
    }
    
    /* Process state transitions */
    switch (seState)
    {
        /* Init state: Move immediately to wait state, clear timer */
        case DISPLAY_STATE_INIT:
            seState = DISPLAY_STATE_WAIT;
            subTimerMs = 0u;
            break;
        
        /* Wait state: Move to put state after appropriate amount of time */
        case DISPLAY_STATE_WAIT:
            if (subTimerMs >= DISPLAY_WAIT_TIME_MS)
            {
                /* Set state */
                seState = DISPLAY_STATE_PUT;
                
                /* Set number of digits */
                subNumDigits = DISPLAY_NUM_DIGITS;
            }
            break;
            
        /* Put state: If out of digits, move back to wait state */
        case DISPLAY_STATE_PUT:
            if (subNumDigits == 0u)
            {
                /* Set state */
                seState = DISPLAY_STATE_WAIT;
                
                /* Reset timer */
                subTimerMs = 0u;                
            }
            break;
		
		/* Default case: Move to init state */
		default:
			seState = DISPLAY_STATE_INIT;
			break;
    }
}