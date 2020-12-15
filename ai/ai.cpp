// ai.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ai.h"


// This is an example of an exported variable
AI_API int nai=0;

// This is an example of an exported function.
AI_API int fnai(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Cai::Cai()
{
    return;
}
