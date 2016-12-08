#pragma once
#include "stdafx.h"
#include <map>

class PhoneBookApi;
typedef std::map<UINT, PhoneBookApi*> mapSingleConnects;

struct PhoneBookStruct;
class DatabaseExport
{
public:
	DatabaseExport();
	~DatabaseExport();
	UINT OpenDatabase(LPWSTR bdPathName);
	bool CloseDatabase(UINT handler);

	bool addPhoneBook(UINT handler, const PhoneBookStruct& phoneBook);
	bool deletePhoneBook(UINT handler, ULONG index);
	bool changePhoneBook(UINT handler, ULONG index, const PhoneBookStruct& phoneBook);
	std::vector<PhoneBookStruct> getPhoneBook(UINT handler, ULONG index, ULONG count);
	std::vector<PhoneBookStruct> findPhoneBook(UINT handler, const PhoneBookStruct& phoneBook);
private:
	mapSingleConnects connects;
	UINT lastHandler;
};
