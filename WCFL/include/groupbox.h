#ifndef _WCFL_CONTROLS_GROUPBOX_
#define _WCFL_CONTROLS_GROUPBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100815
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcGroupBox -- ����c �������� ���������� "������".
//-----------------------------------------------

class wcGroupBox: public wcWindow
{
public:
    wcGroupBox(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();
};

#endif //_WCFL_CONTROLS_GROUPBOX_