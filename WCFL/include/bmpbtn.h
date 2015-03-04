#ifndef _WCFL_CONTROLS_BMPBUTTON_
#define _WCFL_CONTROLS_BMPBUTTON_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100714
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"

//-----------------------------------------------
// wcBitmapButton -- ����c �������� ���������� ������-��������.
//-----------------------------------------------							

class wcBitmapButton: public wcWindow
{
public:
    wcBitmapButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, HBITMAP Bitmap);
    ~wcBitmapButton();

	void SetBitmap(HBITMAP Bitmap);
	HBITMAP GetBitmap();
};

#endif //_WCFL_CONTROLS_BMPBUTTON_
