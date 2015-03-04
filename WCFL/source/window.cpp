#include "window.h"
#include "app.h"

inline LRESULT APIENTRY DefWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	extern wcApplication *Application;
	wcWindow *wndTarget = Application->Windows.GetChild(hWnd, true);
	wcMessage msg(wndTarget, uMsg, wParam, lParam);
	if ((!wndTarget)||(!wndTarget->MessageLoop(msg)))
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	else return 0;
}

wcWindow::wcWindow(wcWindow *Parent, const RECT &rct, const uint32 &Style,
				   const uint32 &StyleEx, LPCSTR ClassName) : gcObject()
{
	this->Parent = Parent;
	if (Parent) Parent->Children.Append(this);
	else Application->Windows.Append(this);

	WNDCLASS wcTemp;
	if (!GetClassInfo(GetModuleHandle(0), ClassName, &wcTemp))
	{
		wcTemp.hInstance = GetModuleHandle(0);
		wcTemp.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcTemp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcTemp.lpszMenuName = NULL;
		wcTemp.lpszClassName = ClassName;
		wcTemp.hbrBackground = (HBRUSH)COLOR_BTNSHADOW;
		wcTemp.style = CS_DROPSHADOW;
		wcTemp.lpfnWndProc = DefWndProc;
		wcTemp.cbClsExtra = 0;
		wcTemp.cbWndExtra = 0;
		RegisterClass(&wcTemp);
	}

	if (Parent) hWnd = CreateWindowEx(StyleEx, ClassName, NULL, Style,
			rct.left, rct.top, rct.right - rct.left, rct.bottom - rct.top,
			Parent->GetWndHandle(), NULL, GetModuleHandle(0), NULL);
	else hWnd = CreateWindowEx(StyleEx, ClassName, NULL, Style,
			rct.left, rct.top, rct.right - rct.left, rct.bottom - rct.top,
			NULL, NULL, GetModuleHandle(0), NULL);
	this->bExists = true;
}

wcWindow::~wcWindow()
{
	if (IsWindowExists())
	{
		DestroyWindow(this->hWnd);
		this->bExists = false;
	}

	if ((Parent)&&(Parent->IsWindowExists()))
	{
		uint32 chld;
		Parent->Children.FindChild(this->GetWndHandle(), chld);
		*((wcWindow **)Parent->Children.Get(chld)) = NULL;
		Parent->Children.Delete(chld);
	}
}

bool wcWindow::IsShown()
{
	long wndLong = GetWindowLong(this->hWnd, GWL_STYLE);
	if ((wndLong & WS_VISIBLE) == WS_VISIBLE) return true;
	return false;
}

bool wcWindow::IsEnabled()
{
	long wndLong = GetWindowLong(this->hWnd, GWL_STYLE);
	if ((wndLong & WS_DISABLED) == WS_DISABLED) return false;
	return true;
}

const HWND wcWindow::GetWndHandle()
{
	return hWnd;
}

RECT wcWindow::GetWndRect()
{
	RECT rct;
	GetWindowRect(this->hWnd, &rct);
	return rct;
}

bool wcWindow::SetWndRect(const RECT &rct)
{
	if (MoveWindow(this->hWnd, rct.left, rct.top, rct.right - rct.left,
					rct.bottom - rct.top, true) == TRUE) return true;
	return false;
}

void wcWindow::Enable(const bool &Enabled)
{
	EnableWindow(this->hWnd, Enabled);
}

void wcWindow::Show(const int &ShowCmd)
{
	ShowWindow(this->hWnd, ShowCmd);
}

bool wcWindow::MessageLoop(const wcMessage &Message)
{
	if (Message.uMessageID == WM_COMMAND)
	{
		if (Message.lParam)
		{
			//Если элемент -- не меню, то...
			if ((HWND)Message.lParam != this->hWnd)
			{
				//Если сообщение для дочернего, то...
				wcWindow * wndTarget = Children.GetChild((HWND)Message.lParam, true);
				if (wndTarget) wndTarget->MessageLoop(Message);
				else return false;
			}
			else
			{
				wcEvent *evt = Events.GetHandler(EVT_COMMAND, HIWORD(Message.wParam));
				if (evt) evt->funcEvent(Message);
				else return false;
			}
		}
		//Если элемент -- меню или ускоритель, то..
		else return false;
	}
	else
	if (Message.uMessageID == WM_NOTIFY)
	{
		if (((LPNMHDR)Message.lParam)->hwndFrom != this->hWnd)
		{
			//Если сообщение от дочернего, то...
			wcWindow * wndTarget = Children.GetChild(((LPNMHDR)Message.lParam)->hwndFrom, true);
			if (wndTarget) wndTarget->MessageLoop(Message);
			else return false;
		}
		else
		{
			wcEvent *evt = Events.GetHandler(EVT_NOTIFY, ((LPNMHDR)Message.lParam)->code);
			if (evt) evt->funcEvent(Message);
			else return false;
		}
	}
	else
	{
		if ((Message.uMessageID == WM_DESTROY)&&(Message.wndTarget->bExists))
		{
			Message.wndTarget->bExists = false;
			wcEvent *evt = Events.GetHandler(EVT_DEFAULT, Message.uMessageID);
			if (evt) evt->funcEvent(Message);
			else return false;
		}
 		else
		if (Message.wndTarget->bExists)
		{
			wcEvent *evt = Events.GetHandler(EVT_DEFAULT, Message.uMessageID);
			if (evt) evt->funcEvent(Message);
			else return false;
		}
	}
	return true;
}

bool wcWindow::IsWindowExists()
{
	return bExists;
}
