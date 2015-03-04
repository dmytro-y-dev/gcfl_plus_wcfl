#include "menuitem.h"

uint32 uNextMenuID = 1; //Индекс идентификатора следующего элемента-меню для добавления

wcMenu::wcMenu(wcMenu *menuParent, const wcMenuType &Type, LPCSTR Title) : gcObject()
{
	this->Children.SetParent(this);
	this->hMenu = NULL;
	this->uMenuID = 0;

	this->Parent = menuParent;
	if ((!menuParent)&&(Type == MIT_SUBMENU)) this->hMenu = CreateMenu();
	else if (menuParent)
	{
		this->hMenu = NULL;
		this->uMenuID = 0;
		switch (Type)
		{
		case MIT_NORMAL:
			AppendMenu(Parent->GetMenuHandle(), MF_STRING, uNextMenuID, Title);
			this->uMenuID = uNextMenuID; uNextMenuID++;
			break;
		case MIT_SEPARATOR:
			AppendMenu(Parent->GetMenuHandle(), MF_SEPARATOR, NULL, NULL);
			break;
		case MIT_SUBMENU:
			this->hMenu = CreatePopupMenu();
			AppendMenu(Parent->GetMenuHandle(), MF_POPUP | MF_STRING, (UINT_PTR)this->hMenu, Title);
			break;
		};
		Parent->Children.Append(this);
	}
}

//Этот конструктор только для уже созданных меню!
wcMenu::wcMenu(wcMenu *menuParent, HMENU MenuH, const uint32 &MenuID) : gcObject()
{
	this->Children.SetParent(this);
	this->hMenu = MenuH;
	this->uMenuID = MenuID;

	this->Parent = menuParent;
	Parent->Children.Append(this);
}

wcMenu::~wcMenu()
{
	uint8 uIndex = 0;
	if (GetMenuIndex(uIndex)) RemoveMenu(Parent->GetMenuHandle(), uIndex, MF_BYPOSITION);
}


HMENU wcMenu::GetMenuHandle()
{
	return this->hMenu;
}

uint32 wcMenu::GetMenuID()
{
	return this->uMenuID;
}

bool wcMenu::GetMenuIndex(uint8 &Index)
{
	if (!Parent) return false;
	uint8 uIndex = 0;
	uint8 uCount = Parent->Children.Count();

	for (; uIndex < uCount; uIndex++) if (Parent->Children[uIndex] == this) break;
	if (uIndex == uCount) return false;
	Index = uIndex;
	return true;
}

bool wcMenu::InputMenuProc(const wcMessage &msg)
{
	wcEvent *evt;
	if ((evt = Events.GetHandler(EVT_DEFAULT, msg.uMessageID)) != NULL)
	{
		evt->funcEvent(msg);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////
//
//		wcMenuList class
//
/////////////////////////////////////////////////////

uint32 wcMenuList::Append(wcMenu *itm)
{
	uint32 uIndex = gcDynList::Append(NULL);
	this->Items->Content = itm;
	return uIndex;
}

wcMenu * wcMenuList::Append(const wcMenuType &Type, LPCSTR Title)
{
	wcMenu *bufMenu = new wcMenu(Parent, Type, Title);
	return bufMenu;
}

bool wcMenuList::Delete(const uint32 &Index)
{
	wcMenu *bufMenu = Get(Index);
	if (!bufMenu) return false;
	gcDynList::Delete(Index);
	return true;
}

wcMenu * wcMenuList::Insert(const uint32 &Index, const wcMenuType &Type, LPCSTR Title)
{
	wcMenu *bufMenu;
	switch (Type)
	{
	case MIT_NORMAL:
		InsertMenu(Parent->GetMenuHandle(), Index, MF_BYPOSITION | MF_STRING, uNextMenuID, Title);
		bufMenu = new wcMenu(Parent, NULL, uNextMenuID);
		uNextMenuID++;
		break;
	case MIT_SEPARATOR:
		InsertMenu(Parent->GetMenuHandle(), Index, MF_BYPOSITION | MF_SEPARATOR, NULL, NULL);
		bufMenu = new wcMenu(Parent, NULL, 0);
		break;
	case MIT_SUBMENU:
		HMENU hMenu = CreatePopupMenu();
		InsertMenu(Parent->GetMenuHandle(), Index, MF_BYPOSITION | MF_POPUP | MF_STRING,
			(UINT_PTR)hMenu, Title);
		bufMenu = new wcMenu(Parent, hMenu, 0);
		break;
	};
	return bufMenu;
}

wcMenu * wcMenuList::Find(const uint32 &ID, const bool &bSearchChildren)
{
	for (uint32 i = 0; i < Count(); i++)
	{
		wcMenu *menu = this->Get(i);
		if (menu->GetMenuID() == ID) return menu;
		else
		if (bSearchChildren)
		{
			menu = menu->Children.Find(ID, true);
			if (menu) return menu;
		}
	}
	return NULL;
}

wcMenu * wcMenuList::Find(const HMENU MenuHandle, const bool &bSearchChildren)
{
	for (uint32 i = 0; i < Count(); i++)
	{
		wcMenu *menu = this->Get(i);
		if (menu->GetMenuHandle() == MenuHandle) return menu;
		else
		if (bSearchChildren)
		{
			menu = menu->Children.Find(MenuHandle, true);
			if (menu) return menu;
		}
	}
	return NULL;
}