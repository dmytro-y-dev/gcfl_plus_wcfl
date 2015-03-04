#ifndef _WCFL_MENUBAR__
#define _WCFL_MENUBAR__

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100631
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "menuitem.h"

class wcTopWindow;

//-----------------------------------------------
// wcMenuBar -- класc полоски меню для окна.
//-----------------------------------------------

class wcMenuBar: public gcObject
{
public:
	wcMenuBar();
	~wcMenuBar();

	HMENU GetBarHandle();
	wcMenuList & GetItems();
	void Update();

	virtual bool InputMenuProc(const wcMessage &msg);
protected:
	wcMenu *MainItm;
public:
	wcTopWindow *Parent;
};

//Расширение MGUIT
	#define MENUBAR_ADD_ITEM(menuBar, itmName, Caption)					\
	wcMenu *itmName = menuBar->GetItems().Append(MIT_NORMAL, Caption);	\

	#define MENUBAR_ADD_SUBMENU(menuBar, itmName, Caption)				\
	wcMenu *itmName = menuBar->GetItems().Append(MIT_SUBMENU, Caption);	\

	#define MENU_ADD_ITEM(subItmName, itmName, Caption)					\
	wcMenu *itmName = subItmName->Children.Append(MIT_NORMAL, Caption);	\

	#define MENU_ADD_SUBMENU(subItmName, itmName, Caption)				\
	wcMenu *itmName = subItmName->Children.Append(MIT_SUBMENU, Caption);\

	#define MENU_ADD_SEPARATOR(itmName)									\
	itmName->Children.Append(MIT_SEPARATOR, NULL);						\

#endif //_WCFL_MENUBAR__