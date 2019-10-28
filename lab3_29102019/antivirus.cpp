// antivirus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

#define EXE_NAME "antivirus.exe"
#define VIRUS_SIGNATURE "55 89 e5 53 57 56 81 ec 9c 00 00 00 8d 45 08 89" 

namespace fs = std::filesystem;

int isFileViral(const fs::path exeFilePath) {
	std::vector<unsigned char> bytes;
	{
		std::ifstream in(exeFilePath, std::ios::binary);
		bytes.assign(std::istreambuf_iterator<char>(in >> std::noskipws),
			std::istreambuf_iterator<char>());
		in.close();
	}

	std::ostringstream oss;
	oss << std::hex << std::setfill('0');
	for (int v : bytes) {
		oss << std::setw(2) << v << ' ';
	}
	std::string str = oss.str();

	return str.find(VIRUS_SIGNATURE) != std::string::npos;
}

int main()
{
	const fs::path currentDirPath = fs::current_path();
	const fs::path exeFilePath = currentDirPath / EXE_NAME;

	for (const auto& entry : fs::directory_iterator(currentDirPath)) {
		if (entry.is_directory()) continue;
		const fs::path filePath = entry.path();
		if (filePath == exeFilePath) continue;
		if (filePath.extension() == ".exe") {
			std::cout << "File: " << filePath << " -- " << (isFileViral(filePath) ? "True" : "False") << std::endl;

		}
	}

	system("pause");
}
