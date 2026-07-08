#include <iostream>
#include <regex>
#include <string>

//Преобразовать дату из YYYY-MM-DD в DD.MM.YYYY:  2025-07-01 на 01.07.2025
int main() {
    std::string data1 = "My birthday on 2008-05-16";
    std::regex date1(R"((\d{4})-(\d{2})-(\d{2}))");

    std::string data2 = std::regex_replace(data1, date1,"$3.$2.$1");

    std::cout << "Input: " << data1 << std::endl;
    std::cout << "Output: " << data2 << std::endl;
    return 0;
}