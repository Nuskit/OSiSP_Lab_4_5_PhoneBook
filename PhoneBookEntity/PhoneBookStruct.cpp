#include "PhoneBookStruct.h"

ListPhoneBookStruct::ListPhoneBookStruct(PhoneBookStruct * copyPhoneBook, UINT size) :phoneBook(new PhoneBookStruct[size]), count(size)
{
	memcpy(phoneBook, copyPhoneBook, sizeof(PhoneBookStruct)*size);
}

ListPhoneBookStruct::~ListPhoneBookStruct()
{
	delete[] phoneBook;
}
