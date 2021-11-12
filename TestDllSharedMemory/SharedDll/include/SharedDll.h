#ifndef SHARED_DLL_H
#define SHARED_DLL_H

#ifdef SHAREDDLL_EXPORTS
#define SHAREDDLL_API __declspec(dllexport)
#else
#define SHAREDDLL_API __declspec(dllimport)
#endif // SHAREDDLL_EXPORTS

extern "C"
{
	SHAREDDLL_API void SetValueString(const char *str);

	SHAREDDLL_API char* GetValueString();
}

#endif // !SHARED_DLL_H
