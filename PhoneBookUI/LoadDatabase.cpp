#include "stdafx.h"
#include "LoadDatabase.h"

OPENDATABASEROUTINE openDatabaseRoutine;
CLOSEDATABASEROUTINE closeDatabaseRoutine;

ADDPHONEBOOKROUTINE addPhoneBookRoutine;
DELETEPHONEBOOKROUTINE deletePhoneBookRoutine;
CHANGEPHONEBOOK changePhoneBook;
GETPHONEBOOKROUTINE getPhoneBook;
FINDPHONEBOOKROUTINE findPhoneBook;

extern HINSTANCE        hInst;
extern HWND             g_hMainWindow;
HMODULE                 g_hDatabaseLibrary;
const char              *g_DatabasePtr = nullptr;
int                     g_cRecordsInBase = 0;
HMODULE hModule;

BOOL LoadDatabaseDLL(void)
{
	hModule = LoadLibrary(TEXT("PhoneBookDLL.dll"));
	DWORD error = 0;

	if (hModule == nullptr) {
		error = GetLastError();
	}
	else {
		openDatabaseRoutine = OPENDATABASEROUTINE(GetProcAddress(hModule, "OpenDatabase"));
		closeDatabaseRoutine = CLOSEDATABASEROUTINE(GetProcAddress(hModule, "CloseDatabase"));
		
		addPhoneBookRoutine = ADDPHONEBOOKROUTINE(GetProcAddress(hModule, "AddPhoneBook"));
		deletePhoneBookRoutine = DELETEPHONEBOOKROUTINE(GetProcAddress(hModule, "DeletePhoneBook"));
		changePhoneBook = CHANGEPHONEBOOK(GetProcAddress(hModule, "ChangePhoneBook"));
		getPhoneBook = GETPHONEBOOKROUTINE(GetProcAddress(hModule, "GetPhoneBook"));
		findPhoneBook = FINDPHONEBOOKROUTINE(GetProcAddress(hModule, "FindPhoneBook"));
		if (!(openDatabaseRoutine && closeDatabaseRoutine && addPhoneBookRoutine 
			&& deletePhoneBookRoutine && changePhoneBook && getPhoneBook && findPhoneBook)) {
			error = GetLastError();
		}
	}

	if (error) {
		DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
		HLOCAL hlocal = nullptr;

		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr, GetLastError(), systemLocale,
			PTSTR(&hlocal), 0, nullptr);

		MessageBox(nullptr, PTCHAR(hlocal), nullptr, MB_OK);
		LocalFree(hlocal);
		CloseDatabaseDLL();
		return FALSE;
	}

	return TRUE;
}

BOOL CloseDatabaseDLL()
{
	return FreeLibrary(hModule);
}

BOOL GetFilename(TCHAR *szFile)
{
    OPENFILENAME ofn;

    memset(&ofn, 0, sizeof ofn);
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hInstance = hInst;
    ofn.hwndOwner = g_hMainWindow;
    ofn.lpstrFilter = nullptr;
    ofn.lpstrCustomFilter = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH * sizeof *szFile;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrTitle = nullptr;

    return GetOpenFileName(&ofn);
}
