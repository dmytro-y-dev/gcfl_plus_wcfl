#include "listctrl.h"

wcListCtrl::wcListCtrl(wcWindow *Parent, const RECT &rct, const uint32 &Style) :
	wcWindow(Parent, rct, Style | WS_CHILD | LVS_REPORT | LVS_SINGLESEL,
			WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE, WC_LISTVIEW)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);

	this->uColumnsCount = 0;
}

wcListCtrl::~wcListCtrl()
{
	//
}

uint32 wcListCtrl::AddRow()
{
	LPLVITEM itmTemp = new LVITEM;
	itmTemp->mask = 0;
	itmTemp->iItem = GetItemsCount();
	itmTemp->iSubItem = 0;

	ListView_InsertItem(this->hWnd, itmTemp);
	delete itmTemp;
	return GetItemsCount() - 1;
}

bool wcListCtrl::InsertRow(const uint32 &RowIndex)
{
	LPLVITEM itmTemp = new LVITEM;
	itmTemp->mask = 0;
	itmTemp->iItem = RowIndex;
	itmTemp->iSubItem = 0;

	if (ListView_InsertItem(this->hWnd, itmTemp))
	{
		delete itmTemp;
		return true;
	}
	else
	{
		delete itmTemp;
		return false;
	}
}

bool wcListCtrl::SetString(const uint32 &RowIndex, const uint32 &ColumnIndex, gcString String)
{
	LPLVITEM _macro_lvi = new LVITEM;
	_macro_lvi->iSubItem = ColumnIndex;

	if (String.Length() > 0)
	{
		_macro_lvi->cchTextMax = String.Length();
		_macro_lvi->pszText = new CHAR[_macro_lvi->cchTextMax + 1];
		_macro_lvi->pszText = strcpy(_macro_lvi->pszText, String.GetCharBuffer());
		_macro_lvi->pszText[_macro_lvi->cchTextMax] = '\0';
	} else
	{
		_macro_lvi->cchTextMax = 0;
		_macro_lvi->pszText = NULL;
	}

	if (!SendMessage(this->hWnd, LVM_SETITEMTEXT, RowIndex, (LPARAM)_macro_lvi))
	{
		delete []_macro_lvi->pszText;
		delete _macro_lvi;
		return false;
	}
	delete []_macro_lvi->pszText;
	delete _macro_lvi;
	return true;
}

gcString wcListCtrl::GetString(const uint32 &RowIndex, const uint32 &ColumnIndex)
{
	LPLVITEM _macro_lvi = new LVITEM;
	_macro_lvi->iSubItem = ColumnIndex;

	_macro_lvi->cchTextMax = 1024;
	_macro_lvi->pszText = new CHAR[1025];

	SendMessage(this->hWnd, LVM_GETITEMTEXT, RowIndex, (LPARAM)_macro_lvi);

	_macro_lvi->cchTextMax = strlen(_macro_lvi->pszText);
	LPSTR buf = new CHAR[_macro_lvi->cchTextMax + 1];
	buf = strcpy(buf, _macro_lvi->pszText);
	buf[_macro_lvi->cchTextMax] = '\0';

	delete []_macro_lvi->pszText;
	delete _macro_lvi;
	gcString Str = _T(buf);
	delete []buf;
	return Str;
}

bool wcListCtrl::RemoveRow(const uint32 &RowIndex)
{
	if (ListView_DeleteItem(this->hWnd, RowIndex)) return true;
	return false;
}

uint32 wcListCtrl::AddColumn(gcString String, const uint32 &uWidth)
{
	LPLVCOLUMN colTemp = new LVCOLUMN;
	colTemp->mask = LVCF_TEXT | LVCF_WIDTH;
	colTemp->fmt = 0;

	colTemp->cchTextMax = String.Length();
	colTemp->pszText = new CHAR[colTemp->cchTextMax + 1];
	colTemp->pszText = strcpy(colTemp->pszText, String.GetCharBuffer());
	colTemp->pszText[colTemp->cchTextMax] = '\0';

	colTemp->cx = uWidth; this->uColumnsCount++;
	ListView_InsertColumn(this->hWnd, GetColumnsCount(), colTemp);
	delete []colTemp->pszText;
	delete colTemp;
	return this->uColumnsCount;
}

void wcListCtrl::AddColumns(gcStrList Strings, gcDynList<uint32> uWidths)
{
	uint32 uCount;
	if (Strings.Count() > uWidths.Count()) uCount = uWidths.Count();
	else uCount = Strings.Count();

	for (uint32 i = 0; i < uCount; i++) AddColumn(*Strings[i], *uWidths[i]);
}

bool wcListCtrl::InsertColumn(const uint32 &ColumnIndex, const uint32 &uWidth, gcString String)
{
	LPLVCOLUMN colTemp = new LVCOLUMN;
	colTemp->mask = LVCF_TEXT | LVCF_WIDTH;
	colTemp->fmt = 0;

	colTemp->cchTextMax = String.Length();
	colTemp->pszText = new CHAR[colTemp->cchTextMax + 1];
	colTemp->pszText = strcpy(colTemp->pszText, String.GetCharBuffer());
	colTemp->pszText[colTemp->cchTextMax] = '\0';

	colTemp->cx = uWidth; this->uColumnsCount++;
	int iRes = ListView_InsertColumn(this->hWnd, ColumnIndex, colTemp);
	delete []colTemp->pszText;
	delete colTemp;
	if (iRes == -1) return false;
	else return true;
}

uint32 wcListCtrl::GetColumnsCount()
{
	return this->uColumnsCount;
}

bool wcListCtrl::RemoveColumn(const uint32 &ColumnIndex)
{
	if (ListView_DeleteColumn(this->hWnd, ColumnIndex))
	{
		this->uColumnsCount--;
		return true;
	}
	return false;
}

void wcListCtrl::ClearAll()
{
	ListView_DeleteAllItems(this->hWnd);
}

gcString wcListCtrl::GetColumn(const uint32 &ColumnIndex)
{
	LPLVCOLUMN col = NULL; gcString strResult;
	if (ListView_GetColumn(this->hWnd, ColumnIndex, col) == FALSE) return EmptyStr;
	if ((col->mask & LVCF_TEXT) != LVCF_TEXT)
	{
		delete []col->pszText;
		delete col;
	}
	else
	{
		LPSTR Text = new CHAR[col->cchTextMax + 1];
		Text = strcpy(Text, col->pszText);
		Text[col->cchTextMax] = '\0';

		delete []col->pszText;
		delete col;

		strResult = _T(Text);
		delete []Text;
	}
	return strResult;
}
uint32 wcListCtrl::GetItemsCount()
{
	return ListView_GetItemCount(this->hWnd);
}

bool wcListCtrl::GetCurSelection(uint32 &Index)
{
	if ((Index = ListView_GetSelectionMark(this->hWnd)) == -1) return false;
	return true;
}

void wcListCtrl::SetCurSelection(const bool &bSelected, const uint32 &Index)
{
	ListView_SetSelectionMark(this->hWnd, Index);
}

void wcListCtrl::SetStyleEx(const DWORD &StyleEx)
{
	ListView_SetExtendedListViewStyle(this->hWnd, StyleEx);
}
