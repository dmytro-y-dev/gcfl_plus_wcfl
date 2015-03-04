#ifndef _WCFL_EVENTS_
#define _WCFL_EVENTS_

//-----------------------------------------------
//WCFL -- Windows Classes and Functions Library
// ���������� ������� � ������� ��� ������ � ������
//������ �����: 20100631
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include <gclist.h>

class wcWindow;

//-----------------------------------------------
// wcMessage -- ����c ���������, ���������� ��������
//-----------------------------------------------

class wcMessage: public gcObject
{
public:
	wcWindow *wndTarget;
	uint32 uMessageID;
	uint32 wParam;
	long lParam;
	wcMessage(wcWindow *Target, const uint32 &MessageID, const uint32 &WParam, const long &LParam) :
		wndTarget(Target), uMessageID(MessageID), wParam(WParam), lParam(LParam) {;}
	wcMessage() : wndTarget(NULL), uMessageID(0), wParam(0), lParam(0) {;}
};

typedef void (* EVTPROC)(const wcMessage &);
enum wcEventType {EVT_NOTIFY, EVT_COMMAND, EVT_DEFAULT};

//-----------------------------------------------
//wcEvent -- ����c �������, ����������� ����������
// �� ������� ����������.
//-----------------------------------------------

class wcEvent: public gcObject
{
public:
	const wcEventType evtType;
	const uint32 uMessageID;
	EVTPROC funcEvent;
	wcEvent(const wcEvent &evt) :
		evtType(evt.evtType), uMessageID(evt.uMessageID), funcEvent(evt.funcEvent) {;}
	wcEvent(const wcEventType &EventType, const uint32 &MessageID, EVTPROC EventProc) :
		evtType(EventType), uMessageID(MessageID), funcEvent(EventProc) {;}
	wcEvent(const wcEventType &EventType, const uint32 &MessageID) :
		evtType(EventType), uMessageID(MessageID), funcEvent(NULL) {;}
};

//-----------------------------------------------
//wcEventsTable -- ������� ������� (������ wcEvent).
//-----------------------------------------------

class wcEventsTable: public gcDynList<wcEvent>
{
public:
	~wcEventsTable();

	bool Delete(const uint32 &Index);
	void Clear(void);

	wcEvent * GetHandler(const wcEventType &EventType, const uint32 &MessageID);
	bool FindHandler(const wcEventType &EventType, const uint32 &MessageID, uint32 &Index);
};

#endif //_WCFL_EVENTS_
