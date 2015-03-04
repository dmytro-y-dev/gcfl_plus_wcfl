#include "wcfl_main.h"

RECT _RECT(long left, long top, long width, long height)
{
	RECT rct = {left, top, left + width, top + height};
	return rct;
}