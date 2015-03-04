#ifndef _WCFL_CONTROLS_LISTBOX_
#define _WCFL_CONTROLS_LISTBOX_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100713
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstrlist.h>

//-----------------------------------------------
// wcListBox -- класc элемента управления списка.
//-----------------------------------------------

enum wcSelectionType {SEL_EXTENDED, SEL_MULTIPLE, SEL_NOSEL, SEL_SINGLE};

class wcListBox: public wcWindow
{
public:
    wcListBox(wcWindow *Parent, const RECT &rct, const uint32 &Style);
    ~wcListBox();

	uint32 AddString(gcString String);
	void AddStrings(gcStrList Strings);
	bool InsertString(const uint32 &Index, gcString String);
	uint32 GetStringsCount();
	bool RemoveString(const uint32 &Index);
	void Clear();

	gcString GetString(const uint32 &Index);
	gcStrList GetStrings();
	
	//Для ListBox'ов с "мультивыделением"
	bool IsSelected(const uint32 &Index);
	bool Select(const uint32 &Index, const bool &bSelect = true);
	uint32 GetSelectionsCount();
	gcDynList<uint32> GetSelections();
	void SetSelections(gcDynList<uint32> Selections);

	//Для ListBox'ов с одиночным выделением
	bool GetCurSelection(uint32 &Index);
	bool SetCurSelection(const bool &bSelected, const uint32 &Index = 0);

	//Проверка параметров и их изменение
	wcSelectionType GetSelectionType(); //Можно выделять только один элемент или несколько?
};

#endif //_WCFL_CONTROLS_LISTBOX_
