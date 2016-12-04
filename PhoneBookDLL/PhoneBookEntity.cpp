#include "stdafx.h"
#include "PhoneBookEntity.h"
#include "PhoneBookMemory.h"
#include "PhoneBookFile.h"

PhoneBookEntity::PhoneBookEntity(LPWSTR bdPathName)
{
	fileHwnd = CreateFile(bdPathName, FILE_ALL_ACCESS, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!fileHwnd)
		throw std::invalid_argument("Error file name\n");

	LARGE_INTEGER fileSize;
	if (GetFileSizeEx(fileHwnd, &fileSize) == FALSE)
	{
		clearUp();
		throw std::invalid_argument("Error file size\n");
	}

	phoneBd = fileSize.HighPart
		? dynamic_cast<PhoneBookApi*>(new PhoneBookFile(fileHwnd, fileSize))
		: dynamic_cast<PhoneBookApi*>(new PhoneBookMemory(fileHwnd, fileSize));
}

PhoneBookEntity::~PhoneBookEntity()
{
	clearUp();
	delete phoneBd;
}

void PhoneBookEntity::clearUp()
{
	CloseHandle(fileHwnd);
}

bool PhoneBookEntity::addPhoneBook(const PhoneBookStruct & phoneBook)
{
	return phoneBd->addPhoneBook(phoneBook);
}

bool PhoneBookEntity::deletePhoneBook(ULONG index)
{
	return phoneBd->deletePhoneBook(index);
}

bool PhoneBookEntity::changePhoneBook(ULONG index, const PhoneBookStruct & phoneBook)
{
	return phoneBd->changePhoneBook(index, phoneBook);
}

std::vector<PhoneBookStruct> PhoneBookEntity::getPhoneBook(ULONG index, ULONG count)
{
	return phoneBd->getPhoneBook(index, count);
}
