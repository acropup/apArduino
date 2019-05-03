#ifndef APDATATYPES_H
#define APDATATYPES_H

// apDataTypes.h defines short names for the standard integer datatypes

#ifdef ARDUINO
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
#else
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;
typedef signed char     s8;
typedef signed short    s16;
typedef signed long     s32;
#endif

#endif
