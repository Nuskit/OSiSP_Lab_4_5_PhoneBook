#include "stdafx.h"
#include "DatabaseExport.h"
#include "dllMain.h"
#include "PhoneBookStruct.h"

static DatabaseExport databaseExport;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

PHONEBOOKDLL_API UINT OpenDatabase(LPWSTR bdPathName)
{
	return databaseExport.OpenDatabase(bdPathName);
}

PHONEBOOKDLL_API bool CloseDatabase(UINT handler)
{
	return databaseExport.CloseDatabase(handler);
}

PHONEBOOKDLL_API bool AddPhoneBook(UINT handler, const PhoneBookStruct & phoneBook)
{
	return databaseExport.addPhoneBook(handler, phoneBook);
}

PHONEBOOKDLL_API bool DeletePhoneBook(UINT handler, ULONG index)
{
	return databaseExport.deletePhoneBook(handler, index);
}

PHONEBOOKDLL_API bool ChangePhoneBook(UINT handler, ULONG index, const PhoneBookStruct & phoneBook)
{
	return databaseExport.changePhoneBook(handler, index, phoneBook);
}

PHONEBOOKDLL_API ListPhoneBookStruct* GetPhoneBook(UINT handler, ULONG index, ULONG count)
{
	auto listPhoneBook = databaseExport.getPhoneBook(handler, index, count);
	return new ListPhoneBookStruct(listPhoneBook.data(), listPhoneBook.size());
}

PHONEBOOKDLL_API ListPhoneBookStruct* FindPhoneBook(UINT handler, const PhoneBookStruct& phoneBook)
{
	auto listPhoneBook = databaseExport.findPhoneBook(handler, phoneBook);
	return new ListPhoneBookStruct(listPhoneBook.data(), listPhoneBook.size());
}
