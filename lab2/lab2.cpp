// lab2.cpp: определяет точку входа для консольного приложения.
//

#include <windows.h> 
#include <strsafe.h>

int main()
{
	WCHAR  fileName[MAX_PATH];
	wchar_t cmd[MAX_PATH + 100];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, fileName, MAX_PATH);

	swprintf(cmd, L"cmd.exe /c del \"%s\"", fileName);

	CreateProcess(NULL, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return 0;
}
