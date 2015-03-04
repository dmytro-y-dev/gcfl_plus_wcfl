#ifndef _WCFL_FILEDLG_
#define _WCFL_FILEDLG_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100714
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "window.h"
#include <gcstring.h>

//-----------------------------------------------
// wcFileDialog -- ������ ������ �����.
//-----------------------------------------------

class wcFileDialog: public gcObject
{
public:
	wcFileDialog(wcWindow *mainWnd);
	~wcFileDialog();

	bool ExecuteSaveDialog(const DWORD &Flags = 0, const DWORD &FlagsEx = 0);
	bool ExecuteOpenDialog(const DWORD &Flags = 0, const DWORD &FlagsEx = 0);
public:
	gcString InitialDir;
	gcString Title;
	gcString DefExtension;
	gcString Filter;
	gcString FilePath;
protected:
	wcWindow *wndMain;
};

#endif //_WCFL_FILEDLG_
