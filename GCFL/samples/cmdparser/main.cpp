#include <stdio.h>
#include <process.h>

#include "string.h"
#include "list.h"
#include "strlist.h"
#include "config.h"

#include "cmdparser.h"

void strTest(gcCmdParser &parser)
{
	gcString strText = _T("ПрятВеть!");
	printf("%s\n", strText.GetCharBuffer());
	printf("%i\n", strText.Find(_T("т"), 0, false, false));
}

void strListTest(gcCmdParser &parser)
{
	gcStrList Strings;
	if (!Strings.LoadFile("Debug\\text.txt")) printf("unable to open file...\n");
	for (uint32 i = 0; i < Strings.Count(); i++) printf("%s %i\n", Strings[i].GetCharBuffer(), Strings[i].Length());
	Strings += "--END OF PROTOCOL--";
	Strings.SaveFile("Debug\\text.txt");
}

void configTest(gcCmdParser &parser)
{
	gcConfig cfg;
	if (!cfg.LoadFile(parser.GetValue(_T("path")))) printf("unable to open file...\n");
	for (uint32 i = 0; i < cfg.Count(); i++)
	{
		cfg[i].CleanName();
		cfg[i].CleanValue();
		printf("Param: %s\nValue: %s\n", 
			cfg[i].Name.GetCharBuffer(), cfg[i].Value.GetCharBuffer());
	}
	cfg.SaveFile(parser.GetValue(_T("path")));
}

DEFINE_DEFAULT_EVENT(strTest)
BEGIN_EVENTS_TABLE()
	DEFINE_EVENT(configTest, "cfg")
	DEFINE_EVENT(strListTest, "str")
END_EVENTS_TABLE()

INIT_DEFAULT_PARSER()