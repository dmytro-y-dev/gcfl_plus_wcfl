#ifndef _WCFL_CONTROLS_STATIC_
#define _WCFL_CONTROLS_STATIC_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100713
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcStatic -- класc элемента управления статического элемента.
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
