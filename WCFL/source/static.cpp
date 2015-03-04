#include "static.h"

wcStatic::wcStatic(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Text) :
	wcWindow(Parent, rct, Style | WS_CHILD, WS_EX_NOPARENTNOTIFY, WC_STATIC)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);

	SetText(Text);
}

wcStatic::~wcStatic()
{
	//
}

bool wcStatic::SetText(gcString Text)
{
	if (SetWindowText(this->hWnd, Text.GetCharBuffer())) return true;
	return false;
}

gcString wcStatic::GetText()
{
	int iTextLen = GetWindowTextLength(this->hWnd);
	if (iTextLen < 1) return EmptyStr;
	LPSTR Text = new CHAR[iTextLen + 1];
	GetWindowText(this->hWnd, Text, iTextLen + 1);
	gcString str = _T(Text);
	delete []Text;
	return str;
}

void wcStatic::SetIcon(HICON Icon)
{
	SendMessage(this->hWnd, STM_SETICON, (WPARAM)Icon, NULL);
}

HICON wcStatic::GetIcon()
{
	return (HICON)SendMessage(this->hWnd, STM_GETICON, NULL, NULL);
}

void wcStatic::SetBitmap(HBITMAP Bitmap)
{
	SendMessage(this->hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bitmap);
}

HBITMAP wcStatic::GetBitmap()
{
	return (HBITMAP)SendMessage(this->hWnd, STM_GETIMAGE, IMAGE_BITMAP, NULL);
}
