#ifndef _GCFL_BITS_FUNCS_
#define _GCFL_BITS_FUNCS_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// Библиотека основных классов и функций
//Версия файла: 20100627
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "types_common.h"

//-----------------------------------------------
// Функции для работы с 8-битными числами
//-----------------------------------------------

bool GetBit8(const uint8 &Number, const uint8 &BitPosition);
bool SetBit8(uint8 &Number, const uint8 &BitPosition, const bool &Value);

//-----------------------------------------------
// Функции для работы с 16-битными числами
//-----------------------------------------------

bool GetBit16(const uint16 &Number, const uint8 &BitPosition);
bool SetBit16(uint16 &Number, const uint8 &BitPosition, const bool &Value);

//-----------------------------------------------
// Функции для работы с 32-битными числами
//-----------------------------------------------

bool GetBit32(const uint32 &Number, const uint8 &BitPosition);
bool SetBit32(uint32 &Number, const uint8 &BitPosition, const bool &Value);

//-----------------------------------------------
// Функции для работы с 64-битными числами
//-----------------------------------------------

bool GetBit64(const uint64 &Number, const uint8 &BitPosition);
bool SetBit64(uint64 &Number, const uint8 &BitPosition, const bool &Value);

#endif //_GCFL_BITS_FUNCS_
