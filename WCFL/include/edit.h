#ifndef _WCFL_CONTROLS_EDIT_
#define _WCFL_CONTROLS_EDIT_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100713
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcEdit -- класc элемента управления текстового редактора.
//-----------------------------------------------					

class wcEdit: public wcWindow
{
public:
    wcEdit(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Text);
    ~wcEdit();

	bool SetText(gcString sText);
	uint32 GetTextLen();
	gcString GetText();

	void SetTextFont(HFONT Font);
	HFONT GetTextFont();
};

#endif //_WCFL_CONTROLS_EDIT_
