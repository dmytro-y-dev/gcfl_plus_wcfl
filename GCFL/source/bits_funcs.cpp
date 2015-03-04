#include "bits_funcs.h"

bool GetBit8(const uint8 &Number, const uint8 &BitPosition)
{
	if (BitPosition > 7) return false;
	uint8 bitFlag = 0x80;
	bitFlag = bitFlag >> (7 - BitPosition);
	if ((Number | bitFlag) == Number) return true;
	return false;
}

bool SetBit8(uint8 &Number, const uint8 &BitPosition, const bool &Value)
{
	if (BitPosition > 7) return false;
	if (GetBit8(Number, BitPosition) == Value) return true;
	uint8 bitFlag = 0x80;
	bitFlag = bitFlag >> (7 - BitPosition);

	if (Value == false) Number = Number & (~bitFlag);
	else Number = Number | bitFlag;

	return true;
}

bool GetBit16(const uint16 &Number, const uint8 &BitPosition)
{
	if (BitPosition > 15) return false;
	uint16 bitFlag = 0x8000;
	bitFlag = bitFlag >> (15 - BitPosition);
	if ((Number | bitFlag) == Number) return true;
	return false;
}

bool SetBit16(uint16 &Number, const uint8 &BitPosition, const bool &Value)
{
	if (BitPosition > 15) return false;
	if (GetBit16(Number, BitPosition) == Value) return true;
	uint16 bitFlag = 0x8000;
	bitFlag = bitFlag >> (15 - BitPosition);

	if (Value == false) Number = Number & (~bitFlag);
	else Number = Number | bitFlag;

	return true;
}

bool GetBit32(const uint32 &Number, const uint8 &BitPosition)
{
	if (BitPosition > 31) return false;
	uint32 bitFlag = 0x80000000;
	bitFlag = bitFlag >> (31 - BitPosition);
	if ((Number | bitFlag) == Number) return true;
	return false;
}

bool SetBit32(uint32 &Number, const uint8 &BitPosition, const bool &Value)
{
	if (BitPosition > 31) return false;
	if (GetBit32(Number, BitPosition) == Value) return true;
	uint32 bitFlag = 0x80000000;
	bitFlag = bitFlag >> (31 - BitPosition);

	if (Value == false) Number = Number & (~bitFlag);
	else Number = Number | bitFlag;

	return true;
}

bool GetBit64(const uint64 &Number, const uint8 &BitPosition)
{
	if (BitPosition > 63) return false;
	uint64 bitFlag = 0x8000000000000000;
	bitFlag = bitFlag >> (63 - BitPosition);
	if ((Number | bitFlag) == Number) return true;
	return false;
}

bool SetBit64(uint64 &Number, const uint8 &BitPosition, const bool &Value)
{
	if (BitPosition > 63) return false;
	if (GetBit64(Number, BitPosition) == Value) return true;
	uint64 bitFlag = 0x8000000000000000;
	bitFlag = bitFlag >> (63 - BitPosition);

	if (Value == false) Number = Number & (~bitFlag);
	else Number = Number | bitFlag;

	return true;
}