#ifndef _WCFL_CONTROLS_ICONBUTTON_
#define _WCFL_CONTROLS_ICONBUTTON_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100714
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"

//-----------------------------------------------
// wcIconButton -- ����c �������� ���������� ������ � �������.
//-----------------------------------------------									

class wcIconButton: public wcWindow
{
public:
    wcIconButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, HICON Icon);
    ~wcIconButton();

	void SetIcon(HICON Icon);
	HICON GetIcon();
};

#endif //_WCFL_CONTROLS_ICONBUTTON_
