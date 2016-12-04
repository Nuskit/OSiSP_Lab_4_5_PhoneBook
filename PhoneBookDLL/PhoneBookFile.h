#pragma once
#include "stdafx.h"
#include "PhoneBookBD.h"

class PhoneBookFile :public PhoneBookBD
{
public:
	PhoneBookFile(HANDLE bdHandle, const LARGE_INTEGER& fileSize) :PhoneBookBD(bdHandle, fileSize) { throw std::runtime_error("Not implemented"); };
protected:
	virtual DWORD getMapSizeHigh(const LARGE_INTEGER & fileSize) override;
	virtual DWORD getMapSizeLow(const LARGE_INTEGER & fileSize) override;
	virtual bool tryAddPhoneBook(const PhoneBookStruct & phoneBook) override;
	virtual bool tryDeletePhoneBook(ULONG index) override;
	virtual bool tryChangePhoneBook(ULONG index, const PhoneBookStruct & phoneBook) override;
	virtual std::vector<PhoneBookStruct> tryGetPhoneBook(ULONG index, ULONG count = 1) override;
	virtual bool isInZone(ULONG index) const override;
};
