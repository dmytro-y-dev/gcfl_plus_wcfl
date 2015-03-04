#ifndef _GCFL_BITS_FUNCS_
#define _GCFL_BITS_FUNCS_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// ���������� �������� ������� � �������
//������ �����: 20100627
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "types_common.h"

//-----------------------------------------------
// ������� ��� ������ � 8-������� �������
//-----------------------------------------------

bool GetBit8(const uint8 &Number, const uint8 &BitPosition);
bool SetBit8(uint8 &Number, const uint8 &BitPosition, const bool &Value);

//-----------------------------------------------
// ������� ��� ������ � 16-������� �������
//-----------------------------------------------

bool GetBit16(const uint16 &Number, const uint8 &BitPosition);
bool SetBit16(uint16 &Number, const uint8 &BitPosition, const bool &Value);

//-----------------------------------------------
// ������� ��� ������ � 32-������� �������
//-----------------------------------------------

bool GetBit32(const uint32 &Number, const uint8 &BitPosition);
bool SetBit32(uint32 &Number, const uint8 &BitPosition, const bool &Value);

//-----------------------------------------------
// ������� ��� ������ � 64-������� �������
//-----------------------------------------------

bool GetBit64(const uint64 &Number, const uint8 &BitPosition);
bool SetBit64(uint64 &Number, const uint8 &BitPosition, const bool &Value);

#endif //_GCFL_BITS_FUNCS_
