#ifndef _WCFL_CONTROLS_LISTCTRL_
#define _WCFL_CONTROLS_LISTCTRL_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100714
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstrlist.h>

//-----------------------------------------------
// wcListCtrl -- ����c �������� ���������� ������.
//-----------------------------------------------

class wcListCtrl: public wcWindow
{
public:
    wcListCtrl(wcWindow *Parent, const RECT &rct, const uint32 &Style);
    ~wcListCtrl();

	uint32 GetItemsCount();

	//������� ��� ������ �� �������� (������)
	uint32 AddRow();
	bool InsertRow(const uint32 &RowIndex);
	bool SetString(const uint32 &RowIndex, const uint32 &ColumnIndex, gcString String);
	gcString GetString(const uint32 &RowIndex, const uint32 &ColumnIndex);
	bool RemoveRow(const uint32 &RowIndex);

	//������� ��� ������ � ����������
	uint32 AddColumn(gcString String, const uint32 &uWidth);
	void AddColumns(gcStrList Strings, gcDynList<uint32> uWidths);
	bool InsertColumn(const uint32 &ColumnIndex, const uint32 &uWidth, gcString String);
	uint32 GetColumnsCount();
	bool RemoveColumn(const uint32 &ColumnIndex);
	void ClearAll();

	gcString GetColumn(const uint32 &ColumnIndex);

	//��� ListCtrl'�� � ��������� ����������
	bool GetCurSelection(uint32 &Index);
	void SetCurSelection(const bool &bSelected, const uint32 &Index = 0);

	void SetStyleEx(const DWORD &StyleEx);
protected:
	uint32 uColumnsCount;
};

#endif //_EWL_LIST_CTRL_H_
