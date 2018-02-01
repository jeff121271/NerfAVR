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
#define TRUE 1u
#define FALSE 0u
#define NULL 0u
#define NULL_PTR ((void *)0u)

typedef long int32_t;
typedef unsigned long uint32_t;
typedef int int16_t;
typedef unsigned int uint16_t;
typedef char int8_t;
typedef unsigned char uint8_t;
typedef unsigned char boolean;
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
