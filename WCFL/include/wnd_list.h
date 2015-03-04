#ifndef _WCFL_WINDOWS_LIST_
#define _WCFL_WINDOWS_LIST_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100631
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include <gclist.h>

class wcWindow;

//-----------------------------------------------
// wcWindowsList -- ������ ����
//-----------------------------------------------

class wcWindowsList: public gcDynList<wcWindow>
{
public:
	wcWindow * GetChild(const HWND hWnd, const bool &bSearchChildren);
	bool FindChild(const HWND hWnd, uint32 &Index);
};

#endif //_WCFL_WINDOWS_LIST_
