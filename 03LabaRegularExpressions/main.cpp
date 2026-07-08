#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <algorithm>

bool IsMatch(const std::string& str, const std::regex& pattern, std::smatch& match) {
    if (std::regex_match(str, match, pattern)) {
        std::cout << "Match!!!" << std::endl;
        return true;
    } else {
        std::cout << "Not Match!!!" << std::endl;
        return false;
    }
}
bool isTemperatureValid(const std::string& tempStr) {
    std::string str = tempStr;
    // Заменяем запятую на точку для корректной работы std::stod
    std::replace(str.begin(), str.end(), ',', '.');

    try {
        double val = std::stod(str);
        // Проверяем на адекватность (например, от -100 до +100 градусов)
        if (val < -100.0 || val > 100.0) {
            std::cout << "  [Error]: Invalid temperature value (" << val << "°)" << std::endl;
            return false;
        }
        std::cout << "  [Success]: Temperature: " << val << "°  is valid." << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cout  << "  [Error]: Couldn't extract temperature value ." << std::endl;
        return false;
    }
}


int main() {
    setlocale(LC_ALL, "Russian_Russia.65001");

    std::ifstream input("Data.txt");
    if (!input.is_open()) {
        std::cerr << "Error. File not found." << std::endl;
        return 1;
    }
    std::regex pattern(R"((?:.+?\s+)?(?:spring|summer|winter|autumn)(?:\s+.+?\s+|\s+)(?:maximum|max\.|average\s+temperature)(?:\s+.+?\s+|\s+)([+-]?\d+(?:[.,]\d+)?)°(?:\s+.+)?)");
    std::string line;



    for (int i = 1;std::getline(input, line); i++) {
        std::cout << "Line number " << i << ": " << line << std::endl;
        std::smatch matchExact;
        if (IsMatch(line, pattern, matchExact)) {
            isTemperatureValid(matchExact[1].str());
        }


        std::smatch matchSub;
        if (std::regex_search(line, matchSub, pattern)) {
            std::cout << "Substring has been found!!!  ";
            std::cout << "Substring: " << matchSub[0].str() << std::endl;
            isTemperatureValid(matchSub[1].str());
        }
        else {
            std::cout << "Substring has not been found" << std::endl;
        }
    }
    return 0;
}