#include "listbox.h"
#include <bits_funcs.h>

wcListBox::wcListBox(wcWindow *Parent, const RECT &rct, const uint32 &Style) :
	wcWindow(Parent, rct, Style | WS_CHILD | LBS_HASSTRINGS,
		WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY, WC_LISTBOX)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);
}

wcListBox::~wcListBox()
{
	Clear();
}

uint32 wcListBox::AddString(gcString String)
{
	return SendMessage(this->hWnd, LB_ADDSTRING, NULL, (LPARAM)(String.GetCharBuffer()));
}

void wcListBox::AddStrings(gcStrList Strings)
{
	uint32 uMemory = 0;
	for (uint32 i = 0; i < Strings.Count(); i++) uMemory += Strings[i]->Length();

	SendMessage(this->hWnd, LB_INITSTORAGE, Strings.Count(), (LPARAM)uMemory);
	for (uint32 i = 0; i < Strings.Count(); i++)
		SendMessage(this->hWnd, LB_ADDSTRING, NULL, (LPARAM)(Strings[i]->GetCharBuffer()));
}

bool wcListBox::InsertString(const uint32 &Index, gcString String)
{
	int iResult = SendMessage(this->hWnd, LB_INSERTSTRING, Index, (LPARAM)(String.GetCharBuffer()));
	if ((iResult == LB_ERR)||(iResult == LB_ERRSPACE)) return false;
	return true;
}

uint32 wcListBox::GetStringsCount()
{
	return SendMessage(this->hWnd, LB_GETCOUNT, NULL, NULL);
}

bool wcListBox::RemoveString(const uint32 &Index)
{
	if (SendMessage(this->hWnd, LB_DELETESTRING, Index, NULL) == LB_ERR) return false;
	return true;
}

gcString wcListBox::GetString(const uint32 &Index)
{
	uint32 uCharsCount = 0;
	if ((uCharsCount = SendMessage(this->hWnd, LB_GETTEXTLEN, Index, NULL)) == LB_ERR) return EmptyStr;
	LPSTR String = new CHAR[uCharsCount + 1];
	SendMessage(this->hWnd, LB_GETTEXT, Index, (LPARAM)String);
	gcString Text = _T(String);
	delete []String;
	return Text;
}

gcStrList wcListBox::GetStrings()
{
	gcStrList lstStrings;
	uint32 uCount = GetStringsCount();
	for (uint32 i = 0; i < uCount; i++)
		lstStrings.Append(new gcString(GetString(i)));
	return lstStrings;
}

void wcListBox::Clear()
{
	SendMessage(this->hWnd, LB_RESETCONTENT, NULL, NULL);
}
	
//Для ListBox'ов с "мультивыделением"
bool wcListBox::IsSelected(const uint32 &Index)
{
	if (SendMessage(this->hWnd, LB_GETSEL, Index, NULL) > 0) return true;
	return false;
}

bool wcListBox::Select(const uint32 &Index, const bool &bSelect)
{
	if ((bSelect) && (SendMessage(this->hWnd, LB_SETSEL, TRUE, Index) != LB_ERR)) return true;
	else if ((!bSelect) && (SendMessage(this->hWnd, LB_SETSEL, FALSE, Index) != LB_ERR)) return true;

	return false;
}

uint32 wcListBox::GetSelectionsCount()
{
	uint32 uCount = 0;
	if ((uCount = SendMessage(this->hWnd, LB_GETSELCOUNT, NULL, NULL)) == LB_ERR)
	{
		if (SendMessage(this->hWnd, LB_GETCURSEL, NULL, NULL) == LB_ERR) return 0;
		else return 1;
	}
	return uCount;
}

gcDynList<uint32> wcListBox::GetSelections()
{
	gcDynList<uint32> lstSelections;
	uint32 MaxSelections = GetSelectionsCount();
	uint32 *Selections = new uint32[MaxSelections];
	if (SendMessage(this->hWnd, LB_GETSELITEMS, MaxSelections, (LPARAM)Selections) == LB_ERR)
	{
		uint32 Index;
		if (GetCurSelection(Index)) {
			lstSelections.Append(new uint32(Index));
		}
	}
	else
	{
		for (uint32 i = 0; i < MaxSelections; i++) {
			lstSelections.Append(new uint32(Selections[i]));
		}
	}
	return lstSelections;
}

void wcListBox::SetSelections(gcDynList<uint32> Selections)
{
	for (uint32 i = 0; i < Selections.Count(); i++) Select(*Selections[i]);
}

//Для ListBox'ов с одиночным выделением
bool wcListBox::GetCurSelection(uint32 &Index)
{
	if ((Index = SendMessage(this->hWnd, LB_GETCURSEL, NULL, NULL)) == LB_ERR) return false;
	return true;
}

bool wcListBox::SetCurSelection(const bool &bSelected, const uint32 &Index)
{
	if (bSelected)
	{
		if (SendMessage(this->hWnd, LB_SETCURSEL, Index, NULL) == LB_ERR) return false;
	}
	else SendMessage(this->hWnd, LB_SETCURSEL, -1, NULL);
	return true;
}

wcSelectionType wcListBox::GetSelectionType()
{
	long iStyle = GetWindowLong(this->hWnd, GWL_STYLE);
	if ((iStyle & LBS_MULTIPLESEL) == LBS_MULTIPLESEL)
		return SEL_MULTIPLE;
	else if ((iStyle & LBS_EXTENDEDSEL) == LBS_EXTENDEDSEL)
		return SEL_EXTENDED;
	else if ((iStyle & LBS_NOSEL) == LBS_NOSEL)
		return SEL_NOSEL;
	return SEL_SINGLE;
}
