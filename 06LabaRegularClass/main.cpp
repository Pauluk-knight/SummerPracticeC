#include <iostream>
#include <concepts>

template <typename T>
requires std::regular<T>
void IsRegularClass(T& t) {
    std::cout << "Class is regular" << std::endl;
}




class Fraction {
private:
    int numerator;   // числитель
    int denominator; // знаменатель

public:
    // 1. Конструктор по умолчанию (ОБЯЗАТЕЛЕН).
    Fraction() : numerator(0), denominator(1) {}
    // 2. Деструктор (ОБЯЗАТЕЛЕН)
    ~Fraction() = default;

    // 3. Конструктор копирования (ОБЯЗАТЕЛЕН)
    Fraction(const Fraction& other)
        : numerator(other.numerator), denominator(other.denominator) {}

    // 4. Оператор присваивания копированием (ОБЯЗАТЕЛЕН)
    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }

    // 5. Конструктор перемещения (ОБЯЗАТЕЛЕН)
    Fraction(Fraction&& other) noexcept
        : numerator(other.numerator), denominator(other.denominator) {
        other.numerator = 0;
        other.denominator = 1;
    }

    // 6. Оператор присваивания перемещением (ОБЯЗАТЕЛЕН)
    Fraction& operator=(Fraction&& other) noexcept {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;

            other.numerator = 0;
            other.denominator = 1;
        }
        return *this;
    }


    bool operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    Fraction(int n, int d) : numerator(n), denominator(d != 0 ? d : 1) {}
};

// Если закомментировать ЛЮБОЙ из 7 методов выше,
// компиляция остановится на этой строке с ошибкой.
static_assert(std::regular<Fraction>, "Класс Fraction потерял свою регулярность!");

int main() {
    Fraction f1(1, 2); // 1/2
    Fraction f2;       // 0/1 (сработал конструктор по умолчанию)

    f2 = f1;           // сработало копирование

    if (f1 == f2) {    // сработало сравнение
        std::cout << "Дроби равны! Класс ведет себя как регулярный тип." << std::endl;
    }

    return 0;
}