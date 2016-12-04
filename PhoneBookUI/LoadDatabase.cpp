#include "stdafx.h"
#include "LoadDatabase.h"

BOOL LoadDatabaseDLL(void)
{
}

BOOL GetFilename(TCHAR *szFile)
{
    OPENFILENAME ofn;

    memset(&ofn, 0, sizeof ofn);
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hInstance = hInst;
    ofn.hwndOwner = g_hMainWindow;
    ofn.lpstrFilter = nullptr;
    ofn.lpstrCustomFilter = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH * sizeof *szFile;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrTitle = nullptr;

    return GetOpenFileName(&ofn);
}
