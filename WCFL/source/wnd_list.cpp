#include "wnd_list.h"
#include "window.h"

wcWindow * wcWindowsList::GetChild(const HWND hWnd, const bool &bSearchChildren)
{
	uint32 uIndex = 0;
	if (!FindChild(hWnd, uIndex))
	{
		if (!bSearchChildren) return NULL;

		wcWindow *bufWnd = NULL;
		for (uint32 i = 0; i < this->uItemsCount; i++)
		{
			bufWnd = this->Get(i);
			if ((bufWnd)&&(bufWnd = bufWnd->Children.GetChild(hWnd, true))&&(bufWnd)) return bufWnd;
		}

		return NULL;
	}

	wcWindow *wnd = this->Get(uIndex);
	return wnd;
}

bool wcWindowsList::FindChild(const HWND hWnd, uint32 &Index)
{
	for (uint32 i = 0; i < this->Count(); i++)
	{
		wcWindow *wnd = this->Get(i);
		if (wnd->GetWndHandle() == hWnd)
		{
			Index = i;
			return true;
		}
	}
	return false;
}