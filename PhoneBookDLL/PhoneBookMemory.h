#pragma once
#include "stdafx.h"
#include "PhoneBookBD.h"

class PhoneBookMemory :public PhoneBookBD
{
public:
	virtual void init(HANDLE bdHandle, const LARGE_INTEGER& fileSize) override;
	~PhoneBookMemory();
	virtual PhoneBookStruct getConcreteBook(ULONG index) override;
protected:
	virtual bool tryAddPhoneBook(const PhoneBookStruct & phoneBook) override;
	virtual bool tryDeletePhoneBook(ULONG index) override;
	virtual bool tryChangePhoneBook(ULONG index, const PhoneBookStruct & phoneBook) override;
	virtual bool isInZone(ULONG index) const override;
	virtual std::vector<PhoneBookStruct> tryGetPhoneBook(ULONG index, ULONG count = 1) override;
	virtual DWORD getMapSizeHigh(const LARGE_INTEGER & fileSize) override;
	virtual DWORD getMapSizeLow(const LARGE_INTEGER & fileSize) override;
private:
	bool getFreeBlock(PhoneBookStruct*& freeBlock);
	PhoneBookStruct* bdBase;

	// ������������ ����� PhoneBookBD
	virtual std::vector<PhoneBookStruct> findPhoneBook(const PhoneBookStruct & phoneBook, int index) override;
};
