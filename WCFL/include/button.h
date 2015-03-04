#ifndef _WCFL_CONTROLS_BUTTON_
#define _WCFL_CONTROLS_BUTTON_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100631
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcButton -- класc элемента управления кнопки.
//-----------------------------------------------

class wcButton: public wcWindow
{
public:
    wcButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();
};

#endif //_WCFL_CONTROLS_BUTTON_
