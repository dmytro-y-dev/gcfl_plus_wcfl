#ifndef _GCFL_CONFIG_
#define _GCFL_CONFIG_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// ���������� �������� ������� � �������
//������ �����: 20100627
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "gcstring.h"
#include "gclist.h"
#include "types_common.h"

//-----------------------------------------------
// gcConfigItem -- ����c �������� ������������
//-----------------------------------------------

class gcConfigItem: public gcObject
{
public:
    gcString Name;
    gcString Value;
public:
	gcConfigItem(const gcString &sName, const gcString &sValue) : gcObject()
    {
        Name = sName;
        Value = sValue;
    }

	gcConfigItem() : gcObject() {;}

	//������� ��� �������, ���� � �.�. �� ����� ���������
	void CleanName() {
		CleanStr(this->Name);
	}

	//... �� �������� ���������
	void CleanValue() {
		CleanStr(this->Value);
	}
protected:
	void CleanStr(gcString &str)
	{
		uint32 uCount = str.Length();
		uint32 uFromBeg = 0, uFromEnd = uCount - 1;
		for (uint32 i = 0; i < uCount; i++)
		{
			if ((str[i] != ' ')&&
				(str[i] != '\t')&&
				(str[i] != '\n'))
			{
				uFromBeg = i;
				break;
			}
		}

		for (uint32 i = uCount; i > uFromBeg; i--)
		{
			if ((str[i - 1] != ' ')&&
				(str[i - 1] != '\t')&&
				(str[i - 1] != '\n'))
			{
				uFromEnd = i;
				break;
			}
		}

		str = str.SubString(uFromBeg, uFromEnd - uFromBeg);
	}
};

//-----------------------------------------------
// gcConfig -- ����c ������������
//----------------------------------------------

class gcConfig : public gcDynList<gcConfigItem>
{
public:
    bool LoadFile(const gcString &Filename);
    bool SaveFile(const gcString &Filename);

	gcString* FindValue(const gcString &Name);
};

#endif //_GCFL_CONFIG_
