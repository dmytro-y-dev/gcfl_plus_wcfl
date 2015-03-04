#ifndef _WCFL_CONTROLS_GROUPBOX_
#define _WCFL_CONTROLS_GROUPBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100815
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcGroupBox -- класc элемента управления "группа".
//-----------------------------------------------

class wcGroupBox: public wcWindow
{
public:
    wcGroupBox(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title);

	bool SetCaption(gcString Caption);
	gcString GetCaption();
};

#endif //_WCFL_CONTROLS_GROUPBOX_