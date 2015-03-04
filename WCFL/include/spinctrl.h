#ifndef _WCFL_CONTROLS_SPINCTRL_
#define _WCFL_CONTROLS_SPINCTRL_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100714
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include "edit.h"

//-----------------------------------------------
// wcUpDown -- ����c �������� ���������� ������ ���������� ������.
//-----------------------------------------------

class wcUpDown: public wcWindow
{
public:
    wcUpDown(wcWindow *Parent, const RECT &rct, const uint32 &Style, const int &MinValue,
		const int &MaxValue, const int &Value);
    ~wcUpDown();

	void SetValue(const int &Value);
	bool GetValue(int &Value);

	void SetRange(const int &MinValue, const int &MaxValue);
};

//-----------------------------------------------
// wcSpinCtrl -- ����c �������� ���������� ���� � ������.
//-----------------------------------------------

class wcSpinCtrl: public wcUpDown
{
public:
    wcSpinCtrl(wcWindow *Parent, const RECT &rct, const uint32 &Style, const int &MinValue,
		const int &MaxValue, const int &Value);
    ~wcSpinCtrl();

	void SetTextFont(HFONT Font);
	HFONT GetTextFont();
public:
	wcEdit *ctrlEdit;
};

#endif //_EWL_EDIT_H_
