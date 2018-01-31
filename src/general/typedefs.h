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
#define NULL 0u
#define NULL_PTR ((void *)0u)

// todo: Fix these up later; make sure they match hardware/compiler definitions
typedef long int32_t;
typedef unsigned long uint32_t;
typedef int int16_t;
typedef unsigned int uint16_t;
typedef char int8_t;
typedef unsigned char uint8_t;

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
