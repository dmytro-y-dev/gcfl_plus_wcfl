#ifndef _GCFL_DYN_LIST_
#define _GCFL_DYN_LIST_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// Библиотека основных классов и функций
//Версия файла: 20100627
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "gcobject.h"
#include "types_common.h"

#include <assert.h>

//-----------------------------------------------
// gcDynItem -- Класc элемента динамического списка
//-----------------------------------------------

template <typename objClass>
class gcDynList;

template <typename objClass>
class gcDynItem: public gcObject
{
friend gcDynList<objClass>;
public:
	objClass *Content;
protected:
	gcDynItem<objClass> *Next;
	gcDynItem<objClass> *Prev;
	bool AutoRemove;
public:
	gcDynItem(gcDynItem<objClass> *itmPrev, const bool &bAutoRemove) : gcObject()
	{
		this->Prev = itmPrev;
		if (itmPrev)
		{
			this->Next = this->Prev->Next;
			this->Prev->Next = this;
		}
		else this->Next = NULL;

		this->Content = NULL;
		this->AutoRemove = bAutoRemove;
	}

	~gcDynItem(void)
	{
		if (this->Prev) this->Prev->Next = this->Next;
		if (this->Next) this->Next->Prev = this->Prev;
		if ((this->AutoRemove)&&(this->Content)) delete (objClass *)this->Content;
	}

//------------------------------------------------------------

	gcDynItem<objClass> * GetNext(void)
	{
		return this->Next;
	}

	gcDynItem<objClass> * GetPrev(void)
	{
		return this->Prev;
	}

	uint32 GetIndex(void)
	{
		uint32 uIndex = 0;
		gcDynItem * bufItem = this->Prev;
		while (bufItem) bufItem = bufItem->Prev;
		return uIndex;
	}

//------------------------------------------------------------

	void SwapWithNext(void)
	{
		if (!this->Next) return;

		this->Next->Prev = this->Prev;
		if (this->Prev) this->Prev->Next = this->Next;

		this->Prev = this->Next;
		this->Next = this->Prev->Next;

		this->Prev->Next = this;
		if (this->Next) this->Next->Prev = this;
	}

	void SwapWithPrev(void)
	{
		if (!this->Prev) return;

		this->Prev->Next = this->Next;
		if (this->Next) this->Next->Prev = this->Prev;

		this->Next = this->Prev;
		this->Prev = this->Prev->Prev;
		if (this->Prev) this->Prev->Next = this;

		this->Next->Prev = this;
	}

	gcDynItem<objClass> *InsertPrev(const bool &bAutoRemove)  //Не используйте эту функцию! Она используется внутренними функциями GCFL!
	{
		this->Prev = new gcDynItem<objClass>(this->Prev, bAutoRemove);
		this->Prev->Next = this;
		return this->Prev;
	}

	bool IsToRemove() { return AutoRemove; }
};

//-----------------------------------------------
// gcDynList -- Основной класc списков. Используется для
// хранения элементов в виде связаного списка.
//-----------------------------------------------

template <typename objClass>
class gcDynList: public gcObject
{
protected:
    uint32 uItemsCount;
    uint32 uItemsIndex;
    gcDynItem<objClass> *Items;
public:
	gcDynList(void) : gcObject()
	{
		this->Items = NULL;
		this->uItemsCount = 0;
		this->uItemsIndex = 0;
	}

    ~gcDynList(void)
	{
		Clear();
	}

//------------------------------------------------------------

    objClass * Get(const uint32 &Index)
	{
		if (!GotoItm(Index)) return NULL;
		return this->Items->Content;
	}

	uint32 GetCurIndex(void)
	{
		return this->uItemsIndex;
	}

    uint32 Count(void)
	{
		return this->uItemsCount;
	}

//------------------------------------------------------------

