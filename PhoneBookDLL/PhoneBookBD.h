#pragma once
#include "stdafx.h"
#include "PhoneBookStruct.h"
#include "PhoneBookApi.h"

#define MAX_COUNT_BLOCK_IN_MEMORY 1000
#define MAX_COUNT_BLOCK_IN_FILE 1000000

#define MAX_BD_IN_MEMORY_SIZE MAX_COUNT_BLOCK_IN_MEMORY * SIZE_ENTITY
#define MAX_BD_IN_FILE_SIZE MAX_COUNT_BLOCK_IN_FILE * SIZE_ENTITY
#define MAP_FILE_OBJECT_NAME TEXT("PHONE_BD")

class PhoneBookBD: public PhoneBookApi
{
public:
	virtual void init(HANDLE bdHandle, const LARGE_INTEGER& fileSize);
	virtual ~PhoneBookBD();
	bool addPhoneBook(const PhoneBookStruct& phoneBook);
	bool deletePhoneBook(ULONG index);
	bool changePhoneBook(ULONG index, const PhoneBookStruct& phoneBook);
	std::vector<PhoneBookStruct> getPhoneBook(ULONG index, ULONG count = 1);


	virtual DWORD getMapSizeHigh(const LARGE_INTEGER& fileSize) = 0;
	virtual DWORD getMapSizeLow(const LARGE_INTEGER& fileSize) = 0;
protected:
	virtual bool tryAddPhoneBook(const PhoneBookStruct& phoneBook) = 0;
	virtual bool tryDeletePhoneBook(ULONG index) = 0;
	virtual bool tryChangePhoneBook(ULONG index, const PhoneBookStruct& phoneBook) = 0;
	virtual std::vector<PhoneBookStruct> tryGetPhoneBook(ULONG index, ULONG count = 1) = 0;
	virtual bool isInZone(ULONG index) const = 0;
	LPVOID getMappingData(DWORD offsetLow, DWORD offsetHigh, SIZE_T length);
private:
	DWORD getSizeLow(const LARGE_INTEGER& fileSize);
	DWORD getSizeHigh(const LARGE_INTEGER& fileSize);
	void clearUp();

	HANDLE fileMapping;
};
