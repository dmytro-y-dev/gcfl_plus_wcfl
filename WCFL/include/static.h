#ifndef _WCFL_CONTROLS_STATIC_
#define _WCFL_CONTROLS_STATIC_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100713
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcStatic -- ����c �������� ���������� ������������ ��������.
//-----------------------------------------------								

class wcStatic: public wcWindow
{
public:
    wcStatic(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Text);
    ~wcStatic();

	bool SetText(gcString Text);
	gcString GetText();

	void SetIcon(HICON Icon);
	HICON GetIcon();

	void SetBitmap(HBITMAP Bitmap);
	HBITMAP GetBitmap();
};

#endif //_WCFL_CONTROLS_STATIC_
