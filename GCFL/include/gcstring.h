#ifndef _GCFL_STRING_
#define _GCFL_STRING_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// ���������� �������� ������� � �������
//������ �����: 20100626
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "types_common.h"
#include "gcobject.h"

//-----------------------------------------------
// gcString -- ����� ������
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

	// �������� ������� �����
	uint32 Append(const gcString &str2add); //���������� ����� ����� ������
	uint32 Append(const char &chr2add); //���������� ����� ����� ������

	uint32 Copy(LPCSTR str2copy); //���������� ������� ���� ����������� ��������
	void   Copy(LPCSTR str2copy, const uint32 &Length);
	uint32 Copy(const gcString &str2copy); //���������� ������� ���� ����������� ��������

	gcString SubString(const uint32 &From, const uint32 &Length) const;
	uint32 Length() const;
	bool IsEmpty() const;
	void Clear();

	// ������ � ��������� (��������� CP1251)
	char UpperChr(const uint32 &Index);
	char LowerChr(const uint32 &Index);
	gcString UpperStr() const;
	gcString LowerStr() const;

	// �������� ����������� "�������" ������
	bool IsNumericStr() const; //������-����� (�����!)
	bool IsOnlyLatin() const; //������ �� ��������� ����

	// ������ � �����������
	gcString::eCodePage GetCodePage() const;
	bool ChangeCodePage(const eCodePage &page, const bool &Force = false);

	// ����� �� ������
	int Find(const gcString &ToFind, const uint32 &uPosFrom = 0,
		const bool &bWholeWord = false, const bool &bSearchReverse = false) const;
	uint32 Replace(const gcString &ToFind, const gcString &ToReplace, const uint32 &uPosFrom = 0,
		const bool &bWholeWord = false);

	// ��������� �������
	LPCSTR GetCharBuffer() const; //���������� ����������� ��������� �� �����
	bool IsDivider(const uint32 &Index) const; //������ �������� ������������?
	void Trim();

	// ��������������
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

//�������������� ������� ������ � gcString
#ifndef _T
#define _T(str) gcString((LPCSTR)str)
#endif

extern const gcString EmptyStr;

#endif //_GCFL_STRING_