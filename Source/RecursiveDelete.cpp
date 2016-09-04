// RecursiveDelete.cpp : Defines the entry point for the console application.
// deletes files and directories, used on headless systems to remove...
#include "stdafx.h"
#include <windows.h>

int DeleteDirectory(WCHAR * wpath);

int wmain(int argc, wchar_t * argv[])
{
    if (argc > 1)
    {
        DeleteDirectory(argv[1]);
    }
    return 0;
}

int DeleteDirectory(WCHAR * wpath)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    WCHAR TargetPath[MAX_PATH];
    WCHAR SearchPath[MAX_PATH];
    errno_t result = wcscpy_s(SearchPath, MAX_PATH, wpath);
    result |= wcscat_s(SearchPath, MAX_PATH, L"\\*.*");
    if (0 == result)
    {
        hFind = FindFirstFile(SearchPath, &FindFileData);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                result = wcscpy_s(TargetPath, MAX_PATH, wpath);
                result |= wcscat_s(TargetPath, MAX_PATH, L"\\");
                result |= wcscat_s(TargetPath, MAX_PATH, FindFileData.cFileName);
                if(0 != result)
                {
                    break;
                }
                else if (0 == (FILE_ATTRIBUTE_DEVICE & FindFileData.dwFileAttributes))
                {
                    if (0 != (FILE_ATTRIBUTE_DIRECTORY & FindFileData.dwFileAttributes ))
                    {
                        if ((wcscmp(FindFileData.cFileName, L".")) &&
                                (wcscmp(FindFileData.cFileName, L"..")))
                        {
                            DeleteDirectory(TargetPath);
                            RemoveDirectory(TargetPath);
                        }
                    }
					else
					{
						DWORD file_attributes = GetFileAttributesW(TargetPath);
						if((INVALID_FILE_ATTRIBUTES != file_attributes) &&
							(file_attributes & FILE_ATTRIBUTE_READONLY))
						{
							SetFileAttributes(TargetPath, file_attributes & ~FILE_ATTRIBUTE_READONLY);
						}
                        DeleteFile(TargetPath);
                    }
                }
            }
            while (FindNextFile(hFind, &FindFileData));
            FindClose(hFind);
        }
    }
    return result;
}
