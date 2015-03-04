#include "gcstrfuncs.h"

void strPrintSub(const char *Str, const uint32 &Offset, const uint32 &Length,
				  const bool &bStopOnNull, FILE *fOut)
{
	if (!bStopOnNull) for (uint32 i = 0; i < Length; i++) putc(Str[i + Offset], fOut);
	else for (uint32 i = 0; i < Length; i++) if (Str[i + Offset] == '\0') break; else putc(Str[i + Offset], fOut);
}

bool strSubEquale(const char *Str1, const uint32 &Offset1, const char *Str2, const uint32 &Offset2, const uint32 &Length)
{
	for (uint32 i = 0; i < Length; i++)
		if (Str1[Offset1 + i] != Str2[Offset2 + i]) return false;
	return true;
}

char * strSubstr(char * Substr, const char * Text,
        const uint32 &uPosFrom, const uint32 &uPosLen)
{
    for (uint32 i = 0; i < uPosLen; i++)
        Substr[i] = Text[uPosFrom + i];
    Substr[uPosLen] = '\0';

    return Substr;
}

char chrUpper(char Char)
{
	if (((uint8)Char > 223)||
        (((uint8)Char > 96)&&((uint8)Char < 123)))
			Char -= 32;
	return Char;
}

char * strUpper(char * sText)
{
    uint32 iCount = strLength(sText);
    for (uint32 i = 0; i < iCount; i++)
        sText[i] = chrUpper(sText[i]);
    return sText;
}

char chrLower(char Char)
{
	if ((((uint8)Char > 191)&&(((uint8)Char < 224)))
        ||(((uint8)Char > 64)&&(((uint8)Char < 91))))
			Char += 32;
	return Char;
}

char * strLower(char * sText)
{
    uint32 iCount = strLength(sText);
    for (uint32 i = 0; i < iCount; i++)
		sText[i] = chrLower(sText[i]);
    return sText;
}

bool IsNumericStr(const char *sText)
{
	uint32 iCount = strLength(sText);
    for (uint32 i = 0; i < iCount; i++)
		if ((sText[i] < 48)||(sText[i] > 57)) return false;
    return true;
}

uint32 strLength(const char * String)
{
    if (!String) return 0;
    uint32 uRes = 0;
    while (String[uRes] != '\0') uRes++;
    return uRes;
}

bool IsOnlyLatin(const char * strText)
{
	uint32 uCount = 0;
	uint32 uStrLen = strLength(strText);
	for (uint32 i = 0; i < uStrLen; i++)
    {
        if ((uint8)strText[i] > 127) uCount++;
    }
	if (uCount == 0) return true;
	return false;
}

bool strIsCP1251(const char * strText)
{
    uint32 uStrLen = strLength(strText);
    uint32 uCP1251Count = 0;
    for (uint32 i = 0; i < uStrLen; i++)
    {
        if ((((uint8)strText[i] > 191)&&((uint8)strText[i] < 224))
            ||(((uint8)strText[i] > 240)&&((uint8)strText[i] < 243))
            ||((uint8)strText[i] > 243))
        uCP1251Count++;
    }

    uint32 uCP866Count = 0;
    for (uint32 i = 0; i < uStrLen; i++)
    {
        if ((((uint8)strText[i] > 127)&&((uint8)strText[i] < 168))
            ||(((uint8)strText[i] > 168)&&((uint8)strText[i] < 175)))
        uCP866Count++;
    }

    if (uCP1251Count > uCP866Count) return true;
    return false;
}

char * strCP1251ToCP866(char * strText)
{
    uint32 uLen = strLength(strText);

    for (uint32 i = 0; i < uLen; i++)
    {
        if (((uint8)strText[i] > 191)&&((uint8)strText[i] < 240))
            strText[i] -= 64;
        else
        if ((uint8)strText[i] > 239)
            strText[i] -= 16;
        else
        if ((uint8)strText[i] == 168)
            strText[i] += 72;
        else
        if ((uint8)strText[i] == 186)
            strText[i] += 57;
    }

    return strText;
}

char * strCP866ToCP1251(char * strText)
{
    uint32 uLen = strLength(strText);

    for (uint32 i = 0; i < uLen; i++)
    {
        if (((uint8)strText[i] > 127)&&((uint8)strText[i] < 176))
            strText[i] += 64;
        else
        if (((uint8)strText[i] > 223)&&((uint8)strText[i] < 240))
            strText[i] += 16;
        else
        if ((uint8)strText[i] > 239)
        {
            switch ((uint8)strText[i])
            {
                case 240: //¨
                    strText[i] -= 72;
                break;
                case 241: //¸
                    strText[i] -= 57;
                break;
            }
        }
    }

    return strText;
}

bool strEquale(const char * String1, const char * String2)
{
    uint32 uLen = strLength(String1);
    if (uLen != strLength(String2)) return false;
    else
    {
	for (uint32 i = 0; i < uLen; i++)
	    if (String1[i] != String2[i]) return false;
    }
    return true;
}

bool IsDivider(const char &c)
{
	if (((uint8)c < 48)||(((uint8)c > 57)&&((uint8)c < 64))
		||(((uint8)c > 90)&&((uint8)c < 97))) return true;
	return false;
}

int strpos(const char * strText, const char * strSubText, const uint32 &uPosFrom, const bool &bWholeWord)
{
	int pos = -1;
	uint32 uTextLen = strLength(strText), uSubLen = strLength(strSubText);

	if (uTextLen < uSubLen) return -1;
	if (uPosFrom > (uTextLen - uSubLen - 1)) return -1;

	for (uint32 i = uPosFrom; i < uTextLen; i++)
	{
		if (strText[i] == strSubText[0])
		{
			if (bWholeWord)
			{
				if ((i > 0)&&(!IsDivider(strText[i - 1]))) continue;
				else if ((i + uSubLen < uTextLen)&&(!IsDivider(strText[i + uSubLen]))) continue;
			}
			pos = i;
			for (uint32 j = 1; j < uSubLen; j++)
			{
				if (strText[i + j] != strSubText[j])
				{
					pos = -1;
					break;
				}
			}
			if (pos != -1) break;
		}
	}

	return pos;
}

int strposrev(const char * strText, const char * strSubText, const uint32 &uPosFrom, const bool &bWholeWord)
{
	int pos = -1;
	uint32 uTextLen = strLength(strText), uSubLen = strLength(strSubText);

	if (uTextLen < uSubLen) return -1;
	if (uPosFrom > (uTextLen - uSubLen)) return -1;

	for (uint32 i = uPosFrom + 1; i > 0; i--)
	{
		if (strText[i - 1] == strSubText[0])
		{
			if (bWholeWord)
			{
				if ((i > 1)&&(!IsDivider(strText[i - 2]))) continue;
				else if ((i + uSubLen - 1 < uTextLen)&&(!IsDivider(strText[i - 1 + uSubLen]))) continue;
			}
			pos = i - 1;
			for (uint32 j = 1; j < uSubLen; j++)
			{
				if (strText[i - 1 + j] != strSubText[j])
				{
					pos = -1;
					break;
				}
			}

			if (pos != -1) break;
		}
	}

	return pos;
}

char * strCopy(const char *strToCopy)
{
	uint32 uLen = strLength(strToCopy);
	if (uLen == 0) return NULL;

	char * newStr = new char[uLen + 1];
	for (uint32 i = 0; i < uLen; i++) newStr[i] = strToCopy[i];
	newStr[uLen] = '\0';

	return newStr;
}
