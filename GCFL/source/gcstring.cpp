#include "gcstring.h"
#include "gclist.h"
#include <assert.h>
#include <stdio.h>

const gcString EmptyStr = _T("");

gcString::gcString(const char &c)
{
	this->sTextBuf = new char[2];
	this->sTextBuf[0] = c;
	this->sTextBuf[1] = '\0';
	this->uLength = 1;
}

gcString::gcString(const gcString &str2copy) : gcObject()
{
	this->sTextBuf = NULL;
	this->uLength = 0;
	Copy(str2copy);
}

gcString::gcString(LPCSTR String) : gcObject()
{
	this->sTextBuf = NULL;
	this->uLength = 0;
	Copy((LPCSTR)String);
}

gcString::gcString(LPCSTR String, const uint32 &Length) : gcObject()
{
	this->sTextBuf = NULL;
	this->uLength = 0;
	Copy(String, Length);
}

gcString::~gcString()
{
	if (this->sTextBuf) delete []this->sTextBuf;
}

void gcString::Copy(LPCSTR str2copy, const uint32 &uLenCopy)
{
	if (this->sTextBuf) delete []this->sTextBuf;

	if (uLenCopy > 0)
	{
		this->sTextBuf = new char[uLenCopy + 1];
		for (uint32 i = 0; i < uLenCopy; i++) {
			this->sTextBuf[i] = str2copy[i];
		}
		this->sTextBuf[uLenCopy] = '\0';
	} else this->sTextBuf = NULL;

	this->uLength = uLenCopy;
}

uint32 gcString::Copy(const gcString &str2copy)
{
	return Copy((LPCSTR)str2copy.GetCharBuffer());
}

uint32 gcString::Copy(LPCSTR str2copy)
{
	uint32 uLenCopy = 0;
	if (str2copy) {
		while (str2copy[uLenCopy] != '\0') uLenCopy++;
	}

	Copy(str2copy, uLenCopy);

	return uLenCopy;
}

uint32 gcString::Append(const gcString &str2add)
{
	if (!this->sTextBuf) return Copy(str2add);

	uint32 uLenBase = this->Length();
	uint32 uLenAdd = str2add.Length();
	if (uLenAdd > 0)
	{
		LPSTR newStrBase = new char[uLenBase + uLenAdd + 1];
		for (uint32 i = 0; i < uLenBase; i++) {
			newStrBase[i] = this->sTextBuf[i];
		}
		for (uint32 i = 0; i < uLenAdd; i++) {
			newStrBase[i + uLenBase] = str2add.GetCharBuffer()[i];
		}
		newStrBase[uLenBase + uLenAdd] = '\0';

		delete []this->sTextBuf;
		this->sTextBuf = newStrBase;
	}

	this->uLength = uLenBase + uLenAdd;
	return this->uLength;
}

uint32 gcString::Append(const char &chr2add)
{
	uint32 uLenBase = this->Length();

	LPSTR newStrBase = new char[uLenBase + 2];
	for (uint32 i = 0; i < uLenBase; i++) {
		newStrBase[i] = this->sTextBuf[i];
	}
	newStrBase[uLenBase] = chr2add;
	newStrBase[uLenBase + 1] = '\0';

	delete []this->sTextBuf;
	this->sTextBuf = newStrBase;

	this->uLength = uLenBase + 1;
	return uLenBase + 1;
}

LPCSTR gcString::GetCharBuffer() const
{
	return this->sTextBuf;
}

uint32 gcString::Length() const
{
	// Динамический подсчет длины строки
	/*uint32 uRes = 0;
	if (this->sTextBuf) {
		while (this->sTextBuf[uRes] != '\0') uRes++;
	}*/	 
	
	// Возвращение заранее просчитаного значения
    return uLength;
}

bool gcString::IsEmpty() const
{
	for (uint32 i = 0; i < uLength; i++)
		if (sTextBuf[i] > 0x20) return false;
	return true;
}

