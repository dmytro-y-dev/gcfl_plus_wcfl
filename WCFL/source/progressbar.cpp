#include "progressbar.h"

wcProgressBar::wcProgressBar(wcWindow *Parent, const RECT &rct, const uint32 &Style, const uint32 &MinValue,
		const uint32 &MaxValue, const uint32 &Value) :
	wcWindow(Parent, rct, Style | WS_CHILD, WS_EX_NOPARENTNOTIFY, PROGRESS_CLASS)
{
	SetRange(MinValue, MaxValue);
	SetValue(Value);
}

wcProgressBar::~wcProgressBar()
{
	//
}

void wcProgressBar::SetValue(const uint32 &Value)
{
	SendMessage(this->hWnd, PBM_SETPOS, Value, 0);
}

uint32 wcProgressBar::GetValue()
{
	return SendMessage(this->hWnd, PBM_GETPOS, 0, 0);
}

void wcProgressBar::SetStep(const uint32 &Value)
{
	SendMessage(this->hWnd, PBM_SETSTEP, Value, 0);
}

uint32 wcProgressBar::GetStep()
{
	return SendMessage(this->hWnd, PBM_GETSTEP, 0, 0);
}

void wcProgressBar::Step()
{
	SendMessage(this->hWnd, PBM_STEPIT, 0, 0);
}

void wcProgressBar::SetRange(const uint32 &MinValue, const uint32 &MaxValue)
{
	SendMessage(this->hWnd, PBM_SETRANGE32, MinValue, MaxValue);
}
