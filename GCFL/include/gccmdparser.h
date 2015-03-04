#ifndef _GCFL_CMD_PARSER_
#define _GCFL_CMD_PARSER_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// ���������� �������� ������� � �������
//������ �����: 20100703
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "types_common.h"
#include "gcstring.h"
#include "gclist.h"

//-----------------------------------------------
// gcCmdParam - �������� ���������� ������
//-----------------------------------------------

class gcCmdParam : public gcObject //�������� ���������� ������
{
public:
	gcString Name;
	gcString Value;
};

//-----------------------------------------------
// gcCmdParser - ������ ���������� ������
//-----------------------------------------------

class gcCmdParser : public gcObject //������ ���������� ������
{
protected:
	gcString sCommand;
	gcDynList<gcCmdParam> Params;
public:
	gcCmdParser();
	~gcCmdParser();

	void ParseCmdLine(const gcString &sCmdLine, const uint16 &uParseFrom);

	bool IsParamExists(const gcString &sParamName);
	gcString GetParam(const uint16 &uParamID);
	gcString GetValue(const uint16 &uParamID);
	gcString GetValue(const gcString &sParamName);

	uint16 GetParamsCount() { return Params.Count(); }
	gcString GetCommand() { return sCommand; }
protected:
	int ParseValue(gcCmdParam *Param, const uint16 &uCurChar, const gcString &sCmdLine, const uint16 &uCmdLen);
};

typedef void (* gcCmdEvent)(gcCmdParser &Parser);

struct gcEvent
{
	gcString Name;
	gcCmdEvent Func;
};

//���������� ������������ ������� ��� ���������� �������� �������������
#define DEFINE_DEFAULT_EVENT(Event)									\
gcCmdEvent DefaultEvent;												\
void InitDefEvent()													\
{																	\
	DefaultEvent = Event;											\
}																	\

#define BEGIN_EVENTS_TABLE()\
void ExecEvents(gcCmdParser &Parser)\
{\

//���������� ������� ������������
#define DEFINE_EVENT(Event, Command)\
if (_T(Command) == Parser.GetCommand())\
	Event(Parser);\
else\

#define END_EVENTS_TABLE()\
	DefaultEvent(Parser);\
}\


#define INIT_DEFAULT_PARSER()										\
																	\
extern "C" {														\
																	\
__declspec(dllimport)												\
__out																\
LPSTR																\
__stdcall															\
GetCommandLineA(													\
    void															\
    );																\
																	\
}																	\
																	\
void InitDefEvent();												\
void InitCmdEvent();												\
																	\
gcCmdParser DefaultParser;											\
int main(int argc, char **argv)										\
{																	\
	InitDefEvent();													\
	LPCSTR lpCmdLine = GetCommandLineA();							\
	if (argc > 1)													\
	{																\
		DefaultParser.ParseCmdLine(_T(lpCmdLine), _T(argv[0]).Length() + 1);	\
		ExecEvents(DefaultParser);									\
	}																\
	else DefaultEvent(DefaultParser);								\
	return 0;														\
}																	\

#endif //_GCFL_CMD_PARSER_