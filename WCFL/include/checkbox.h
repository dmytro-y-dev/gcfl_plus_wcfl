#ifndef _WCFL_CONTROLS_CHECKBOX_
#define _WCFL_CONTROLS_CHECKBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100816
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcCheckBox -- ����c �������� ���������� "������/�����".
//-----------------------------------------------

class wcCheckBox: public wcWindow
{
public:
    wcCheckBox(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();

	bool IsSelected();
	void SetSelection(const bool &bSelected = true);
};

#endif //_WCFL_CONTROLS_CHECKBOX_
