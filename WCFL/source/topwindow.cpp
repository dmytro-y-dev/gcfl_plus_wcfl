#include "topwindow.h"

wcTopWindow::wcTopWindow(wcWindow *Parent, const RECT &rct, const uint32 &Style,
					   const uint32 &StyleEx, LPCSTR Title) :
	wcWindow(Parent, rct, Style, StyleEx | WS_EX_NOPARENTNOTIFY, WC_TOPWINDOW)
{
	SetCaption(Title);
	this->barMenu = NULL;
}

wcTopWindow::~wcTopWindow()
{
	if (this->barMenu) this->barMenu->Parent = NULL;
}

bool wcTopWindow::SetCaption(LPCSTR sCaption)
{
	if (SetWindowText(this->hWnd, sCaption)) return true;
	return false;
}

LPSTR wcTopWindow::GetCaption()
{
	int iTextLen = GetWindowTextLength(this->hWnd);
	if (iTextLen < 1) return NULL;
	LPSTR sCaption = new CHAR[iTextLen + 1];
	GetWindowText(this->hWnd, sCaption, iTextLen + 1);
	return sCaption;
}

void wcTopWindow::SetIcon(HICON Icon, const bool &bSmallIcon)
{
	if (bSmallIcon) SendMessage(this->hWnd, WM_SETICON, ICON_SMALL, (LPARAM)Icon);
	else SendMessage(this->hWnd, WM_SETICON, ICON_BIG, (LPARAM)Icon);
}

HICON wcTopWindow::GetIcon(const bool &bSmallIcon)
{
	if (bSmallIcon) return (HICON)SendMessage(this->hWnd, WM_GETICON, ICON_SMALL, NULL);
	else return (HICON)SendMessage(this->hWnd, WM_GETICON, ICON_BIG, NULL);
}

void wcTopWindow::Close()
{
	DestroyWindow(this->hWnd);
}

bool wcTopWindow::MessageLoop(const wcMessage &Message)
{
	if (Message.uMessageID == WM_COMMAND)
	{
		if ((HIWORD(Message.wParam) == 0)&&(Message.lParam == 0))
		{
			//Если элемент -- меню, то..
			if (barMenu) return barMenu->InputMenuProc(Message);
			else
			return false;
		}
		else return wcWindow::MessageLoop(Message);
	}
	else return wcWindow::MessageLoop(Message);
}

void wcTopWindow::SetMenubar(wcMenuBar *Menubar)
{
	barMenu = Menubar;
	if (Menubar)
	{
		SetMenu(this->hWnd, Menubar->GetBarHandle());
		Menubar->Parent = this;
	}
	else SetMenu(this->hWnd, NULL);
}

wcMenuBar * wcTopWindow::GetMenuBar()
{
	return barMenu;
}