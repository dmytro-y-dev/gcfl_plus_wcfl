#include "gcobject.h"

#ifdef GCFL_DEBUG
	#include <stdio.h>
	int iObjCount = 0;
#endif

gcObject::gcObject()
{
	#ifdef GCFL_DEBUG
		static int iNewCount = 0;
		iNewCount++; iObjCount++;
		printf("gcObject [%i] created (op #%i)\n", iObjCount, iNewCount);
	#endif
}

gcObject::~gcObject()
{
	#ifdef GCFL_DEBUG
		static int iDelCount = 0;
		iDelCount++; iObjCount--;
		printf("gcObject [%i] deleted (op #%i)\n", iObjCount, iDelCount);
	#endif
}
