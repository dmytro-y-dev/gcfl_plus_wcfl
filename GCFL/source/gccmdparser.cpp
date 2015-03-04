#include "gccmdparser.h"
#include <stdio.h>
#include <process.h>

gcCmdParser::gcCmdParser() : gcObject()
{
	//
}

gcCmdParser::~gcCmdParser()
{
	//
}

void gcCmdParser::ParseCmdLine(const gcString &sCmdLine, const uint16 &uParseFrom)
{
	uint16 uCmdLen = sCmdLine.Length();
	uint16 uCommandLen = uCmdLen - uParseFrom;
	for (uint16 i = uParseFrom; i < uCmdLen; i++)
	{
		if ((sCmdLine[i] == ' ')||(sCmdLine[i] == '\t'))
		{
			uCommandLen = i - uParseFrom;
			break;
		}
	}

	sCommand = sCmdLine.SubString(uParseFrom, uCommandLen);
	sCommand = sCommand.LowerStr();
	//printf("%s %s %i [cmd] %i [len] %i [shift]\n", sCommand.GetCharBuffer(), sCmdLine.GetCharBuffer(),
	//	uCommandLen, uCmdLen, uParseFrom);

	int iCurSymb = uParseFrom + uCommandLen + 1;
	while (iCurSymb != -1)
	{
		gcCmdParam *param = new gcCmdParam();
		iCurSymb = ParseValue(param, iCurSymb, sCmdLine, uCmdLen);
		if (iCurSymb != -1) this->Params.Append(param);
	}
}

bool gcCmdParser::IsParamExists(const gcString &sParamName)
{
	for (uint8 i = 0; i < Params.Count(); i++)
		if (Params[i]->Name == sParamName) return true;
	return false;
}

gcString gcCmdParser::GetParam(const uint16 &uParamID)
{
	assert(uParamID < Params.Count());
	return Params[uParamID]->Name; 
}

gcString gcCmdParser::GetValue(const uint16 &uParamID)
{
	assert(uParamID < Params.Count());
	return Params[uParamID]->Value; 
}

gcString gcCmdParser::GetValue(const gcString &sParamName)
{
	for (uint8 i = 0; i < Params.Count(); i++)
		if (Params[i]->Name == sParamName) return Params[i]->Value;

	printf("Parse error: No parameter with name %s!", sParamName.GetCharBuffer());
	exit(-1);
}

int gcCmdParser::ParseValue(gcCmdParam *Param, const uint16 &iCurSymb, const gcString &sCmdLine, const uint16 &uCmdLen)
{
	if (iCurSymb >= uCmdLen) return -1;

	bool bRead = false;
	for (uint16 i = iCurSymb; i < uCmdLen; i++)
	{
		if (sCmdLine[i] == '=') {
			bRead = true; break;
		}
		else Param->Name += sCmdLine[i];
	}
	if (!bRead) return -1;

	Param->Name = Param->Name.LowerStr();
	//Прочитали параметр - теперь читаем значение

	bool bNoCheck = false; uint8 uChecksCount = 0;
	for (uint16 i = iCurSymb + Param->Name.Length() + 1; i < uCmdLen; i++)
	{
		if ((!bNoCheck)&&(sCmdLine[i] == ' ')) {
			break;
		}
		else
		if ((sCmdLine[i] == '"')||(sCmdLine[i] == '\''))
		{
			bNoCheck = !bNoCheck;
			uChecksCount++;
		}
		else Param->Value += sCmdLine[i];
	}

	return (iCurSymb + Param->Value.Length() + Param->Name.Length() + uChecksCount + 2);
}