#ifndef _WCFL_CONTROLS_BUTTON_
#define _WCFL_CONTROLS_BUTTON_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100631
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcButton -- ����c �������� ���������� ������.
//-----------------------------------------------

class wcButton: public wcWindow
{
public:
    wcButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();
};

#endif //_WCFL_CONTROLS_BUTTON_
