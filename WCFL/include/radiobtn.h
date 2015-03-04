#ifndef _WCFL_CONTROLS_RADIO_BTN_
#define _WCFL_CONTROLS_RADIO_BTN_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100815
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcRadioButton -- класc элемента управления "выбор одного из нескольких".
//-----------------------------------------------

class wcRadioButton: public wcWindow
{
public:
    wcRadioButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();

	bool IsSelected();
	void SetSelection(const bool &bSelected = true);
};

#endif //_WCFL_CONTROLS_RADIO_BTN_
