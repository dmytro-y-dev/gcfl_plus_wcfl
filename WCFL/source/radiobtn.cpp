#include "radiobtn.h"

wcRadioButton::wcRadioButton(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Title) :
	wcWindow(Parent, rct, Style | WS_CHILD | BS_AUTORADIOBUTTON | BS_TEXT,
			WS_EX_NOPARENTNOTIFY, WC_BUTTON)
{
	HFONT hFnt = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)hFnt, TRUE);

	SetCaption(Title);
}

bool wcRadioButton::SetCaption(gcString Caption)
{
	if (SetWindowText(this->hWnd, Caption.GetCharBuffer())) return true;
	return false;
}

gcString wcRadioButton::GetCaption()
{
	int iTextLen = GetWindowTextLength(this->hWnd);
	if (iTextLen < 1) return EmptyStr;
	LPSTR sCaption = new CHAR[iTextLen + 1];
	GetWindowText(this->hWnd, sCaption, iTextLen + 1);
	gcString Text = _T(sCaption);
	delete []sCaption;
	return Text;
}

bool wcRadioButton::IsSelected()
{
	if (SendMessage(hWnd, BM_GETCHECK, 0, 0) == BST_CHECKED) return true;
	return false;
}

void wcRadioButton::SetSelection(const bool &bSelected)
{
	if (bSelected) SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
	else SendMessage(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
}
