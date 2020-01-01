#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

namespace fs = std::filesystem;

std::map<std::string, std::string> dict = {{"1e", "a"},
                                           {"2a", "SHIFT_PRESSED"},
                                           {"aa", "SHIFT_UNPRESSED"},
                                           {"3a", "CAPS_PRESSED"},
                                           {"ba", "CAPS_UNPRESSED"},
                                           {"39", " "}};

std::string getProgramText(const fs::path filePath) {
    std::vector<unsigned char> bytes; {
        std::ifstream in(filePath, std::ios::binary);
        bytes.assign(std::istreambuf_iterator<char>(in >> std::noskipws),
                     std::istreambuf_iterator<char>());
        in.close();
    }

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int v : bytes) {
        oss << std::setw(2) << v << ' ';
    }

    return oss.str();
}

std::vector<std::string> split_ws(std::string str)
{
    std::vector<std::string> result ;

    std::istringstream stm(str);
    std::string token ;
    while( stm >> token)
        result.push_back(token) ;

    return result;
}

int main() {
    const fs::path filePath = "MYFILE.BIN";
    //std::cout << getProgramText(filePath);
    auto text = split_ws(getProgramText(filePath));
    std::string rez = "";
    bool isShifted = false;

    for(auto symbol : text) {
        auto pos = dict.find(symbol);
        if (pos != dict.end()) {
            auto value = dict[symbol];
            if (value == "SHIFT_PRESSED" ) isShifted = true;
            if (value == "SHIFT_UNPRESSED" ) isShifted = false;
            if (value == "CAPS_PRESSED" ) isShifted = true;
            if (value == "CAPS_UNPRESSED" ) isShifted = false;
            if (value == "a") {
                rez += isShifted ? "A" : "a";
            }
            if (value == " ") {
                rez += " ";
            }

        }
    }

    std::cout << rez << std::endl;

    return 0;
}