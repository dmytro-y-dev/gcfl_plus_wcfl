#ifndef _WCFL_CONTROLS_SPINCTRL_
#define _WCFL_CONTROLS_SPINCTRL_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100714
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include "edit.h"

//-----------------------------------------------
// wcUpDown -- класc элемента управления кнопок управления числом.
//-----------------------------------------------

class wcUpDown: public wcWindow
{
public:
    wcUpDown(wcWindow *Parent, const RECT &rct, const uint32 &Style, const int &MinValue,
		const int &MaxValue, const int &Value);
    ~wcUpDown();

	void SetValue(const int &Value);
	bool GetValue(int &Value);

	void SetRange(const int &MinValue, const int &MaxValue);
};

//-----------------------------------------------
// wcSpinCtrl -- класc элемента управления поля с числом.
//-----------------------------------------------

class wcSpinCtrl: public wcUpDown
{
public:
    wcSpinCtrl(wcWindow *Parent, const RECT &rct, const uint32 &Style, const int &MinValue,
		const int &MaxValue, const int &Value);
    ~wcSpinCtrl();

	void SetTextFont(HFONT Font);
	HFONT GetTextFont();
public:
	wcEdit *ctrlEdit;
};

#endif //_EWL_EDIT_H_
