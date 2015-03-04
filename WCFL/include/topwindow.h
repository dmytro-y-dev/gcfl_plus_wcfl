#ifndef _WCFL_TOP_WINDOW_
#define _WCFL_TOP_WINDOW_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100631
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include "menubar.h"

#ifdef _WIN32
// Top Window Class Name
#define WC_TOPWINDOWA				"TopWindow"
#define WC_TOPWINDOWW				L"TopWindow"

#ifdef UNICODE
#define WC_TOPWINDOW				WC_TOPWINDOWW
#else
#define WC_TOPWINDOW				WC_TOPWINDOWA
#endif

#else //Non _WIN32
#define WC_TOPWINDOW				"TopWindow"
#endif

//-----------------------------------------------
//wcTopWindow -- класc "верхнего" окна приложения.
// Используется как основной контейнер для всех
// других окон.
//-----------------------------------------------

class wcTopWindow: public wcWindow
{
public:
    wcTopWindow(wcWindow *Parent, const RECT &rct, const uint32 &Style, const uint32 &StyleEx, LPCSTR Title);
    ~wcTopWindow();

	bool SetCaption(LPCSTR sCaption);
	LPSTR GetCaption();

	void SetIcon(HICON Icon, const bool &bSmallIcon);
	HICON GetIcon(const bool &bSmallIcon);

	void SetMenubar(wcMenuBar *Menubar);
	wcMenuBar * GetMenuBar();

	void Close();

	virtual bool MessageLoop(const wcMessage &Message);
protected:
	wcMenuBar *barMenu;
};

#endif //_WCFL_TOP_WINDOW_
