/**
 *  typedefs.h
 *
 *  Contains all primitive type definitions for the project.
 *
 *  Jeff Campbell
 *  1/31/18
 *
 */

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/* Defines */

/* Constant value for True */
#define TRUE 1u

/* Constant value for False */
#define FALSE 0u

/* Null value */
#define NULL 0u

/* Null value, but as a pointer */
#define NULL_PTR ((void *)0u)

/* Standard integer types */
typedef long int32_t;
typedef unsigned long uint32_t;
typedef int int16_t;
typedef unsigned int uint16_t;
typedef char int8_t;
typedef unsigned char uint8_t;

/* Boolean */
typedef unsigned char boolean;

/* Volatile definitions */
typedef volatile long vint32_t;
typedef volatile unsigned long vuint32_t;
typedef volatile int vint16_t;
typedef volatile unsigned int vuint16_t;
typedef volatile char vint8_t;
typedef volatile unsigned char vuint8_t;

// todo: Check later if this ever really gets used
typedef union nibbles
{
    uint8_t Byte;
    struct
    {
        uint8_t N1:4;
        uint8_t N2:4;
    } Nibbles;
} nibbles_t;

/* Global Functions */

#endif /* #ifndef TYPEDEFS_H */
