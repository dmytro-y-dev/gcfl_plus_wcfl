#ifndef _WCFL_CONTROLS_ICONBUTTON_
#define _WCFL_CONTROLS_ICONBUTTON_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100714
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"

//-----------------------------------------------
// wcIconButton -- класc элемента управления кнопки с иконкой.
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
