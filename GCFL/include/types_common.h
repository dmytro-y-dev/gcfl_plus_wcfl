#ifndef _GCFL_COMMON_TYPES_
#define _GCFL_COMMON_TYPES_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// Библиотека основных классов и функций
//Версия файла: 20100703
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

//Основные типы чисел с модификаторами

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned int uint;
typedef unsigned long long int uint64;

typedef char int8;
typedef short int int16;
typedef int int32;
typedef long long int int64;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

//Границы чисел различной длины

#define MAX_INT8		127
#define MAX_INT16		32767
#define MAX_INT32		2147483647

#define MIN_INT8		-128
#define MIN_INT16		-32768
#define MIN_INT32		-2147483648

#define MAX_UINT8		255
#define MAX_UINT16		65535
#define MAX_UINT32		4294967295

typedef char * LPSTR;
typedef const char * LPCSTR;

#endif //_GCFL_COMMON_TYPES_