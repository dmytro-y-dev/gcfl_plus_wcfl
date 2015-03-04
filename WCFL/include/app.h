#ifndef _WCFL_APPLICATION_
#define _WCFL_APPLICATION_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 20100630
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include "wnd_list.h"

//-----------------------------------------------
//wcApplication -- класc приложения. Используется для
// контроля действий программы, правильной ее инициализации
// и уничтожения, а также для контроля списка окон.
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