void gcString::Clear()
{
	delete []this->sTextBuf;
	this->sTextBuf = NULL;
	this->uLength = 0;
}

gcString gcString::operator + (const gcString &str2add) const
{
	gcString buf(*this);
	buf.Append(str2add);
	return buf;
}

void gcString::operator = (const gcString &str2add)
{
	Copy(str2add);
}

gcString gcString::operator += (const gcString &str2add)
{
	Append(str2add);
	return *this;
}

gcString gcString::operator + (const char &chr2add) const
{
	gcString buf(*this);
	buf.Append(chr2add);
	return buf;
}

gcString gcString::operator += (const char &chr2add)
{
	Append(chr2add);
	return *this;
}

const char & gcString::operator [] (const uint32 &Index) const
{
	assert(Index < this->Length());
	return this->sTextBuf[Index]; 
}

char & gcString::operator [] (const uint32 &Index)
{
	assert(Index < this->Length());
	return this->sTextBuf[Index]; 
}

char gcString::UpperChr(const uint32 &Index)
{
	if (((uint8)this->sTextBuf[Index] > 223)
		||(((uint8)this->sTextBuf[Index] > 96)&&((uint8)this->sTextBuf[Index] < 123)))
			this->sTextBuf[Index] -= 32;
	return this->sTextBuf[Index];
}

char gcString::LowerChr(const uint32 &Index)
{
	if ((((uint8)this->sTextBuf[Index] > 191)&&(((uint8)this->sTextBuf[Index] < 224)))
        ||(((uint8)this->sTextBuf[Index] > 64)&&(((uint8)this->sTextBuf[Index] < 91))))
			this->sTextBuf[Index] += 32;
	return this->sTextBuf[Index];
}

gcString gcString::UpperStr() const
{
	gcString strBuf(*this);
	uint32 iCount = this->Length();
    for (uint32 i = 0; i < iCount; i++) strBuf.UpperChr(i);
    return strBuf;
}

gcString gcString::LowerStr() const
{
	gcString strBuf(*this);
	uint32 iCount = this->Length();
    for (uint32 i = 0; i < iCount; i++) strBuf.LowerChr(i);
    return strBuf;
}

gcString gcString::SubString(const uint32 &From, const uint32 &Length) const
{
	gcString substr;
	uint32 uCount = this->Length();
	if ((uCount > 0)&&(From + Length <= uCount))
	{
		substr.sTextBuf = new char[Length + 1];
		for (uint32 i = 0; i < Length; i++)
		{
			substr.sTextBuf[i] = this->sTextBuf[i + From];
		}
		substr.sTextBuf[Length] = '\0';
		substr.uLength = Length;
	}
	return substr;
}

bool gcString::operator == (const gcString &str2add) const
{
	uint32 uLen = this->Length();
	if (uLen != str2add.Length()) {
		return false;
	}
	else {
		for (uint32 i = 0; i < uLen; i++) {
			if (this->sTextBuf[i] != str2add[i]) return false;
		}
	}
    return true;
}

bool gcString::IsNumericStr() const
{
	uint32 iCount = this->Length();
	for (uint32 i = 0; i < iCount; i++) if ((this->sTextBuf[i] < 48)||(this->sTextBuf[i] > 57)) return false;
    return true;
}

bool gcString::IsOnlyLatin() const
{
	uint32 uStrLen = this->Length();
	for (uint32 i = 0; i < uStrLen; i++) {
        if ((uint8)this->sTextBuf[i] > 127) return false;
    }
	return true;
}

