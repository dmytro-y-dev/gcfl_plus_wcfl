#ifndef _WCFL_MACROS_GUI_TOOLKIT_
#define _WCFL_MACROS_GUI_TOOLKIT_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 2010.06.31
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include "app.h"

//-----------------------------------------------
// MACROS_GUI_TOOLKIT (MGUIT)
//  ��� ��� �����? ��� ����� �������� ��� ��������
//  �������� ����������.
//-----------------------------------------------

//����������� ������������� ����������
#define WCFL_GUI_CONSTRUCTORS()						\
class wcMyApp: public wcApplication					\
{													\
public:												\
    bool OnInit();									\
    int OnQuit();									\
};													\
													\
IMPLEMENT_APP(wcMyApp)								\
													\
bool wcMyApp::OnInit()								\
{													\

//����� ����������� �������������
#define WCFL_GUI_CONSTRUCTORS_END(UserInit)			\
	UserInit();										\
	return true;									\
}													\

//����������� ������������ ����������
#define WCFL_GUI_DESTRUCTORS()						\
int wcMyApp::OnQuit()								\
{													\

//����� ����������� ������������
#define WCFL_GUI_DESTRUCTORS_END()					\
	return 0;										\
}													\

#define CREATE_OBJ(name, objlink)				\
name = objlink;										\

#define DELETE_OBJ(name, type)						\
delete name;										\

#define ADD_EVENT(targetname, evtlink)				\
targetname->Events.Append(evtlink);				\

//�������� ������
#define DEFINE_OBJ(name, type)						\
type *name = NULL;									\

#define DEFINE_GLOBAL_OBJ(name, type) DEFINE_OBJ(name, type)

//�������� ������, ��� ���������� �����
#define EXTERN_OBJ(name, type)						\
extern type *name;									\

#endif //_WCFL_MACROS_GUI_TOOLKIT_
