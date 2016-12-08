#pragma once
#include "stdafx.h"

struct PhoneBookStruct;
class PhoneBookApi
{
public:
	virtual ~PhoneBookApi() {}
	virtual bool addPhoneBook(const PhoneBookStruct& phoneBook) = 0;
	virtual bool deletePhoneBook(ULONG index) = 0;
	virtual bool changePhoneBook(ULONG index, const PhoneBookStruct& phoneBook) = 0;
	virtual std::vector<PhoneBookStruct> getPhoneBook(ULONG index, ULONG count) = 0;
	virtual PhoneBookStruct getConcreteBook(ULONG index) = 0;
	virtual std::vector<PhoneBookStruct> findPhoneBook(const PhoneBookStruct& phoneBook, int index) = 0;
};
