#include "app.h"
#include "topwindow.h"
#include "menubar.h"

#include "button.h"
#include "edit.h"
#include "static.h"
#include "listbox.h"
#include "mguit.h"

//Глобальные объекты
//ЗАМЕТКА! DEFINE_OBJ и DEFINE_GLOBAL_OBJ - одна и та же функция 
DEFINE_GLOBAL_OBJ(wndMain, wcTopWindow)
DEFINE_GLOBAL_OBJ(MainMenu, wcMenuBar)
DEFINE_OBJ(lstTest, wcListBox)

void CloseApp(const wcMessage &msg)
{
	Application->Terminate(0);
}

void ClickApp(const wcMessage &msg)
{
	MessageBox(wndMain->GetWndHandle(), "OK!", "tst", 0);
	MainMenu->GetItems().Delete(0);
	MainMenu->Update();
}

void MyUserInit()
{
	wndMain->SetMenubar(MainMenu);
	lstTest->AddString(_T("test 1"));
	lstTest->AddString(_T("test 2"));
	lstTest->AddString(_T("test 3"));
}

WCFL_GUI_CONSTRUCTORS()
	//Если вы объявили некоторые объекты глобальными, то перед вызовом CREATE_OBJ
	//нужно сделать ссылки на эти объекты с помощью EXTERN_OBJ
	EXTERN_OBJ(wndMain, wcTopWindow)
	EXTERN_OBJ(MainMenu, wcMenuBar)
	EXTERN_OBJ(lstTest, wcListBox)

	//Если вы не хотите объявлять некоторые объекты глобальными, просто добавьте их объявления внутрь данного блока
	DEFINE_OBJ(btnNew, wcButton)
	DEFINE_OBJ(btnClickMe, wcButton)
	DEFINE_OBJ(stPanel, wcStatic)

	//Собственно создание окон
	CREATE_OBJ(wndMain, wcTopWindow, new wcTopWindow(NULL, _RECT(400, 300, 500, 250), WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, "test"))
	//-- BEGIN wndMain --//
		CREATE_OBJ(stPanel, wcStatic, new wcStatic(wndMain, _RECT(5, 5, 210, 30), WS_VISIBLE | SS_SUNKEN, ""))
		CREATE_OBJ(btnNew, wcButton, new wcButton(wndMain, _RECT(10, 10, 200, 20), WS_VISIBLE, "test"))
		CREATE_OBJ(btnClickMe, wcButton, new wcButton(wndMain, _RECT(10, 35, 200, 20), WS_VISIBLE, "Qool!"))
		CREATE_OBJ(lstTest, wcListBox, new wcListBox(wndMain, _RECT(10, 60, 200, 80), WS_VISIBLE))
		
		CREATE_OBJ(MainMenu, wcMenuBar, new wcMenuBar())
			MENUBAR_ADD_SUBMENU(MainMenu, menuSubTest, "testmenu")
				MENU_ADD_ITEM(menuSubTest, mHi, "hi!")
				MENU_ADD_SEPARATOR(menuSubTest);
				MENU_ADD_ITEM(menuSubTest, mExit, "E&xit")
			MENUBAR_ADD_SUBMENU(MainMenu, menuFile, "File")
				MENU_ADD_ITEM(menuFile, mFileExit, "E&xit")

		ADD_EVENT(mHi, new wcEvent(EVT_DEFAULT, WM_COMMAND, ClickApp))
		ADD_EVENT(mExit, new wcEvent(EVT_DEFAULT, WM_COMMAND, CloseApp))
		ADD_EVENT(mFileExit, new wcEvent(EVT_DEFAULT, WM_COMMAND, CloseApp))

		ADD_EVENT(wndMain, new wcEvent(EVT_DEFAULT, WM_DESTROY, CloseApp))
		ADD_EVENT(btnNew, new wcEvent(EVT_COMMAND, BN_CLICKED, ClickApp))
	//-- END wndMain --//
WCFL_GUI_CONSTRUCTORS_END(MyUserInit)

WCFL_GUI_DESTRUCTORS()
	DELETE_OBJ(MainMenu, wcMenuBar)
WCFL_GUI_DESTRUCTORS_END()
