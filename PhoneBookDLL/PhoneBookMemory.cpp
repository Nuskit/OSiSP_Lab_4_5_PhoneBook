#include "stdafx.h"
#include "PhoneBookMemory.h"

PhoneBookMemory::PhoneBookMemory(HANDLE bdHandle, const LARGE_INTEGER & fileSize) : PhoneBookBD(bdHandle, fileSize),
bdBase(static_cast<PhoneBookStruct*>(getMappingData(getMapSizeLow(fileSize), getMapSizeHigh(fileSize), MAX_BD_IN_MEMORY_SIZE)))
{
}

PhoneBookMemory::~PhoneBookMemory()
{
	UnmapViewOfFile(bdBase);
}

DWORD PhoneBookMemory::getMapSizeHigh(const LARGE_INTEGER & fileSize)
{
	return 0;
}

DWORD PhoneBookMemory::getMapSizeLow(const LARGE_INTEGER & fileSize)
{
	return MAX_BD_IN_MEMORY_SIZE;
}

bool PhoneBookMemory::getFreeBlock(PhoneBookStruct* freeBlock)
{
	freeBlock = bdBase;
	ULONG count = 0;
	while ((freeBlock->isFree) && (++count <= MAX_COUNT_BLOCK_IN_MEMORY))
		++freeBlock;
	return count <= MAX_COUNT_BLOCK_IN_MEMORY;
}

bool PhoneBookMemory::isInZone(ULONG index) const
{
	return index < MAX_COUNT_BLOCK_IN_MEMORY;
}

bool PhoneBookMemory::tryAddPhoneBook(const PhoneBookStruct & phoneBook)
{
	bool isComplete;
	PhoneBookStruct* freeBlock = nullptr;
	if ((isComplete = getFreeBlock(freeBlock)))
		CopyMemory(freeBlock, &phoneBook, SIZE_ENTITY);
	return isComplete;
}

bool PhoneBookMemory::tryDeletePhoneBook(ULONG index)
{
	bdBase[index].isFree = 0;
	return true;
}

bool PhoneBookMemory::tryChangePhoneBook(ULONG index, const PhoneBookStruct & phoneBook)
{
	CopyMemory(&(bdBase[index]), &phoneBook, SIZE_ENTITY);
	return true;
}

std::vector<PhoneBookStruct> PhoneBookMemory::tryGetPhoneBook(ULONG index, ULONG count)
{
	return std::vector<PhoneBookStruct>(&bdBase[index], &bdBase[index] + count);
}
