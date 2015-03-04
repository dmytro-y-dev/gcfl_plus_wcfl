#ifndef _GCFL_STRING_
#define _GCFL_STRING_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// Библиотека основных классов и функций
//Версия файла: 20100626
//Автор: Альданис Темнолесный (Aldanis Darkwood)
//-----------------------------------------------

#include "types_common.h"
#include "gcobject.h"

//-----------------------------------------------
// gcString -- Класс строки
//-----------------------------------------------

class gcString: public gcObject
{
protected:
	LPSTR sTextBuf;
	uint32 uLength;
public:
	enum eCodePage {CP1251, CP866, UNKNOWN};

	gcString(LPCSTR String = NULL);
	gcString(LPCSTR String, const uint32 &Length);
	gcString(const gcString &str2copy);
	gcString(const char &c);
	~gcString();

	// Основные функции строк
	uint32 Append(const gcString &str2add); //Возвращает новую длину строки
	uint32 Append(const char &chr2add); //Возвращает новую длину строки

	uint32 Copy(LPCSTR str2copy); //Возвращает сколько было скопировано символов
	void   Copy(LPCSTR str2copy, const uint32 &Length);
	uint32 Copy(const gcString &str2copy); //Возвращает сколько было скопировано символов

	gcString SubString(const uint32 &From, const uint32 &Length) const;
	uint32 Length() const;
	bool IsEmpty() const;
	void Clear();

	// Работа с регистром (кодировка CP1251)
	char UpperChr(const uint32 &Index);
	char LowerChr(const uint32 &Index);
	gcString UpperStr() const;
	gcString LowerStr() const;

	// Операции определения "природы" строки
	bool IsNumericStr() const; //Строка-число (целое!)
	bool IsOnlyLatin() const; //Строка из латинских букв

	// Работа с кодировками
	gcString::eCodePage GetCodePage() const;
	bool ChangeCodePage(const eCodePage &page, const bool &Force = false);

	// Поиск по строке
	int Find(const gcString &ToFind, const uint32 &uPosFrom = 0,
		const bool &bWholeWord = false, const bool &bSearchReverse = false) const;
	uint32 Replace(const gcString &ToFind, const gcString &ToReplace, const uint32 &uPosFrom = 0,
		const bool &bWholeWord = false);

	// Различные функции
	LPCSTR GetCharBuffer() const; //Возвращает константный указатель на текст
	bool IsDivider(const uint32 &Index) const; //Символ является разделителем?
	void Trim();

	// Преобразования
	bool ToInt(int &val);

	gcString operator + (const gcString &str2add) const;
	gcString operator += (const gcString &str2add);
	gcString operator + (const char &chr2add) const;
	gcString operator += (const char &chr2add);
	void operator = (const gcString &str2add);
	bool operator == (const gcString &str2add) const;
	bool operator != (const gcString &str2add) const;
	const char & operator [] (const uint32 &Index) const;
	char & operator [] (const uint32 &Index);
};

//Преобразование обычной строки в gcString
#ifndef _T
#define _T(str) gcString((LPCSTR)str)
#endif

extern const gcString EmptyStr;

#endif //_GCFL_STRING_