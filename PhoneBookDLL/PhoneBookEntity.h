#pragma once
#include "stdafx.h"
#include "PhoneBookApi.h"

class PhoneBookEntity :public PhoneBookApi
{
public:
	PhoneBookEntity(LPWSTR bdPathName);
	~PhoneBookEntity();
	virtual bool addPhoneBook(const PhoneBookStruct & phoneBook) override;
	virtual bool deletePhoneBook(ULONG index) override;
	virtual bool changePhoneBook(ULONG index, const PhoneBookStruct & phoneBook) override;
	virtual std::vector<PhoneBookStruct> getPhoneBook(ULONG index, ULONG count = 1) override;
private:
	PhoneBookApi* createBd(const LARGE_INTEGER& fileSize);
	void clearUp();

	HANDLE fileHwnd;
	PhoneBookApi *phoneBd;
};
