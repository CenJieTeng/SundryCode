#include <cstring>
#include "SharedDll.h"

#pragma warning(disable : 4996)

#pragma data_seg("SharedData")
char m_strString[256] = "";
#pragma data_seg()
#pragma comment(linker, "/SECTION:SharedData,RWS")

SHAREDDLL_API void SetValueString(const char *str)
{
    std::strcpy(m_strString, str);
}

SHAREDDLL_API char* GetValueString()
{
    return m_strString;
}