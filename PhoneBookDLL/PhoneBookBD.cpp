#include "stdafx.h"
#include "PhoneBookBD.h"

PhoneBookBD::PhoneBookBD(HANDLE bdHandle, const LARGE_INTEGER& fileSize)
{
	fileMapping = CreateFileMapping(bdHandle, NULL, PAGE_READWRITE, getSizeHigh(fileSize), getSizeLow(fileSize), MAP_FILE_OBJECT_NAME);
	if (!fileMapping)
		throw std::invalid_argument("Error file size\n");
}

PhoneBookBD::~PhoneBookBD()
{
	clearUp();
}

bool PhoneBookBD::addPhoneBook(const PhoneBookStruct & phoneBook)
{
	return tryAddPhoneBook(phoneBook);
}

bool PhoneBookBD::deletePhoneBook(ULONG index)
{
	return isInZone(index) ? tryDeletePhoneBook(index) : false;
}

bool PhoneBookBD::changePhoneBook(ULONG index, const PhoneBookStruct & phoneBook)
{
	return isInZone(index) ? tryChangePhoneBook(index, phoneBook) : false;
}

std::vector<PhoneBookStruct> PhoneBookBD::getPhoneBook(ULONG index, ULONG count)
{
	return isInZone(index) ? tryGetPhoneBook(index, count) : std::vector<PhoneBookStruct>();
}

LPVOID PhoneBookBD::getMappingData(DWORD offsetLow, DWORD offsetHigh, SIZE_T length)
{
	return MapViewOfFile(fileMapping, FILE_MAP_ALL_ACCESS, offsetHigh, offsetLow, length);
}

DWORD PhoneBookBD::getSizeLow(const LARGE_INTEGER & fileSize)
{
	return getMapSizeLow(fileSize);
}

DWORD PhoneBookBD::getSizeHigh(const LARGE_INTEGER & fileSize)
{
	return getMapSizeHigh(fileSize);
}

void PhoneBookBD::clearUp()
{
	CloseHandle(fileMapping);
}
