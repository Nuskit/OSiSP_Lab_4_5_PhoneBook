#pragma once

#include "Resource.h"
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <CommCtrl.h>
#include <Uxtheme.h>
#include <Commdlg.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>

struct PhoneBookStruct;
struct ListPhoneBookStruct;
typedef UINT (*OPENDATABASEROUTINE)(LPWSTR bdPathName);
typedef bool (*CLOSEDATABASEROUTINE)(UINT handler);

typedef bool (*ADDPHONEBOOKROUTINE)(UINT handler, const PhoneBookStruct& phoneBook);
typedef bool (*DELETEPHONEBOOKROUTINE)(UINT handler, ULONG index);
typedef bool (*CHANGEPHONEBOOK)(UINT handler, ULONG index, const PhoneBookStruct& phoneBook);
typedef ListPhoneBookStruct* (*GETPHONEBOOKROUTINE)(UINT handler, ULONG index, ULONG count);
typedef ListPhoneBookStruct* (*FINDPHONEBOOKROUTINE)(UINT handler, const PhoneBookStruct& phoneBook);