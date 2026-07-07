#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <regex>

void isFound(bool f) {
    std::cout << (f ? "Found ": "Not Found") << std::endl;
}
bool isReal(const std::string& s) {
    std::regex realNumberRegex(R"(^-?(\d+/\d+|\d+\.\d+|\d+\.?\d*[eE][+-]?\d+)$)");
    return std::regex_match(s,realNumberRegex);
}
double toDouble(const  std::string& s) {
    size_t slashPosition = s.find("/");
    if (slashPosition != std::string::npos) {
        int numerator = std::stoi(s.substr(0, slashPosition));
        int denominator = std::stoi(s.substr(slashPosition + 1));
        if (denominator == 0) {
            throw std::runtime_error("Zero denominator in fraction!");
        }
        return static_cast<double>(numerator)/denominator;
    }
    return std::stod(s);
}

int main() {
    
//12.05.2023 15 -7 3.14 -2.5e-3 1/2 -7/8 42 0.001 5e2 3/4


// 1) Reading from file
    std::string data;
    if (std::ifstream input("Data.txt"); input.is_open()) {
        std::getline(input, data, '\0');
    }
    else {
        std::cerr <<"Enable to open file" << std::endl;
        return 1;
    }
    std::cout << data << std::endl;

// 2) Regular expressions of Date and Numbers
    std::regex regDate(R"(\b(\d{2}\.\d{2}\.\d{4})\b)");
    std::regex regNum(R"(\b(?:-?\d+/\d+|-?\d+\.\d+|-?\d+\.?\d*[eE][+-]?\d+|-?\d+)\b)");


    std::smatch dateMatch;
    std::sregex_iterator dateIt(data.begin(), data.end(), regDate);
    std::sregex_iterator end; // empty iterator == finish of search
    if (dateIt == end) {
        std::cerr <<"Date has not been found! File has incorrect format!" <<std::endl;
        return 1;
    }
    dateMatch = *dateIt; // saving the first match of date
    size_t datePosition = dateMatch.position();
    ++dateIt; // shift iterator on the position of the next match of date, if it exists
    if (dateIt != end) {
        std::cerr << "Error! More then one date have been found!" << std::endl;
        return 1;
    }
    std::cout << "Date has been found!" << std::endl;
    std::cout << dateMatch.str() << std::endl;

    std::string beforeDate = data.substr(0, datePosition);
    if (regex_search(beforeDate,regNum)) {
        std::cerr << "Error! There are numbers before date!" << std::endl;
        return 1;
    }

// 3) Finding a sum of real and integer numbers
    std::string afterDate = data.substr(datePosition + dateMatch.length());
    long long intSum = 0;
    double realSum = 0.0;

    std::sregex_iterator it(afterDate.begin(), afterDate.end(), regNum);
    for (; it!=end; ++it) {
        std::string numString = it->str();
        double value = toDouble(numString);
        if (isReal(numString)) {
            realSum += value;
        }
        else {
            intSum += static_cast<int>(value);
        }
    }
    std::string realStr;
    std::string intStr;

    std::sregex_iterator it1(afterDate.begin(), afterDate.end(),regNum );
    for (; it1!=end; ++it1) {
        std::string numStr = it1->str();
        if (isReal(numStr)) {
            realStr +=numStr + ' ';
        }
        else {intStr += numStr + ' ';
}
    }
    std::cout << "The Real Numbers:  " << realStr << std::endl;
    std::cout << "The Sum of the real numbers: " << realSum << std::endl;
    std::cout << "The Integer Numbers:  " << intStr << std::endl;
    std::cout << "The Sum of the integer numbers: " << intSum << std::endl;

    return 0;
}