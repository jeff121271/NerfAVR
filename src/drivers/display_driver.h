/**
 *  display_driver.h
 *
 *  Interface for the 7 segment display driver.
 *
 *  Jeff Campbell
 *  2/6/18
 *
 */

#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

/* Includes */

/* Defines */

/* Time, in ms, to wait between display updates */
#define DISPLAY_WAIT_TIME_MS 100u

/* Number of digits on the 7 segment display */
#define DISPLAY_NUM_DIGITS 3u

/* Enumeration for display driver state machine */
typedef enum display_driver_state
{
    DISPLAY_STATE_INIT = 0,        /* < Init state */
    DISPLAY_STATE_WAIT,            /* < Waiting state */
    DISPLAY_STATE_PUT,            /* < Put character state */
} display_driver_state_t;

/* Global Functions */
extern void gvDisplay_init(void);
extern void gvDisplay_process(uint16_t uwCallRateMs);
extern void gvDisplay_setOutput(uint16_t uwNew);

#endif /* #ifndef DISPLAY_DRIVER_H */