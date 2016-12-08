#include "stdafx.h"
#include "PhoneBookFile.h"

DWORD PhoneBookFile::getMapSizeHigh(const LARGE_INTEGER & fileSize)
{
	return MAX_BD_IN_FILE_SIZE / MAXDWORD;
}

DWORD PhoneBookFile::getMapSizeLow(const LARGE_INTEGER & fileSize)
{
	return MAX_BD_IN_FILE_SIZE % MAXDWORD;
}

bool PhoneBookFile::tryAddPhoneBook(const PhoneBookStruct & phoneBook)
{
	return false;
}

bool PhoneBookFile::tryDeletePhoneBook(ULONG index)
{
	return false;
}

bool PhoneBookFile::tryChangePhoneBook(ULONG index, const PhoneBookStruct & phoneBook)
{
	return false;
}

std::vector<PhoneBookStruct> PhoneBookFile::tryGetPhoneBook(ULONG index, ULONG count)
{
	return std::vector<PhoneBookStruct>();
}

bool PhoneBookFile::isInZone(ULONG index) const
{
	return false;
}

std::vector<PhoneBookStruct> PhoneBookFile::findPhoneBook(const PhoneBookStruct & phoneBook, int index)
{
	return std::vector<PhoneBookStruct>();
}

PhoneBookStruct PhoneBookFile::getConcreteBook(ULONG index)
{
	return PhoneBookStruct();
}
