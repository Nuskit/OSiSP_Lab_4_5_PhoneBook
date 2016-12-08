#include "stdafx.h"
#include "DatabaseExport.h"
#include "PhoneBookEntity.h"
#include "PhoneBookStruct.h"

DatabaseExport::DatabaseExport() :lastHandler(-1)
{
}

DatabaseExport::~DatabaseExport()
{
	for (auto& singleConnect : connects)
		delete singleConnect.second;
	connects.clear();
}

UINT DatabaseExport::OpenDatabase(LPWSTR bdPathName)
{
	int connectLink = lastHandler + 1;
	try
	{
		connects[connectLink] = new PhoneBookEntity(bdPathName);
		++lastHandler;
	}
	catch (...)
	{
		connectLink = -1;
	}
	return connectLink;
}

bool DatabaseExport::CloseDatabase(UINT handler)
{
	bool isCloseConnect = false;
	auto itMapConnects = connects.find(handler);
	if (itMapConnects != connects.end())
	{
		delete (*itMapConnects).second;
		connects.erase(itMapConnects);
		isCloseConnect = true;
	}
	return isCloseConnect;
}

bool DatabaseExport::addPhoneBook(UINT handler, const PhoneBookStruct & phoneBook)
{
	auto itMapConnects = connects.find(handler);
	if (itMapConnects != connects.end())
	{
		return (*itMapConnects).second->addPhoneBook(phoneBook);
	}
	return false;
}

bool DatabaseExport::deletePhoneBook(UINT handler, ULONG index)
{
	auto itMapConnects = connects.find(handler);
	if (itMapConnects != connects.end())
	{
		return (*itMapConnects).second->deletePhoneBook(index);
	}
	return false;
}

bool DatabaseExport::changePhoneBook(UINT handler, ULONG index, const PhoneBookStruct & phoneBook)
{
	auto itMapConnects = connects.find(handler);
	if (itMapConnects != connects.end())
	{
		return (*itMapConnects).second->changePhoneBook(index, phoneBook);
	}
	return false;
}

std::vector<PhoneBookStruct> DatabaseExport::getPhoneBook(UINT handler, ULONG index, ULONG count)
{
	auto itMapConnects = connects.find(handler);
	if (itMapConnects != connects.end())
	{
		return (*itMapConnects).second->getPhoneBook(index, count);
	}
	return std::vector<PhoneBookStruct>();
}
