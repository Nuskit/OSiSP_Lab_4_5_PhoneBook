#pragma once
#include <Windows.h>

#define PHONE_DB_PHONE_LEN      8
#define PHONE_DB_LASTNAME_LEN   32
#define PHONE_DB_NAME_LEN       32
#define PHONE_DB_PATRONYM_LEN   32
#define PHONE_DB_STREET_LEN     30
#define PHONE_DB_HOUSE_LEN      8
#define PHONE_DB_HOUSING_LEN    8
#define PHONE_DB_APARTMENT_LEN  8

struct PhoneBookStruct
{
	TCHAR lastName[PHONE_DB_LASTNAME_LEN];
	TCHAR firstName[PHONE_DB_NAME_LEN];
	TCHAR patronym[PHONE_DB_PATRONYM_LEN];
	TCHAR phone[PHONE_DB_PHONE_LEN];
	TCHAR house[PHONE_DB_HOUSE_LEN];
	TCHAR housing[PHONE_DB_HOUSING_LEN];
	TCHAR apartment[PHONE_DB_APARTMENT_LEN];
	TCHAR street[PHONE_DB_STREET_LEN];
	BOOL isFree;
};

#define SIZE_ENTITY sizeof(PhoneBookStruct)

struct ListPhoneBookStruct
{
	ListPhoneBookStruct(PhoneBookStruct* copyPhoneBook, UINT size);
	~ListPhoneBookStruct();
	UINT count;
	PhoneBookStruct* phoneBook;
};
