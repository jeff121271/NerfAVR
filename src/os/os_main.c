/**
 *  os_main.c
 *
 *  Main file of a primitive OS I decided to make.
 *
 *  Jeff Campbell
 *  1/31/18
 *
 */

/* Includes */
#include <stdint.h>
#include "null.h"
#include "tasks.h"
#include "timer.h"
#include "display_driver.h"
#include "os_main.h"

/* Prototypes */
void gvOS_enter(void);
static void vOS_initTasks(void);

/* Local Variables */
static os_task_t xTaskPool[OS_NUM_TASKS];

/**
 *  void gvOS_enter(void)
 *
 *  Description:
 *      Entry point of the OS.  Kicks off the task scheduling.
 *      Task scheduling is currently assumed to have 1ms resolution.
 *
 *  Parameters:
 *      N/A
 *
 *  Returns:
 *      N/A
 *
 */
void gvOS_enter(void)
{
    os_task_id_t eId;

    /* Initialize tasks */
    vOS_initTasks();

    /* Call task init functions */
    for ( eId = 0; eId < OS_NUM_TASKS; eId++ )
    {
        /* Null pointer check */
        if ( NULL_PTR != xTaskPool[eId].pvInitFunction )
        {
            xTaskPool[eId].pvInitFunction();
        }
    }

    /* Enter scheduling loop */
    for (;;)
    {
        /* Sleep for one tick */
        gvTimer_sleepMs(1u);

        /* Loop through task pool */
        for ( eId = 0; eId < OS_NUM_TASKS; eId++)
        {
            /* Decrement task counter */
            xTaskPool[eId].uwTicks--;

            /* Check if task is ready */
            if ( 0u == xTaskPool[eId].uwTicks )
            {
                /* Null pointer check */
                if ( NULL_PTR != xTaskPool[eId].pvStepFunction )
                {
                    /* Execute step function */
                    xTaskPool[eId].pvStepFunction(xTaskPool[eId].uwRateMs);
                }

                /* Reset task counter */
                xTaskPool[eId].uwTicks = xTaskPool[eId].uwRateMs;
            }
        }
    }
}

/**
 *    static void vOS_initTasks(void)
 *
 *    Description:
 *        Initializes all tasks.  Value of uwTicks should be
 *        staggered to prevent tasks from having to execute
 *        in the same 1ms period.
 *
 *    Parameters:
 *        N/A
 *
 *    Returns:
 *        N/A
 *
 */
static void vOS_initTasks(void)
{
	/* Configure display driver task */
	xTaskPool[OS_TASK_DISPLAY].uwRateMs = 10u;
	xTaskPool[OS_TASK_DISPLAY].uwTicks = 10u;
	xTaskPool[OS_TASK_DISPLAY].pvInitFunction = NULL_PTR;
	xTaskPool[OS_TASK_DISPLAY].pvStepFunction = &gvDisplay_process;
}