#ifndef _GCFL_STR_FUNCS_
#define _GCFL_STR_FUNCS_

#include "types_common.h"
#include <stdio.h>

//������ ��������� (bStopOnNull - ��������������-�� ��� ���������� ������� \0)
void strPrintSub(const char *Str, const uint32 &Offset, const uint32 &Length,
				 const bool &bStopOnNull = true, FILE *fOut = stdout);

//�������� � ��������� (� ��������� CP1251)
char chrUpper(char Char);
char chrLower(char Char);
char * strUpper(char * sText);
char * strLower(char * sText);

//��������� ��������� �� ������
char * strSubstr(char * Substr, const char * Text, const uint32 &uPosFrom, const uint32 &uPosLen);

//��������� ����� �� ���������������
bool strEquale(const char * String1, const char * String2);
bool strSubEquale(const char *Str1, const uint32 &Offset1, const char *Str2,
				  const uint32 &Offset2, const uint32 &Length);

//����� ������
uint32 strLength(const char * String);

//����� ������/�����
int strpos(const char * strText, const char * strSubText, const uint32 &uPosFrom, const bool &bWholeWord);
int strposrev(const char * strText, const char * strSubText, const uint32 &uPosFrom, const bool &bWholeWord);

//�������� �� �������
bool IsNumericStr(const char *sText);
bool IsOnlyLatin(const char * strText);
bool IsDivider(const char &c); //�������� �� ������ ������������?

//�������� ������ ������� � ��������� CP1251 (���� true) ��� �� CP866
bool strIsCP1251(const char * strText);

//�������������� ���������
char * strCP1251ToCP866(char * strText);
char * strCP866ToCP1251(char * strText);

//����������� ������
char * strCopy(const char *strToCopy);

#endif //_GCFL_STR_FUNCS_
