#ifndef _WCFL_CONTROLS_COMBOBOX_
#define _WCFL_CONTROLS_COMBOBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100816
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>
#include <gcstrlist.h>

//-----------------------------------------------
// wcGroupBox -- класc элемента управления "группа".
//-----------------------------------------------

class wcComboBox: public wcWindow
{
public:
    wcComboBox(wcWindow *Parent, const RECT &rct, const uint32 &Style);
	~wcComboBox();

	uint32 AddString(gcString String);
	void AddStrings(gcStrList Strings);
	bool InsertString(const uint32 &Index, gcString String);
	uint32 GetStringsCount();
	bool RemoveString(const uint32 &Index);
	void Clear();

	gcString GetString(const uint32 &Index);
	gcStrList GetStrings();
	
	bool GetCurSelection(uint32 &Index);
	bool SetCurSelection(const uint32 &Index, const bool &bSelected = true);
};

#endif //_WCFL_CONTROLS_GROUPBOX_