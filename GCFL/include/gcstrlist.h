#ifndef _GCFL_STR_LIST_
#define _GCFL_STR_LIST_

//-----------------------------------------------
//GCFL -- Generic Classes and Functions Library
// ���������� �������� ������� � �������
//������ �����: 20100627
//�����: �������� ����������� (Aldanis Darkwood)
//-----------------------------------------------

#include "gcstring.h"
#include "gclist.h"
#include "types_common.h"

#include <assert.h>

//-----------------------------------------------
// gcStrList -- ����c ������ �����
//-----------------------------------------------

class gcStrList: public gcDynList<gcString>
{
public:
	bool LoadFile(const gcString &path);
	bool SaveFile(const gcString &path);
};

#endif //_GCFL_STR_LIST_