    uint32 Append(objClass *Data, const bool &bAutoRemove = true)
	{
		GotoItmLast();

		gcDynItem<objClass> *itmNew = new gcDynItem<objClass>(this->Items, bAutoRemove);
		itmNew->Content = Data;

		this->Items = itmNew;
		this->uItemsIndex = this->uItemsCount;
		this->uItemsCount++;

		return this->uItemsIndex;
	}

    bool Insert(const uint32 &Index, objClass *Data, const bool &bAutoRemove = true)
	{
		if (Index == this->uItemsCount) Append(Data, bAutoRemove);
		else
		{
			if (!GotoItm(Index)) return false;
			this->Items = this->Items->InsertPrev(bAutoRemove);
			this->Items->Content = Data;
			this->uItemsCount++;
		}
		return true;
	}

    bool Delete(const uint32 &Index)
	{
		if (!GotoItm(Index)) return false;

		if (this->Items->GetNext())
		{
			this->Items = this->Items->GetNext();
			delete this->Items->GetPrev();
		}
		else
		if (this->Items->GetPrev())
		{
			this->Items = this->Items->GetPrev();
			delete this->Items->GetNext();
			this->uItemsIndex--;
		}
		else
		{
			delete this->Items;
			this->Items = NULL;
			this->uItemsIndex = 0;
		}

		this->uItemsCount--;

		return true;
	}

	bool Replace(const uint32 &Index, objClass *Data, const bool &bAutoRemove = true)
	{
		if (!GotoItm(Index)) return false;

		if (Items->IsToRemove() && Items->Content) delete (objClass *)Items->Content;
		Items->Content = Data;
		Items->AutoRemove = bAutoRemove;

		return true;
	}

    void Clear(void)
	{
		if (this->Items)
		{
			while (this->Items->GetPrev()) this->Items = this->Items->GetPrev();
			while (this->Items->GetNext())
			{
				this->Items = this->Items->GetNext();
				delete this->Items->GetPrev();
			}
			delete this->Items;

			this->Items = NULL;
			this->uItemsCount = 0;
			this->uItemsIndex = 0;		
		}
	}

//------------------------------------------------------------

    bool MoveItmUp(const uint32 &Index, const uint32 &uStepsNumb)
	{
		if (this->uItemsCount < (Index + uStepsNumb + 1)) return false;
		if (!GotoItm(Index)) return false;

		this->uItemsIndex += uStepsNumb;
		for (uint32 i = 0; i < uStepsNumb; i++) this->Items->SwapWithNext();

		return true;
	}

    bool MoveItmDown(const uint32 &Index, const uint32 &uStepsNumb)
	{
		if (((int)(Index - uStepsNumb)) < 0) return false;
		if (!GotoItm(Index)) return false;

		this->uItemsIndex -= uStepsNumb;
		for (uint32 i = 0; i < uStepsNumb; i++) this->Items->SwapWithPrev();

		return true;
	}

//------------------------------------------------------------

    bool GotoItm(const uint32 &Index)
	{
		if (this->Items == NULL) return false;
		if (Index >= this->uItemsCount) return false;
		if (Index == this->uItemsIndex) return true;
		if (Index < this->uItemsIndex)
		{
			for (uint32 i = this->uItemsIndex; i > Index ; i--)
				this->Items = this->Items->GetPrev();
		}
		else
		{
			for (uint32 i = this->uItemsIndex; i < Index; i++)
				this->Items = this->Items->GetNext();
		}
		this->uItemsIndex = Index;

		return true;
	}

    void GotoItmFirst(void)
	{
		GotoItm(0);
	}

    void GotoItmLast(void)
	{
		if (this->uItemsCount > 0) GotoItm(this->uItemsCount - 1);
	}

//------------------------------------------------------------

	objClass * operator [] (const uint32 &Index)
	{
		assert(Index < this->Count());
		GotoItm(Index);
		return (objClass *)this->Items->Content;
	}

	uint32 operator += (objClass *Data)
	{
		return this->Append(Data);
	}
};

#endif //_GCFL_DYN_LIST_
