#pragma once

#ifdef PHONEBOOKDLL_EXPORTS
#define PHONEBOOKDLL_API __declspec(dllexport) 
#else
#define PHONEBOOKDLL_API __declspec(dllimport) 
#endif