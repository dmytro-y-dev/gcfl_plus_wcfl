#include "gcstrlist.h"
#include <stdio.h>

bool gcStrList::LoadFile(const gcString &path)
{
	FILE *fIn = fopen(path.GetCharBuffer(), "rt");
    if (!fIn) return false;

    Clear();
    while (!feof(fIn))
    {
		uint16 uStrLen = 0;
		char *strBuf = new char[65556]; char c = '\0';
		while((!feof(fIn))&&(c != '\n'))
		{
			fread(&c, sizeof(char), 1, fIn);
			strBuf[uStrLen] = c; uStrLen++;
		}
		strBuf[uStrLen - 1] = '\0';

		Append(new gcString(_T(strBuf)));
		delete []strBuf;
    }
    fclose(fIn);

    return true;
}

bool gcStrList::SaveFile(const gcString &path)
{
	FILE * fOut = fopen(path.GetCharBuffer(), "wt");
    if (!fOut) return false;

    for (uint16 i = 0; i < this->uItemsCount; i++)
    {
		GotoItm(i);
		uint16 uStrLen = 0; const char nl = '\n';
		if (this->Items->Content)
		{
			uStrLen = this->Items->Content->Length();
			fwrite(this->Items->Content->GetCharBuffer(), sizeof(char), uStrLen, fOut);
		}
		if (i != (this->uItemsCount - 1)) fwrite(&nl, sizeof(char), 1, fOut);
    }
    fclose(fOut);

    return true;
}
