#include "stdafx.h"
#include "ButtonHandlers.h"
#include "LoadDatabase.h"
#include <Windowsx.h>
#include "PhoneBookStruct.h"
#include "ListViewFunctions.h"

extern HWND             g_hListView, g_hMainWindow;
extern int              g_cRecordsInBase;
extern HWND             g_hInputBox[8];
extern HWND							g_hPageUpDownBuddy;

extern OPENDATABASEROUTINE openDatabaseRoutine;
extern CLOSEDATABASEROUTINE closeDatabaseRoutine;

extern ADDPHONEBOOKROUTINE addPhoneBookRoutine;
extern DELETEPHONEBOOKROUTINE deletePhoneBookRoutine;
extern CHANGEPHONEBOOK changePhoneBook;
extern GETPHONEBOOKROUTINE getPhoneBook;

UINT handler = -1;

void Display(const ListPhoneBookStruct& recTemplate);

void LoadDB(void)
{
	TCHAR szFile[MAX_PATH] = TEXT("\0");

	if (GetFilename(szFile)) {
		if (handler != -1) {
			closeDatabaseRoutine(handler);
		}
		if ((handler = openDatabaseRoutine(szFile)) == -1) {
			MessageBox(
				g_hMainWindow,
				TEXT("Cannot Load DB!"),
				nullptr, MB_OK);
		}
	}
}

void ShowDB(void)
{
	if (handler == -1) {
		MessageBox(g_hMainWindow, TEXT("Error: First you must download a DB"), nullptr, MB_OK);
		return;
	}

	int index;
	GetDlgItemInt(g_hPageUpDownBuddy, GetDlgCtrlID(g_hPageUpDownBuddy), &index, 0);
	
	char buffer[100];
	GetWindowTextA(g_hPageUpDownBuddy, buffer, 100);
	auto listPhoneBook = getPhoneBook(handler, atoi(buffer) * 10, 10);
	Display(*listPhoneBook);
	delete listPhoneBook;
}

void SearchDB(void)
{
	//    PHONE_DB_RECORD recTemplate;
	//
	//    if (g_DatabasePtr == nullptr) {
	//        MessageBox(g_hMainWindow, TEXT("Error: First you must download a DB"), nullptr, MB_OK);
	//        return;
	//    }
	//
	//    GetWindowTextA(g_hInputBox[0], recTemplate->phone, sizeof recTemplate->phone);
	//    GetWindowTextA(g_hInputBox[1], recTemplate->lastname, sizeof recTemplate->lastname);
	//    GetWindowTextA(g_hInputBox[2], recTemplate->name, sizeof recTemplate->name);
	//    GetWindowTextA(g_hInputBox[3], recTemplate->patronym, sizeof recTemplate->patronym);
	//    GetWindowTextA(g_hInputBox[4], recTemplate->street, sizeof recTemplate->street);
	//    GetWindowTextA(g_hInputBox[5], recTemplate->house, sizeof recTemplate->house);
	//    GetWindowTextA(g_hInputBox[6], recTemplate->housing, sizeof recTemplate->housing);
	//    GetWindowTextA(g_hInputBox[7], recTemplate->apartment, sizeof recTemplate->apartment);
	//
	//    auto countOfNotEmtyFields = 0;
	//
	//#define CHECK_IF_FIELD_NOT_EMPTY(field_name)\
	//    if (recTemplate->field_name[0] != '\0') countOfNotEmtyFields++;
	//
	//    CHECK_IF_FIELD_NOT_EMPTY(phone);
	//    CHECK_IF_FIELD_NOT_EMPTY(lastname);
	//    CHECK_IF_FIELD_NOT_EMPTY(name);
	//    CHECK_IF_FIELD_NOT_EMPTY(street);
	//    CHECK_IF_FIELD_NOT_EMPTY(patronym);
	//    CHECK_IF_FIELD_NOT_EMPTY(house);
	//    CHECK_IF_FIELD_NOT_EMPTY(housing);
	//    CHECK_IF_FIELD_NOT_EMPTY(apartment);
	//
	//#undef CHECK_IF_FIELD_NOT_EMPTY
	//
	//    if (countOfNotEmtyFields > 0) {
	//        Display(&recTemplate, countOfNotEmtyFields);
	//    } else {
	//        MessageBox(g_hMainWindow, TEXT("Enter data to search!"), nullptr, MB_OK);
	//    }
}

void AddDB(void)
{
	PhoneBookStruct recTemplate;

	if (handler == -1) {
		MessageBox(g_hMainWindow, TEXT("Error: First you must download a DB"), nullptr, MB_OK);
		return;
	}

	GetWindowText(g_hInputBox[0], recTemplate.phone, sizeof recTemplate.phone);
	GetWindowText(g_hInputBox[1], recTemplate.lastName, sizeof recTemplate.lastName);
	GetWindowText(g_hInputBox[2], recTemplate.firstName, sizeof recTemplate.firstName);
	GetWindowText(g_hInputBox[3], recTemplate.patronym, sizeof recTemplate.patronym);
	GetWindowText(g_hInputBox[4], recTemplate.street, sizeof recTemplate.street);
	GetWindowText(g_hInputBox[5], recTemplate.house, sizeof recTemplate.house);
	GetWindowText(g_hInputBox[6], recTemplate.housing, sizeof recTemplate.housing);
	GetWindowText(g_hInputBox[7], recTemplate.apartment, sizeof recTemplate.apartment);
	recTemplate.isFree = 1;

	if (!addPhoneBookRoutine(handler, recTemplate)) {
		MessageBox(g_hMainWindow, TEXT("Don't add data!"), nullptr, MB_OK);
	}
}

// random generator
//for (int i = 0; i < 100; i++)
//{
//	static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
//
//#define CHANGE(object)\
//\
//		for (int i = 0; i < sizeof(recTemplate.object); i++)\
//			recTemplate.object[i] = charset[rand() % charset.length()];\
//
//	CHANGE(phone);
//	CHANGE(lastName);
//	CHANGE(firstName);
//	CHANGE(patronym);
//	CHANGE(street);
//	CHANGE(house);
//	CHANGE(housing);
//	CHANGE(apartment);
//
//	addPhoneBookRoutine(handler, recTemplate);
//}


void Display(const ListPhoneBookStruct& recTemplate)
{
	ListView_DeleteAllItems(g_hListView);
	for (UINT i = recTemplate.count; i > 0; --i)
	{
		PhoneBookStruct& currectPhoneBook = recTemplate.phoneBook[i - 1];
		if (AddItemToListViewW(g_hListView, currectPhoneBook.phone, 0, 0)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.lastName, 0, 1)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.firstName, 0, 2)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.patronym, 0, 3)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.street, 0, 4)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.house, 0, 5)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.housing, 0, 6)
			|| AddItemToListViewW(g_hListView, currectPhoneBook.apartment, 0, 7))
		{
			DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
			HLOCAL hlocal = nullptr;

			FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
				FORMAT_MESSAGE_ALLOCATE_BUFFER,
				nullptr, GetLastError(), systemLocale,
				PTSTR(&hlocal), 0, nullptr);
			MessageBox(g_hMainWindow,
				TEXT("Something went wrong! Check your DB"),
				nullptr,
				MB_OK);

			MessageBox(nullptr, static_cast<TCHAR*>(hlocal), nullptr, MB_OK);
			LocalFree(hlocal);
			break;
		}
	}
}