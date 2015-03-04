#include "gcconfig.h"
#include "gcstrlist.h"
#include <stdio.h>

bool gcConfig::LoadFile(const gcString &path)
{
    gcStrList lstStrings;
    if (!lstStrings.LoadFile(path)) return false;

	uint32 uCount = lstStrings.Count();
    for (uint32 i = 0; i < uCount; i++)
    {
		uint32 uCount = lstStrings[i]->Length();
		int iDivider = lstStrings[i]->Find(_T("="));
		if (iDivider != -1)
		{
			gcConfigItem *cfgItem = new gcConfigItem();
			cfgItem->Name = lstStrings[i]->SubString(0, iDivider);
			cfgItem->Value = lstStrings[i]->SubString(iDivider + 1, uCount - iDivider - 1);
			cfgItem->CleanName();
			cfgItem->CleanValue();
			Append(cfgItem);
		}
    }

    return true;
}

bool gcConfig::SaveFile(const gcString &path)
{
	FILE *fOut = fopen(path.GetCharBuffer(), "wt");
    if (!fOut) return false;

    uint32 uCount = this->Count(), uLen;
    for (uint32 i = 0; i < uCount; i++)
    {
        GotoItm(i);
		uLen = this->Items->Content->Name.Length();

		fwrite(this->Items->Content->Name.GetCharBuffer(), sizeof(char), uLen, fOut);
        putc('=', fOut);

        uLen = this->Items->Content->Value.Length();
        fwrite(this->Items->Content->Value.GetCharBuffer(), sizeof(char), uLen, fOut);
        putc('\n', fOut);
    }
    fclose(fOut);
    return true;
}

gcString* gcConfig::FindValue(const gcString &Name)
{
	for (uint32 i = 0; i < Count(); i++)
	{
		if (Get(i)->Name == Name)
			return &(Get(i)->Value);
	}
	return NULL;
}

