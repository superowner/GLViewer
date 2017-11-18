// 3DBase.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "3DBase.h"


// This is an example of an exported variable
MY3DBASE_API int nMy3DBase=0;

// This is an example of an exported function.
MY3DBASE_API int fnMy3DBase(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see 3DBase.h for the class definition
CMy3DBase::CMy3DBase()
{
    return;
}
