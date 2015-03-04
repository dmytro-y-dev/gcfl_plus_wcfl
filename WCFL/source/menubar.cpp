#include "menubar.h"
#include "topwindow.h"

wcMenuBar::wcMenuBar(): gcObject()
{
	this->MainItm = new wcMenu(NULL, MIT_SUBMENU);
	this->Parent = NULL;
}

wcMenuBar::~wcMenuBar()
{
	if (this->Parent) this->Parent->SetMenubar(NULL);
	DestroyMenu(this->MainItm->GetMenuHandle());
	delete this->MainItm;
}

void wcMenuBar::Update()
{
	if (this->Parent) DrawMenuBar(this->Parent->GetWndHandle());
}

HMENU wcMenuBar::GetBarHandle()
{
	return this->MainItm->GetMenuHandle();
}

wcMenuList & wcMenuBar::GetItems()
{
	return this->MainItm->Children;
}

bool wcMenuBar::InputMenuProc(const wcMessage &msg)
{
	//Распределяет сообщения по элементам меню
	if (msg.uMessageID == WM_COMMAND)
	{
		wcMenu * itmMenu = MainItm->Children.Find(LOWORD(msg.wParam), true);
		if (itmMenu) return itmMenu->InputMenuProc(msg);
	}
	return false;
}