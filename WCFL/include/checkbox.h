#ifndef _WCFL_CONTROLS_CHECKBOX_
#define _WCFL_CONTROLS_CHECKBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100816
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcCheckBox -- класc элемента управления "флажок/выбор".
//-----------------------------------------------

class wcCheckBox: public wcWindow
{
public:
    wcCheckBox(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();

	bool IsSelected();
	void SetSelection(const bool &bSelected = true);
};

#endif //_WCFL_CONTROLS_CHECKBOX_
