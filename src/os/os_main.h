/**
 *  os_main.h
 *
 *  Interface file for os_main.c.
 *
 *  Jeff Campbell
 *  1/31/18
 *
 */

#ifndef OS_MAIN_H
#define OS_MAIN_H

/* Defines */

/* Enumeration of task IDs */
typedef enum os_task_id
{
    OS_TASK_DISPLAY = 0u,   /* < Display driver update task */
	OS_TASK_PIN_UPDATE,		/* < Periodic pin update task */
    OS_NUM_TASKS,           /* < Number of tasks */
} os_task_id_t;

/* Typedef for OS Task structure */
typedef struct os_task
{
    uint16_t uwRateMs;                                /* < Call rate in ms */
    uint16_t uwTicks;                                /* < Ticks until call time */
    void (*pvInitFunction)(void);                    /* < Init function of task */
    void (*pvStepFunction)(uint16_t uwCallRateMs);    /* < Body of task */
} os_task_t;

/* Global functions */
extern void gvOS_enter(void);

#endif /* #ifndef OS_MAIN_H */