#ifndef _WCFL_CONTROLS_PROGRESSBAR_
#define _WCFL_CONTROLS_PROGRESSBAR_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100713
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"

//-----------------------------------------------
// wcProgressBar -- класc элемента управления бегущей/процентной полоски.
//-----------------------------------------------						

class wcProgressBar: public wcWindow
{
public:
    wcProgressBar(wcWindow *Parent, const RECT &rct, const uint32 &Style, const uint32 &MinValue,
		const uint32 &MaxValue, const uint32 &Value);
    ~wcProgressBar();

	void SetValue(const uint32 &Value);
	uint32 GetValue();

	void SetStep(const uint32 &Value);
	uint32 GetStep();
	void Step();

	void SetRange(const uint32 &MinValue, const uint32 &MaxValue);
};

#endif //_WCFL_CONTROLS_PROGRESSBAR_
