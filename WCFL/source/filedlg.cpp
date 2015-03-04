#include "filedlg.h"

wcFileDialog::wcFileDialog(wcWindow *mainWnd) : gcObject()
{
	this->wndMain = mainWnd;
}

wcFileDialog::~wcFileDialog()
{
	//
}

bool wcFileDialog::ExecuteOpenDialog(const DWORD &Flags, const DWORD &FlagsEx)
{
	for (uint32 i = 0; i < Filter.Length(); i++) {
		if (Filter[i] == '|') Filter[i] = '\0';
	}
	Filter += '\0';
	
	LPOPENFILENAME ofn = new OPENFILENAME;
	ofn->hInstance = GetModuleHandle(NULL);
	if (wndMain) ofn->hwndOwner = wndMain->GetWndHandle();
	else ofn->hwndOwner = NULL;

	ofn->lpstrTitle = Title.GetCharBuffer();
	ofn->lpstrFilter = Filter.GetCharBuffer();

	ofn->lpstrCustomFilter = NULL;
	ofn->nMaxCustFilter = 0;
	ofn->nFilterIndex = 0;

	ofn->lpstrFile = new CHAR[MAX_PATH];
	if (FilePath.Length() > 0) ofn->lpstrFile = strcpy(ofn->lpstrFile, FilePath.GetCharBuffer());
	ofn->lpstrFile[FilePath.Length()] = '\0';
	ofn->nMaxFile = MAX_PATH;

	ofn->lpstrFileTitle = NULL;
	ofn->nMaxFileTitle = 0;

	ofn->lpfnHook = NULL;
	ofn->lpstrInitialDir = InitialDir.GetCharBuffer();
	ofn->nFileOffset = 0;
	ofn->nFileExtension = 0;
	ofn->lpstrDefExt = DefExtension.GetCharBuffer();
	ofn->lCustData = 0;
	ofn->lpTemplateName = NULL;
	ofn->pvReserved = 0;
	ofn->dwReserved = 0;
	ofn->FlagsEx = FlagsEx;
	ofn->Flags = Flags;

	ofn->lStructSize = sizeof(OPENFILENAME);
	if (GetOpenFileName(ofn))
	{
		FilePath = _T(ofn->lpstrFile);
		delete []ofn->lpstrFile;
		delete ofn;
		return true;
	}

	delete []ofn->lpstrFile;
	delete ofn;

	return false;
}

bool wcFileDialog::ExecuteSaveDialog(const DWORD &Flags, const DWORD &FlagsEx)
{
	for (uint32 i = 0; i < Filter.Length(); i++) {
		if (Filter[i] == '|') Filter[i] = '\0';
	}
	Filter += '\0';
	
	LPOPENFILENAME ofn = new OPENFILENAME;
	ofn->hInstance = GetModuleHandle(NULL);
	if (wndMain) ofn->hwndOwner = wndMain->GetWndHandle();
	else ofn->hwndOwner = NULL;

	ofn->lpstrTitle = Title.GetCharBuffer();
	ofn->lpstrFilter = Filter.GetCharBuffer();

	ofn->lpstrCustomFilter = NULL;
	ofn->nMaxCustFilter = 0;
	ofn->nFilterIndex = 0;

	ofn->lpstrFile = new CHAR[MAX_PATH];
	if (FilePath.Length() > 0) ofn->lpstrFile = strcpy(ofn->lpstrFile, FilePath.GetCharBuffer());
	ofn->lpstrFile[FilePath.Length()] = '\0';
	ofn->nMaxFile = MAX_PATH;

	ofn->lpstrFileTitle = NULL;
	ofn->nMaxFileTitle = 0;

	ofn->lpfnHook = NULL;
	ofn->lpstrInitialDir = InitialDir.GetCharBuffer();
	ofn->nFileOffset = 0;
	ofn->nFileExtension = 0;
	ofn->lpstrDefExt = DefExtension.GetCharBuffer();
	ofn->lCustData = 0;
	ofn->lpTemplateName = NULL;
	ofn->pvReserved = 0;
	ofn->dwReserved = 0;
	ofn->FlagsEx = FlagsEx;
	ofn->Flags = Flags;

	ofn->lStructSize = sizeof(OPENFILENAME);
	if (GetSaveFileName(ofn))
	{
		FilePath = _T(ofn->lpstrFile);
		delete []ofn->lpstrFile;
		delete ofn;
		return true;
	}

	delete []ofn->lpstrFile;
	delete ofn;

	return false;
}
