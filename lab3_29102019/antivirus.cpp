// antivirus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include "vector"

#define VIRUS_SIGNATURE "55 89 e5 53 57 56 81 ec 9c 00 00 00 8d 45 08 89" 

namespace fs = std::filesystem;

int isFileViral(const fs::path exeFilePath) {
	std::vector<unsigned char> bytes; {
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

int main(int argc, char** argv) {
	const fs::path currentDirPath = fs::current_path();
    const fs::path exeFilePath = std::string(argv[0]) + ".exe";

	for (const auto& entry : fs::directory_iterator(currentDirPath)) {
		if (entry.is_directory()) continue;
		const fs::path filePath = entry.path();
		if (filePath == exeFilePath) continue;
		if (filePath.extension() == ".exe") {
		    bool isVirus = isFileViral(filePath);
			std::cout << "File: " << filePath << " -- " << (isVirus ? "True" : "False") << std::endl;
			if (isVirus) {
			    fs::remove(filePath);
			}

		}
	}

	system("pause");
}
