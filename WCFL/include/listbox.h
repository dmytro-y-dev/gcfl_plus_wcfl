#ifndef _WCFL_CONTROLS_LISTBOX_
#define _WCFL_CONTROLS_LISTBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100713
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstrlist.h>

//-----------------------------------------------
// wcListBox -- ����c �������� ���������� ������.
//-----------------------------------------------

enum wcSelectionType {SEL_EXTENDED, SEL_MULTIPLE, SEL_NOSEL, SEL_SINGLE};

class wcListBox: public wcWindow
{
public:
    wcListBox(wcWindow *Parent, const RECT &rct, const uint32 &Style);
    ~wcListBox();

	uint32 AddString(gcString String);
	void AddStrings(gcStrList Strings);
	bool InsertString(const uint32 &Index, gcString String);
	uint32 GetStringsCount();
	bool RemoveString(const uint32 &Index);
	void Clear();

	gcString GetString(const uint32 &Index);
	gcStrList GetStrings();
	
	//��� ListBox'�� � "����������������"
	bool IsSelected(const uint32 &Index);
	bool Select(const uint32 &Index, const bool &bSelect = true);
	uint32 GetSelectionsCount();
	gcDynList<uint32> GetSelections();
	void SetSelections(gcDynList<uint32> Selections);

	//��� ListBox'�� � ��������� ����������
	bool GetCurSelection(uint32 &Index);
	bool SetCurSelection(const bool &bSelected, const uint32 &Index = 0);

	//�������� ���������� � �� ���������
	wcSelectionType GetSelectionType(); //����� �������� ������ ���� ������� ��� ���������?
};

#endif //_WCFL_CONTROLS_LISTBOX_
