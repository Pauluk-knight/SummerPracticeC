#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
//checking the correspondence of a sequence of characters
//in whole or in a part to a specific regular expression
// regex_search(data,regex()pattern);



void  IsFound (bool b) {
    std::cout << (b? "Found" : "Not Found") << std::endl;
}


int main() {

//     std::regex regExample("<(.*)>.*</\\1>");
//     bool foundExample = regex_match("<tag>value</tag>",regExample);
// IsFound(foundExample);


    std::string str1;
    std::ifstream file("Data.txt");
    if (file.is_open()) {
        std::getline(file, str1, '\0');
    }
    else {
        std::cerr <<"Enable to open the file" << std::endl;
        return 1;
    }
    std::cout << str1 << std::endl;

    std::regex reg1("ab{2,4}a");
    bool found = regex_search(str1,reg1);
    IsFound(found);


    std::cout << "Testing of some strings" << std::endl;
    std::vector<std::string> tests = {"aaabbbaaa", "xaba", "acsadabbbaaa", "abb2a", "abbbaaaaaaa", "uhu uwu abbba  ;lwco "};

    for (const auto& test : tests) {
        bool t = regex_search(test, reg1);
        IsFound(t);
    }

    return 0;
}