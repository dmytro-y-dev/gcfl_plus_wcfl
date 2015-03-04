#include "edit.h"

wcEdit::wcEdit(wcWindow *Parent, const RECT &rct, const uint32 &Style, gcString Text) :
	wcWindow(Parent, rct, Style | WS_CHILD, WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE, WC_EDIT)
{
	LOGFONT lf;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfClipPrecision = 2;
	lf.lfEscapement = 0;

	strcpy_s(lf.lfFaceName, "Tahoma");

	lf.lfHeight = -11;
	lf.lfItalic = 0;
	lf.lfOrientation = 0;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfPitchAndFamily = 0;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfStrikeOut = 0;
	lf.lfUnderline = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfWidth = 0;

    HFONT hTextFont = CreateFontIndirect(&lf);
	SetTextFont(hTextFont);

	SetText(Text.GetCharBuffer());
}

wcEdit::~wcEdit()
{
	//
}

bool wcEdit::SetText(gcString sText)
{
	if (SetWindowText(this->hWnd, sText.GetCharBuffer())) return true;
	return false;
}

gcString wcEdit::GetText()
{
	int iTextLen = GetWindowTextLength(this->hWnd);
	if (iTextLen < 1) return EmptyStr;
	LPSTR sText = new CHAR[iTextLen + 1];
	GetWindowText(this->hWnd, sText, iTextLen + 1);
	gcString Text = _T(sText);
	delete []sText;
	return Text;
}

uint32 wcEdit::GetTextLen()
{
	return SendMessage(this->hWnd, WM_GETTEXTLENGTH, NULL, NULL);
}

void wcEdit::SetTextFont(HFONT Font)
{
	SendMessage(this->hWnd, WM_SETFONT, (WPARAM)Font, TRUE);
}

HFONT wcEdit::GetTextFont()
{
	return (HFONT)SendMessage(this->hWnd, WM_GETFONT, NULL, NULL);
}