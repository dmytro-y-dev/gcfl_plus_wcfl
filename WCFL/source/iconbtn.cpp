#include "iconbtn.h"

wcIconButton::wcIconButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, HICON Icon) :
	wcWindow(Parent, rct, Style | WS_CHILD | BS_ICON | BS_PUSHBUTTON,
		WS_EX_NOPARENTNOTIFY, WC_BUTTON)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);

	SetIcon(Icon);
}

wcIconButton::~wcIconButton()
{
	//
}

void wcIconButton::SetIcon(HICON Icon)
{
	SendMessage(this->hWnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)Icon);
}

HICON wcIconButton::GetIcon()
{
	return (HICON)SendMessage(this->hWnd, BM_GETIMAGE, IMAGE_ICON, NULL);
}
