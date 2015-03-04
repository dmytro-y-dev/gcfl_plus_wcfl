#ifndef _WCFL_MACROS_GUI_TOOLKIT_
#define _WCFL_MACROS_GUI_TOOLKIT_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// Библиотека классов и функций для работы с окнами
//Версия файла: 2010.06.31
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "wcfl_main.h"
#include "app.h"

//-----------------------------------------------
// MACROS_GUI_TOOLKIT (MGUIT)
//  Что это такое? Это набор макросов для быстрого
//  создания интерфейса.
//-----------------------------------------------

//Определение конструкторов приложения
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

//Конец определений конструкторов
#define WCFL_GUI_CONSTRUCTORS_END(UserInit)			\
	UserInit();										\
	return true;									\
}													\

//Определение деструкторов приложения
#define WCFL_GUI_DESTRUCTORS()						\
int wcMyApp::OnQuit()								\
{													\

//Конец определений деструкторов
#define WCFL_GUI_DESTRUCTORS_END()					\
	return 0;										\
}													\

#define CREATE_OBJ(name, objlink)				\
name = objlink;										\

#define DELETE_OBJ(name, type)						\
delete name;										\

#define ADD_EVENT(targetname, evtlink)				\
targetname->Events.Append(evtlink);				\

//Объявить объект
#define DEFINE_OBJ(name, type)						\
type *name = NULL;									\

#define DEFINE_GLOBAL_OBJ(name, type) DEFINE_OBJ(name, type)

//Объявить объект, уже объявленый ранее
#define EXTERN_OBJ(name, type)						\
extern type *name;									\

#endif //_WCFL_MACROS_GUI_TOOLKIT_
