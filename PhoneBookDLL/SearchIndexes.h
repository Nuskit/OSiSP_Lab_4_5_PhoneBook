#pragma once
#include "AblTree.h"
#include "PhoneBookStruct.h"
#include "PhoneBookBD.h"

template<class T>
class SearchIndexes :public PhoneBookApi
{
public:
	SearchIndexes(PhoneBookBD *bd, int fieldID):indexes(nullptr), bd_(bd), fieldID_(fieldID)
	{
		TCHAR buffer[260];
		wsprintf(buffer, L"INDEX-%d", fieldID);
		fileHwnd = CreateFile(buffer, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fileHwnd == INVALID_HANDLE_VALUE)
			throw std::invalid_argument("Error file name\n");

		LARGE_INTEGER fileSize;
		if (GetFileSizeEx(fileHwnd, &fileSize) == FALSE)
		{
			throw std::invalid_argument("Error file size\n");
		}

		fileMapping = CreateFileMapping(fileHwnd, NULL, PAGE_READWRITE, bd->getMapSizeHigh(fileSize), bd->getMapSizeLow(fileSize), buffer);
		if (!fileMapping)
			throw std::invalid_argument("Error file size\n");

		indexes = new AblTree<UINT>(fileMapping, fileSize);

		bool isData;
		ULONG index = 0;
		do
		{
			PhoneBookStruct& phoneBook = bd->getConcreteBook(index);
			if (isData = phoneBook.isFree)
			{
				insertIndexes(phoneBook);
				++index;
			}
		} while (isData);
	}

	static T GetFieldById(const PhoneBookStruct& phoneBook, int id)
	{
		switch (id)
		{
		case 0:
			return phoneBook.lastName;
		case 1:
			return phoneBook.phone;
		case 2:
			return phoneBook.house;
		default:
			throw std::invalid_argument("invalid field ID");
		}
	}

	void insertIndexes(const PhoneBookStruct & phoneBook)
	{
		indexes->insert(getHash(phoneBook));
	}

	virtual bool addPhoneBook(const PhoneBookStruct & phoneBook) override
	{
		bool isAdd;
		if (isAdd = bd_->addPhoneBook(phoneBook))
			insertIndexes(phoneBook);
		return isAdd;
	}
	virtual bool deletePhoneBook(ULONG index) override
	{
		return bd_->deletePhoneBook(index);
	}

	virtual bool changePhoneBook(ULONG index, const PhoneBookStruct & phoneBook) override
	{
		return bd_->changePhoneBook(index, phoneBook);
	}

	virtual std::vector<PhoneBookStruct> getPhoneBook(ULONG index, ULONG count) override
	{
		return bd_->getPhoneBook(index, count);
	}

	~SearchIndexes()
	{
		delete indexes;
		CloseHandle(fileMapping);
		CloseHandle(fileHwnd);
	}
private:
	HANDLE fileHwnd;
	HANDLE fileMapping;
	AblTree<UINT>* indexes;
	PhoneBookApi *bd_;
	int fieldID_;

	UINT getHash(const PhoneBookStruct& phoneBook)
	{
		return std::hash<T>()(GetFieldById(phoneBook, fieldID_));
	}

	// Унаследовано через PhoneBookApi
	virtual PhoneBookStruct getConcreteBook(ULONG index) override
	{
		throw std::logic_error("Not implemented");
	}

	// Унаследовано через PhoneBookApi
	virtual std::vector<PhoneBookStruct> findPhoneBook(const PhoneBookStruct & phoneBook, int index) override
	{
		std::vector<PhoneBookStruct> findBook;
		auto key = getHash(phoneBook);
		auto findIndex = indexes->findMinHead(key);
		if (findIndex != -1)
		{
			findBook.push_back(bd_->getConcreteBook(findIndex));
			do
			{
				if ((findIndex = indexes->findmin(key, findIndex, false))!=-1)
					findBook.push_back(bd_->getConcreteBook(findIndex));
			} while (findIndex != -1);
		}
		return findBook;
	}
};
