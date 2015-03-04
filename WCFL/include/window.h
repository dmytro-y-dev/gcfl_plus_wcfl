#ifndef _WCFL_WINDOW_
#define _WCFL_WINDOW_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100631
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include "wnd_list.h"
#include "events.h"

//-----------------------------------------------
//wcWindow -- ������� ����� ����. �� ���� ������
// ������������ ��� ��������� �������� ����������.
//-----------------------------------------------

class wcWindow: public gcObject
{
public:
    wcWindow(wcWindow *Parent, const RECT &rct, const uint32 &Style,
		const uint32 &StyleEx, LPCSTR ClassName);
    ~wcWindow();

	bool IsShown();
	bool IsEnabled();

	const HWND GetWndHandle();
	RECT GetWndRect();
	bool SetWndRect(const RECT &rct);

	void Enable(const bool &Enabled = true);
	void Show(const int &ShowCmd = SW_SHOW);

	virtual bool MessageLoop(const wcMessage &Message);
	bool IsWindowExists();
protected:
	HWND hWnd;
	bool bExists;
public:
	wcWindow *Parent;
	wcWindowsList Children;
	wcEventsTable Events;
};

#endif //_WCFL_WINDOW_
