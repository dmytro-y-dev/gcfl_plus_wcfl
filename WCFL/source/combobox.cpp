#include "combobox.h"
#include <bits_funcs.h>

wcComboBox::wcComboBox(wcWindow *Parent, const RECT &rct, const uint32 &Style) :
	wcWindow(Parent, rct, Style | WS_CHILD,
		WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY, WC_COMBOBOX)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);
}

wcComboBox::~wcComboBox()
{
	Clear();
}

uint32 wcComboBox::AddString(gcString String)
{
	return SendMessage(this->hWnd, CB_ADDSTRING, NULL, (LPARAM)(String.GetCharBuffer()));
}

void wcComboBox::AddStrings(gcStrList Strings)
{
	uint32 uMemory = 0;
	for (uint32 i = 0; i < Strings.Count(); i++) uMemory += Strings[i]->Length();

	SendMessage(this->hWnd, CB_INITSTORAGE, Strings.Count(), (LPARAM)uMemory);
	for (uint32 i = 0; i < Strings.Count(); i++)
		SendMessage(this->hWnd, CB_ADDSTRING, NULL, (LPARAM)(Strings[i]->GetCharBuffer()));
}

bool wcComboBox::InsertString(const uint32 &Index, gcString String)
{
	int iResult = SendMessage(this->hWnd, CB_INSERTSTRING, Index, (LPARAM)(String.GetCharBuffer()));
	if ((iResult == CB_ERR)||(iResult == CB_ERRSPACE)) return false;
	return true;
}

uint32 wcComboBox::GetStringsCount()
{
	return SendMessage(this->hWnd, CB_GETCOUNT, NULL, NULL);
}

bool wcComboBox::RemoveString(const uint32 &Index)
{
	if (SendMessage(this->hWnd, CB_DELETESTRING, Index, NULL) == CB_ERR) return false;
	return true;
}

gcString wcComboBox::GetString(const uint32 &Index)
{
	uint32 uCharsCount = 0;
	if ((uCharsCount = SendMessage(this->hWnd, CB_GETLBTEXTLEN, Index, NULL)) == CB_ERR) return EmptyStr;
	LPSTR String = new CHAR[uCharsCount + 1];
	SendMessage(this->hWnd, CB_GETLBTEXT, Index, (LPARAM)String);
	gcString Text = _T(String);
	delete []String;
	return Text;
}

gcStrList wcComboBox::GetStrings()
{
	gcStrList lstStrings;
	uint32 uCount = GetStringsCount();
	for (uint32 i = 0; i < uCount; i++)
		lstStrings.Append(new gcString(GetString(i)));
	return lstStrings;
}

void wcComboBox::Clear()
{
	SendMessage(this->hWnd, CB_RESETCONTENT, NULL, NULL);
}
	
bool wcComboBox::GetCurSelection(uint32 &Index)
{
	if ((Index = SendMessage(this->hWnd, CB_GETCURSEL, NULL, NULL)) == CB_ERR) return false;
	return true;
}

bool wcComboBox::SetCurSelection(const uint32 &Index, const bool &bSelected)
{
	if (bSelected)
	{
		if (SendMessage(this->hWnd, CB_SETCURSEL, Index, NULL) == CB_ERR) return false;
	}
	else SendMessage(this->hWnd, CB_SETCURSEL, -1, NULL);
	return true;
}
