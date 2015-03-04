#include "spinctrl.h"

wcUpDown::wcUpDown(wcWindow *Parent, const RECT &rct, const uint32 &Style, const int &MinValue,
				 const int &MaxValue, const int &Value) :
	wcWindow(Parent, rct, Style | WS_CHILD, WS_EX_NOPARENTNOTIFY, UPDOWN_CLASS)
{
	SetRange(MinValue, MaxValue);
	SetValue(Value);
}

wcUpDown::~wcUpDown()
{
	//
}

void wcUpDown::SetValue(const int &Value)
{
	SendMessage(this->hWnd, UDM_SETPOS32, 0, Value);
}

bool wcUpDown::GetValue(int &Value)
{
	BOOL bResult;
	int iPos = SendMessage(this->hWnd, UDM_GETPOS32, 0, (LPARAM)&bResult);
	if (!bResult)
	{
		Value = iPos;
		return true;
	}
	return false;
}

void wcUpDown::SetRange(const int &MinValue, const int &MaxValue)
{
	SendMessage(this->hWnd, UDM_SETRANGE32, MinValue, MaxValue);
}

wcSpinCtrl::wcSpinCtrl(wcWindow *Parent, const RECT &rct, const uint32 &Style, const int &MinValue,
					 const int &MaxValue, const int &Value) :
	wcUpDown(Parent, _RECT(rct.right, rct.top, 20, rct.bottom - rct.top), Style | UDS_SETBUDDYINT,
		MinValue, MaxValue, Value)
{
	this->ctrlEdit = new wcEdit(Parent, rct, ES_RIGHT | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER, EmptyStr);
	SendMessage(this->hWnd, UDM_SETBUDDY, (WPARAM)ctrlEdit->GetWndHandle(), 0);
	SetValue(Value);
}

wcSpinCtrl::~wcSpinCtrl()
{
	//
}

void wcSpinCtrl::SetTextFont(HFONT Font)
{
	this->ctrlEdit->SetTextFont(Font);
}

HFONT wcSpinCtrl::GetTextFont()
{
	return this->ctrlEdit->GetTextFont();
}