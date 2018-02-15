/**
 *  tasks.h
 *
 *  Interface file for tasks.c.
 *
 *  Jeff Campbell
 *  1/31/18
 */

#ifndef TASKS_H
#define TASKS_H

/* Includes */

/* Definitions */

/* Rate, in ms, of heartbeat pin toggle */
#define TASKS_HEARTBEAT_RATE_MS 100u

/* Global Functions */
extern void gvTasks_pinUpdate(uint16_t uwCallRateMs);

#endif /* #ifndef TASKS_H */