gcString::eCodePage gcString::GetCodePage() const
{
	uint32 uStrLen = this->Length();
    uint32 uCP1251Count = 0;
    for (uint32 i = 0; i < uStrLen; i++)
    {
        if ((((uint8)this->sTextBuf[i] > 191)&&((uint8)this->sTextBuf[i] < 224))
            ||(((uint8)this->sTextBuf[i] > 240)&&((uint8)this->sTextBuf[i] < 243))
            ||((uint8)this->sTextBuf[i] > 243))
        uCP1251Count++;
    }

    uint32 uCP866Count = 0;
    for (uint32 i = 0; i < uStrLen; i++)
    {
        if ((((uint8)this->sTextBuf[i] > 127)&&((uint8)this->sTextBuf[i] < 168))
            ||(((uint8)this->sTextBuf[i] > 168)&&((uint8)this->sTextBuf[i] < 175)))
        uCP866Count++;
    }

	if (uCP1251Count == uCP866Count) return gcString::UNKNOWN;
    if (uCP1251Count > uCP866Count) return gcString::CP1251;
    return gcString::CP866;
}

bool gcString::ChangeCodePage(const eCodePage &page, const bool &Force)
{
	if (!Force)
	{
		gcString::eCodePage eCurPage = this->GetCodePage();
		if (eCurPage == page) return false;
	}
	
	uint32 uLen = this->Length();
	if (page == gcString::CP866)
	{
		for (uint32 i = 0; i < uLen; i++)
		{
			if (((uint8)this->sTextBuf[i] > 191)&&((uint8)this->sTextBuf[i] < 240))
				this->sTextBuf[i] -= 64;
			else
			if ((uint8)this->sTextBuf[i] > 239)
				this->sTextBuf[i] -= 16;
			else
			if ((uint8)this->sTextBuf[i] == 168)
				this->sTextBuf[i] += 72;
			else
			if ((uint8)this->sTextBuf[i] == 186)
				this->sTextBuf[i] += 57;
		}
	}
	else //gcString::CP1251
	{
		for (uint32 i = 0; i < uLen; i++)
		{
			if (((uint8)this->sTextBuf[i] > 127)&&((uint8)this->sTextBuf[i] < 176))
				this->sTextBuf[i] += 64;
			else
			if (((uint8)this->sTextBuf[i] > 223)&&((uint8)this->sTextBuf[i] < 240))
				this->sTextBuf[i] += 16;
			else
			if ((uint8)this->sTextBuf[i] > 239)
			{
				switch ((uint8)this->sTextBuf[i])
				{
					case 240: //Ё
						this->sTextBuf[i] -= 72;
					break;
					case 241: //ё
						this->sTextBuf[i] -= 57;
					break;
				}
			}
		}
	}

	return true;
}

bool gcString::IsDivider(const uint32 &Index) const
{
	if (((uint8)this->sTextBuf[Index] < 48)||
		(((uint8)this->sTextBuf[Index] > 57)&&((uint8)this->sTextBuf[Index] < 64))||
		(((uint8)this->sTextBuf[Index] > 90)&&((uint8)this->sTextBuf[Index] < 97))) return true;
	return false;
}

int gcString::Find(const gcString &ToFind, const uint32 &uPosFrom, const bool &bWholeWord, const bool &bSearchReverse) const
{
	int pos = -1;
	uint32 uTextLen = this->Length(), uSubLen = ToFind.Length();
	if ((uTextLen < uSubLen)||(uPosFrom >= uTextLen)) return -1;

	if (bSearchReverse)
	{
		//Поиск задом-на-перед
		for (uint32 i = uPosFrom + 1; i > 0; i--)
		{
			if (this->sTextBuf[i - 1] == ToFind[0])
			{
				if (bWholeWord)
				{
					if ((i > 1)&&(!this->IsDivider(i - 2))) continue;
					else if ((i + uSubLen - 1 < uTextLen)&&(!this->IsDivider(i - 1 + uSubLen))) continue;
				}
				pos = i - 1;
				for (uint32 j = 1; j < uSubLen; j++)
				{
					if (this->sTextBuf[i - 1 + j] != ToFind[j])
					{
						pos = -1;
						break;
					}
				}

				if (pos != -1) break;
			}
		}
	}
	else
	{
		//Прямой поиск
		for (uint32 i = uPosFrom; i < uTextLen; i++)
		{
			if (this->sTextBuf[i] == ToFind[0])
			{
				if (bWholeWord)
				{
					if ((i > 0)&&(!this->IsDivider(i - 1))) continue;
					else if ((i + uSubLen < uTextLen)&&(!this->IsDivider(i + uSubLen))) continue;
				}
				pos = i;
				for (uint32 j = 1; j < uSubLen; j++)
				{
					if (this->sTextBuf[i + j] != ToFind[j])
					{
						pos = -1;
						break;
					}
				}
				if (pos != -1) break;
			}
		}
	}

	return pos;
}

