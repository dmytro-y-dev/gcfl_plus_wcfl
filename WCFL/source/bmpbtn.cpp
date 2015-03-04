#include "bmpbtn.h"

wcBitmapButton::wcBitmapButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, HBITMAP Bitmap) :
	wcWindow(Parent, rct, Style | WS_CHILD | BS_BITMAP | BS_PUSHBUTTON,
		WS_EX_NOPARENTNOTIFY, WC_BUTTON)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);

	SetBitmap(Bitmap);
}

wcBitmapButton::~wcBitmapButton()
{
	//
}

void wcBitmapButton::SetBitmap(HBITMAP Bitmap)
{
	SendMessage(this->hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bitmap);
}

HBITMAP wcBitmapButton::GetBitmap()
{
	return (HBITMAP)SendMessage(this->hWnd, BM_GETIMAGE, IMAGE_BITMAP, NULL);
}
