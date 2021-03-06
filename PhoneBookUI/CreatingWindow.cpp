#include "stdafx.h"
#include "CreatingWindow.h"
#include "ListViewFunctions.h"
#include "ButtonHandlers.h"
#include "PhoneBookStruct.h"

#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "Comctl32.lib")
#define valMax -100000
#define valMin 0

extern HINSTANCE    hInst;

HWND                g_hMainWindow;
HWND                g_hListView;
HWND                g_hLoadDatabaseButton;
HWND                g_hSearchButton;
HWND                g_hShowButton;
HWND								g_haddButton;
HWND								g_hPageUpDown;
HWND                g_hExitButton;
HWND                g_hInputBox[8];
HWND								g_hPageUpDownBuddy;

const int width_Mp = 7;

struct {
	TCHAR *name;
	int width;
} columns[] = {
		{ TEXT("Number:"), PHONE_DB_PHONE_LEN*width_Mp },
		{ TEXT("Surname:"), PHONE_DB_LASTNAME_LEN*width_Mp },
		{ TEXT("Name:"), PHONE_DB_NAME_LEN*width_Mp },
		{ TEXT("Patronym:"), PHONE_DB_PATRONYM_LEN*width_Mp },
		{ TEXT("Street:"), PHONE_DB_STREET_LEN*width_Mp },
		{ TEXT("House:"), PHONE_DB_HOUSE_LEN*width_Mp },
		{ TEXT("Housing:"), PHONE_DB_HOUSING_LEN*width_Mp },
		{ TEXT("Apartment:"), PHONE_DB_APARTMENT_LEN*width_Mp }
};

const int cColumns = _countof(columns);

#define MAX_LOADSTRING 100
TCHAR       szTitle[MAX_LOADSTRING];
TCHAR       szWindowClass[MAX_LOADSTRING];

BOOL CreateMainWindow(int nCmdShow)
{
	LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInst, IDC_PHONEBOOKUI, szWindowClass, MAX_LOADSTRING);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PHONEBOOKUI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(7);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	auto mwWidth = 30;
	for (auto i = 0; i < cColumns; i++) {
		mwWidth += columns[i].width + 1;
	}

	g_hMainWindow = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0,
		mwWidth + 17, 600,
		NULL, NULL, hInst, NULL);

	RECT mainWindowRect;
	GetClientRect(g_hMainWindow, &mainWindowRect);

	g_hListView = CreateWindowEx(
		WS_EX_STATICEDGE,
		WC_LISTVIEW,
		nullptr,
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS,
		6, 63, // TODO: width
		mainWindowRect.right - 10, mainWindowRect.bottom - 69,
		g_hMainWindow, nullptr, hInst, nullptr);

	for (auto i = 0; i < cColumns; i++) {
		AddColumnToListView(g_hListView, columns[i].name, i, columns[i].width + 1);
	}

	const auto
		loadButtonWidth = 120,
		loadButtonHeigth = 25,
		loadButtonPosX = 6,
		loadButtonPosY = 6;

	g_hLoadDatabaseButton = CreateWindow(
		WC_BUTTON,
		TEXT("Load DataBase"),
		WS_CHILD | WS_VISIBLE,
		loadButtonPosX, loadButtonPosY,
		loadButtonWidth, loadButtonHeigth,
		g_hMainWindow,
		NULL,
		hInst,
		NULL);

	const auto
		pageUpDownWidth = loadButtonWidth,
		pageUpDownHeigth = loadButtonHeigth,
		pageUpDownPosX = loadButtonPosX + loadButtonWidth + 6,
		pageUpDownPosY = loadButtonPosY;
	g_hPageUpDownBuddy= CreateWindowExA(
		0,
		WC_EDITA,
		nullptr,
		WS_VISIBLE | WS_CHILD | ES_CENTER |ES_NUMBER,
		pageUpDownPosX, pageUpDownPosY,
		pageUpDownWidth, pageUpDownHeigth,
		g_hMainWindow,
		nullptr, hInst, nullptr);
	g_hPageUpDown = CreateWindowExA(WS_EX_LEFT | WS_EX_LTRREADING,
		UPDOWN_CLASSA,
		NULL,
		WS_CHILDWINDOW | WS_VISIBLE
		| UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
		0, 0,
		0, 0,
		g_hMainWindow,
		NULL,
		hInst,
		NULL);

	SendMessage(g_hPageUpDown, UDM_SETRANGE, 0, MAKELPARAM(valMax, valMin));    // Sets the controls direction 
																																							// and range.


	const auto
		showButtonWidth = loadButtonWidth,
		showButtonHeigth = loadButtonHeigth,
		showButtonPosX = pageUpDownPosX + loadButtonWidth + 6,
		showButtonPosY = loadButtonPosY;

	g_hShowButton = CreateWindow(
		WC_BUTTON,
		TEXT("Show All"),
		WS_CHILD | WS_VISIBLE,
		showButtonPosX, showButtonPosY,
		showButtonWidth, showButtonHeigth,
		g_hMainWindow,
		NULL,
		hInst,
		NULL);

	const auto
		searchButtonWidth = loadButtonWidth,
		searchButtonHeigth = loadButtonHeigth,
		searchButtonPosX = showButtonPosX + loadButtonWidth + 6,
		searchButtonPosY = loadButtonPosY;
	g_hSearchButton = CreateWindow(
		WC_BUTTON,
		TEXT("Search"),
		WS_CHILD | WS_VISIBLE,
		searchButtonPosX, searchButtonPosY,
		searchButtonWidth, searchButtonHeigth,
		g_hMainWindow,
		NULL,
		hInst,
		NULL);

	const auto
		addButtonWidth = loadButtonWidth,
		addButtonHeigth = loadButtonHeigth,
		addButtonPosX = searchButtonPosX + loadButtonWidth + 6,
		addButtonPosY = loadButtonPosY;
	g_haddButton = CreateWindow(
		WC_BUTTON,
		TEXT("Add"),
		WS_CHILD | WS_VISIBLE,
		addButtonPosX, addButtonPosY,
		addButtonWidth, addButtonHeigth,
		g_hMainWindow,
		NULL,
		hInst,
		NULL);



	auto inputBoxPosX = loadButtonPosX,
		inputBoxPosY = loadButtonPosY + loadButtonHeigth + 6,
		inputBoxHeigth = 20;

	for (auto i = 0; i < cColumns; i++) {
		auto inputBoxWidth = columns[i].width;

		g_hInputBox[i] = CreateWindowEx(
			0,
			WC_EDIT,
			nullptr,
			WS_VISIBLE | WS_CHILD | ES_LEFT,
			inputBoxPosX, inputBoxPosY,
			inputBoxWidth, inputBoxHeigth,
			g_hMainWindow,
			nullptr, hInst, nullptr);

		inputBoxPosX += columns[i].width + 1;

		if (g_hInputBox[i] == nullptr) {
			MessageBox(nullptr, TEXT("Can not Create Window!"), nullptr, MB_OK);
			exit(0);
		}
	}

	ShowWindow(g_hMainWindow, nCmdShow);
	UpdateWindow(g_hMainWindow);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case BN_CLICKED:
		{
			auto hBtn = HWND(lParam);

			if (hBtn == g_hLoadDatabaseButton) {
				LoadDB();
			}
			else if (hBtn == g_hSearchButton) {
				SearchDB();
			}
			else if (hBtn == g_hShowButton) {
				ShowDB();
			}
			else if (hBtn == g_haddButton) {
				AddDB();
			}
		}
		break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
