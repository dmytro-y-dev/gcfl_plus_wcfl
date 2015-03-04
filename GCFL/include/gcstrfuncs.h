#ifndef _GCFL_STR_FUNCS_
#define _GCFL_STR_FUNCS_

#include "types_common.h"
#include <stdio.h>

//Печать подстроки (bStopOnNull - останавливатся-ли при достижение символа \0)
void strPrintSub(const char *Str, const uint32 &Offset, const uint32 &Length,
				 const bool &bStopOnNull = true, FILE *fOut = stdout);

//Операции с регистром (в кодировке CP1251)
char chrUpper(char Char);
char chrLower(char Char);
char * strUpper(char * sText);
char * strLower(char * sText);

//Выделение подстроки со строки
char * strSubstr(char * Substr, const char * Text, const uint32 &uPosFrom, const uint32 &uPosLen);

//Сравнение строк на эквивалентность
bool strEquale(const char * String1, const char * String2);
bool strSubEquale(const char *Str1, const uint32 &Offset1, const char *Str2,
				  const uint32 &Offset2, const uint32 &Length);

//Длина строки
uint32 strLength(const char * String);

//Поиск вперед/назад
int strpos(const char * strText, const char * strSubText, const uint32 &uPosFrom, const bool &bWholeWord);
int strposrev(const char * strText, const char * strSubText, const uint32 &uPosFrom, const bool &bWholeWord);

//Проверка на символы
bool IsNumericStr(const char *sText);
bool IsOnlyLatin(const char * strText);
bool IsDivider(const char &c); //Является ли символ разделителем?

//Является строка строкой в кодировке CP1251 (если true) или же CP866
bool strIsCP1251(const char * strText);

//Преобразования кодировок
char * strCP1251ToCP866(char * strText);
char * strCP866ToCP1251(char * strText);

//Копирование строки
char * strCopy(const char *strToCopy);

#endif //_GCFL_STR_FUNCS_
