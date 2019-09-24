// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h> 
#include <strsafe.h>
#include <iostream>
#include <string>
#define DEFAULT_PASSWORD_ATTEMPTS 3
#define KEY_NAME_LAB2 L"PASSWORD_ATTEMPS_LAB2"
#define PASSWORD L"ruialectuopj2"

void setPasswordAttempts(int value) {
	HKEY hKey = HKEY_CURRENT_USER;
	int size = sizeof(int);

	RegSetValueEx(hKey, KEY_NAME_LAB2, NULL, REG_DWORD, (BYTE*)& value, size);
}

int getPasswordAttempts() {
	DWORD size = sizeof(DWORD);
	DWORD dataType;
	DWORD attempt;
	HKEY hKey = HKEY_CURRENT_USER;
	DWORD options = 0;
	REGSAM samDesired = KEY_READ;
	HKEY OpenResult;
	DWORD flags = RRF_RT_ANY;

	LSTATUS error = RegOpenKeyEx(hKey, NULL, options, samDesired, &OpenResult);
	if (!error) {
		error = RegGetValue(OpenResult, NULL, KEY_NAME_LAB2, flags, &dataType, &attempt, &size);
	}

	if (error) {
		setPasswordAttempts(DEFAULT_PASSWORD_ATTEMPTS);
		return DEFAULT_PASSWORD_ATTEMPTS;
	}
	return attempt;

}

void removeMyself() {
	WCHAR fileName[MAX_PATH];
	WCHAR cmd[MAX_PATH + 100];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, fileName, MAX_PATH);

	swprintf(cmd, L"cmd.exe /c del \"%s\"", fileName);

	CreateProcess(NULL, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

std::string encode(std::string tmp) {
	for (int i = 0; i < tmp.size(); i++)
		tmp[i] = tmp[i] ^ DEFAULT_PASSWORD_ATTEMPTS;
	return tmp;
}

int main(int argc, char* argv[]) {
	std::wstring keyName(PASSWORD);
	std::string password = encode(std::string(keyName.begin(), keyName.end()));//argv[0];
	std::string tmp = "";
	int i = getPasswordAttempts();
	std::cout << "You have " << i << " attemps" << std::endl;
	while (i > 0) {
		std::cout << "Enter your password: ";
		std::getline(std::cin, tmp);
		if (tmp == password) {
			std::cout << "You are win" << std::endl;
			setPasswordAttempts(3);
			getchar();
			return 0;
		}
		setPasswordAttempts(--i);
	}
	std::cout << "Ha-ha, you are lose" << std::endl;
	Sleep(5);

	removeMyself();
	return 0;
}