uint32 gcString::Replace(const gcString &ToFind, const gcString &ToReplace, const uint32 &uPosFrom,
		const bool &bWholeWord)
{
	int pos = uPosFrom;
	gcDynList<uint32> Entries;

	while ((pos = Find(ToFind, pos + 1, bWholeWord, false)) != -1) Entries.Append(new uint32(pos));

	uint32 uResult = Entries.Count();
	if (uResult > 0)
	{
		int iDifference = ToReplace.Length() - ToFind.Length();
		uint32 uNewLen = Length() + uResult * iDifference;

		char *str = new char[uNewLen + 1];
		for (uint32 i = 0, iCur = 0; i < uNewLen;)
		{
			if ((Entries.Count() == 0)||(iCur != *Entries[0]))
			{
				str[i] = sTextBuf[iCur];
				iCur++;	i++;
			}

			else
			{
				Entries.Delete(0);
				for (uint32 j = 0; j < ToReplace.Length(); i++, j++) str[i] = ToReplace[j];
				iCur += ToFind.Length();
			}
		}
		str[uNewLen] = '\0';

		delete [](this->sTextBuf);
		this->sTextBuf = str;

		this->uLength = uNewLen;
	}

	return uResult;
}

bool gcString::operator != (const gcString &str2add) const
{
	return !(this->operator ==(str2add));
}

void gcString::Trim()
{
	uint32 uBegin = 0, uFinish = this->uLength - 1;
	for (; uBegin < this->uLength; uBegin++)
	{
		if (((uint8)this->sTextBuf[uBegin]) > 32) break;
	}

	if (uBegin == this->uLength)
	{
		delete []this->sTextBuf;
		this->sTextBuf = NULL;
		this->uLength  = 0;
		return;
	}

	for (; uFinish > 0; uFinish--)
	{
		if (((uint8)this->sTextBuf[uFinish]) > 32) break;
	}

	uFinish++;
	uint32 uLen = uFinish - uBegin;

	char *buf = new char[uLen + 1];
	for (uint32 i = uBegin; i < uFinish; i++)
	{
		buf[i - uBegin] = this->sTextBuf[i];
	}
	buf[uLen] = '\0';
	this->uLength = uLen;

	delete []this->sTextBuf;
	this->sTextBuf = buf;
}

bool gcString::ToInt(int &val)
{
    if (uLength == 0) return false;

    char *newstr = new char[uLength + 1];
    const char *buf = sTextBuf;
    int i = 0;

    while (*buf)
    {
        if (i == 0 && *buf == '0')
        {
            //nothing to do
        }
        else if (((uint8)*buf >= (uint8)'0' && (uint8)*buf <= (uint8)'9') ||
                 (*buf == '-'))
        {
            newstr[i] = *buf;
            ++i;
        }
        else
        {
            delete []newstr;
            return false;
        }

        ++buf;
    }

    if (i == 0)
    {
        newstr[0] = '0';
        ++i;
    }

    newstr[i] = '\0';

	if (!sscanf(newstr, "%i", &val))
    {
        delete []newstr;
        return false;
    }
    else
    {
        delete []newstr;
	    return true;
    }
}