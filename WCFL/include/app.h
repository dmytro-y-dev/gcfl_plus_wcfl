#ifndef _WCFL_APPLICATION_
#define _WCFL_APPLICATION_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100630
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include "wnd_list.h"

//-----------------------------------------------
//wcApplication -- ����c ����������. ������������ ���
// �������� �������� ���������, ���������� �� �������������
// � �����������, � ����� ��� �������� ������ ����.
//-----------------------------------------------

class wcApplication: public gcObject
{
public:
    wcApplication();
    ~wcApplication();

    virtual void MessageLoop();

	void SetIcon(HICON Icon = NULL);
	HICON GetIcon();

	bool IsRunning();
	void Terminate(const int &iResult = 0);

    virtual bool OnInit() = 0;
    virtual int OnQuit() = 0;
protected:
	bool bRunning;
public:
	wcWindowsList Windows;
};

extern wcApplication *Application;

#define IMPLEMENT_APP(app_class)                        \
                                                        \
int APIENTRY WinMain(HINSTANCE hInst,                   \
        HINSTANCE hPrevInst, LPSTR lpCmd, int ShowCmd)  \
{                                                       \
	extern wcApplication *Application;					\
    Application = new app_class();                      \
                                                        \
    if (Application->OnInit()) Application->MessageLoop();\
                                                        \
    int iResult = Application->OnQuit();                \
    delete (app_class *)Application;                    \
    return iResult;                                     \
}                                                       \

#endif //_WCFL_APPLICATION_
