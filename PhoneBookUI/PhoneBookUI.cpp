#include "stdafx.h"
#include "CreatingWindow.h"
#include "LoadDatabase.h"

HINSTANCE                   hInst;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hInst = hInstance;

	if (LoadDatabaseDLL() == FALSE) {
		return EXIT_FAILURE;
	}

	CreateMainWindow(nCmdShow);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return int(msg.wParam);
}
