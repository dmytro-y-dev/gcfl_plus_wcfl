#include "app.h"
#include "window.h"

const uint32 USR_MSG_PROC = 1000;

wcApplication *Application; //Главный обьект-приложение

wcApplication::wcApplication() : gcObject()
{
    this->bRunning = true;
}

wcApplication::~wcApplication()
{
	//Windows.Clear();
}

bool wcApplication::IsRunning()
{
	return this->bRunning;
}

void wcApplication::MessageLoop()
{
	MSG curMessage; BOOL bRet;
	while ((bRet = GetMessage(&curMessage, NULL, 0, 0 )) != 0)
	{
		if (bRet == -1) break;
		else
		{
			TranslateMessage(&curMessage);
			DispatchMessage(&curMessage);
		}
	}
}

void wcApplication::Terminate(const int &iResult)
{
	this->bRunning = false;
	PostQuitMessage(iResult);
}

void wcApplication::SetIcon(HICON Icon)
{
	if (Windows[0]) SendMessage(Windows[0]->GetWndHandle(), WM_SETICON, ICON_SMALL2, (LPARAM)Icon);
}

HICON wcApplication::GetIcon()
{
	if (Windows[0]) return (HICON)SendMessage(Windows[0]->GetWndHandle(), WM_GETICON, ICON_SMALL2, NULL);
	else return NULL;
}

