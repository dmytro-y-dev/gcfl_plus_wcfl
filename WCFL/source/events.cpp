#include "events.h"

wcEventsTable::~wcEventsTable()
{
	Clear();
}

bool wcEventsTable::Delete(const uint32 &Index)
{
	if (!GotoItm(Index)) return false;
	return gcDynList::Delete(Index);
}

void wcEventsTable::Clear(void)
{
	for (; Count() != 0; )
	{
		GotoItm(0);
		gcDynList::Delete(0);
	}
}

wcEvent *wcEventsTable::GetHandler(const wcEventType &EventType, const uint32 &MessageID)
{
	uint32 uIndex;
	if (!FindHandler(EventType, MessageID, uIndex)) return NULL;

	wcEvent *evt = this->Get(uIndex);
	return evt;
}

bool wcEventsTable::FindHandler(const wcEventType &EventType, const uint32 &MessageID, uint32 &Index)
{
	for (uint32 i = 0; i < this->Count(); i++)
	{
		wcEvent *evt = this->Get(i);
		if ((evt->evtType == EventType)&&
			(evt->uMessageID == MessageID))
		{
			Index = i;
			return true;
		}
	}
	return false;
}