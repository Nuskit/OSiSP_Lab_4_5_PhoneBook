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

PHONEBOOKDLL_API UINT PhoneBookEntity::OpenDatabase(LPWSTR bdPathName)
{
	return databaseExport.OpenDatabase(bdPathName);
}

PHONEBOOKDLL_API bool PhoneBookEntity::CloseDatabase(UINT handler)
{
	return databaseExport.CloseDatabase(handler);
}

PHONEBOOKDLL_API bool PhoneBookEntity::AddPhoneBook(UINT handler, const PhoneBookStruct & phoneBook)
{
	return databaseExport.addPhoneBook(handler, phoneBook);
}

PHONEBOOKDLL_API bool PhoneBookEntity::DeletePhoneBook(UINT handler, ULONG index)
{
	return databaseExport.deletePhoneBook(handler, index);
}

PHONEBOOKDLL_API bool PhoneBookEntity::ChangePhoneBook(UINT handler, ULONG index, const PhoneBookStruct & phoneBook)
{
	return databaseExport.changePhoneBook(handler, index, phoneBook);
}

PHONEBOOKDLL_API std::vector<PhoneBookStruct> PhoneBookEntity::GetPhoneBook(UINT handler, ULONG index, ULONG count)
{
	return databaseExport.getPhoneBook(handler, index, count);
}
