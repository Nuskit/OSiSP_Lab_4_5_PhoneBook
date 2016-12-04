#pragma once
#include "stdafx.h"

#ifdef PHONEBOOKDLL_EXPORTS
#define PHONEBOOKDLL_API __declspec(dllexport) 
#else
#define PHONEBOOKDLL_API __declspec(dllimport) 
#endif

struct PhoneBookStruct;
namespace PhoneBookEntity
{
	PHONEBOOKDLL_API UINT OpenDatabase(LPWSTR bdPathName);
	PHONEBOOKDLL_API bool CloseDatabase(UINT handler);

	PHONEBOOKDLL_API bool AddPhoneBook(UINT handler, const PhoneBookStruct& phoneBook);
	PHONEBOOKDLL_API bool DeletePhoneBook(UINT handler, ULONG index);
	PHONEBOOKDLL_API bool ChangePhoneBook(UINT handler, ULONG index, const PhoneBookStruct& phoneBook);
	PHONEBOOKDLL_API std::vector<PhoneBookStruct> GetPhoneBook(UINT handler, ULONG index, ULONG count = 1);
};
