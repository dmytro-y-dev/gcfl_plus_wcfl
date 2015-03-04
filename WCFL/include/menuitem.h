#ifndef _WCFL_MENUITEM_
#define _WCFL_MENUITEM_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100631
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include "events.h"

class wcMenu;

enum wcMenuType {MIT_NORMAL, MIT_SEPARATOR, MIT_SUBMENU};

//-----------------------------------------------
// wcMenuList -- класc списка дочерних элементов меню.
//-----------------------------------------------

class wcMenuList: public gcDynList<wcMenu>
{
protected:
	wcMenu *Parent;
public:
	wcMenuList() { this->Parent = NULL; }
	wcMenuList(wcMenu *wParent) { this->Parent = wParent; }
		
	bool SetParent(wcMenu *wParent) //Нельзя использовать для уже добавленных в меню списков
	{ if (!Parent) { this->Parent = wParent; return true; } return false; }

	wcMenu *GetParent() { return this->Parent; }

	uint32 Append(wcMenu *itm); //Не используйте эту функцию - это системный вызов
	wcMenu * Append(const wcMenuType &Type, LPCSTR Title); //Используйте эту функцию для добавления меню
	wcMenu * Insert(const uint32 &Index, const wcMenuType &Type, LPCSTR Title);
	bool Delete(const uint32 &Index);

	wcMenu * Find(const uint32 &ID, const bool &bSearchChildren = true);
	wcMenu * Find(const HMENU MenuHandle, const bool &bSearchChildren = true);
};

//-----------------------------------------------
// wcMenu -- класc элемента меню.
//-----------------------------------------------

class wcMenu: public gcObject
{
public:
	wcMenu(wcMenu *Parent, const wcMenuType &Type, LPCSTR Title = NULL);
	wcMenu(wcMenu *Parent, HMENU hMenu, const uint32 &MenuID);
	~wcMenu();

	HMENU GetMenuHandle();
	uint32 GetMenuID();
	bool GetMenuIndex(uint8 &Index);

	virtual bool InputMenuProc(const wcMessage &msg);
protected:
	HMENU hMenu;
	uint32 uMenuID;
public:
	wcMenu *Parent;
	wcMenuList Children;
	wcEventsTable Events;
};

#endif //_WCFL_MENUITEM_